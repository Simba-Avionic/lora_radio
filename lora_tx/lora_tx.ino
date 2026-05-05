// ============================================================
//  ROCKET TELEMETRY — Nadajnik 
//  Dwa źródła GPS - jeden pakiet LoRa co 2s
//
//  MAVLink: dialekt SIMBA, MSG ID 72 (SIMBA_GPS)
//  Pakiet: 22 bajty (bez paddingu, packed)
// ============================================================
#include <RadioLib.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <MAVLink.h>


#define LORA_NSS   41
#define LORA_SCK   7
#define LORA_MOSI  9
#define LORA_MISO  8
#define LORA_RESET 42
#define LORA_BUSY  40
#define LORA_DIO1  39
#define LORA_SW1   38
#define GPS_INT_RX 44
#define GPS_INT_TX 43
#define MAV_RX     2
#define MAV_TX     1

#define SIMBA_MSG_GPS  72
#define TX_INTERVAL_MS 2000UL

// ----------------------------------------------------------------
//  PAKIET RADIOWY — 22 bajty
//
//  Offset  Rozmiar  Pole
//    0       4      int_lat        wbudowany GPS, stopnie * 1E7
//    4       4      int_lon        wbudowany GPS, stopnie * 1E7
//    8       4      int_alt        wbudowany GPS, metry [float]
//   12       4      mav_lat        SIMBA GPS,     stopnie * 1E7
//   16       4      mav_lon        SIMBA GPS,     stopnie * 1E7
//   20       4      mav_alt        SIMBA GPS,     metry [float]  (altitude_cm / 100)
//   24       1      status         mapa bitów 
//   25       1      padding        wyrównanie do 2 bajtów
//   26       2      checksum       CRC-16/CCITT
//  = 28 bajtów łącznie
//
//  Mapa bitów 'status':
//    Bit 0 (0x01) — wbudowany GPS: fix valid
//    Bit 1 (0x02) — SIMBA GPS:     wiadomość odebrana w tym cyklu
// ----------------------------------------------------------------
struct __attribute__((packed)) RocketPacket {
  int32_t  int_lat;
  int32_t  int_lon;
  float    int_alt;

  int32_t  mav_lat;
  int32_t  mav_lon;
  float    mav_alt;

  uint8_t  status;
  uint8_t  _pad;       
  uint16_t checksum;
};

struct __attribute__((packed)) SimbaGpsPayload {
  int32_t lat;
  int32_t lon;
  int32_t altitude_cm;
};

SPIClass    spiLora(HSPI);
SX1262      radio = new Module(LORA_NSS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiLora);
TinyGPSPlus gpsInternal;
HardwareSerial SerialMAV(2);

RocketPacket pkt;
unsigned long lastSend = 0;

// ----------------------------------------------------------------
//  CRC-16/CCITT — wielomian 0x1021
//  Liczy po wszystkich bajtach oprócz ostatnich 2 (pole checksum)
// ----------------------------------------------------------------
uint16_t crc16(const uint8_t *data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (int j = 0; j < 8; j++) {
      crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
    }
  }
  return crc;
}

// ----------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  static_assert(sizeof(RocketPacket) == 28, "Zly rozmiar RocketPacket!");
  Serial.printf("[INIT] sizeof(RocketPacket) = %u bajtow\n", sizeof(RocketPacket));

  Serial1.begin(9600, SERIAL_8N1, GPS_INT_RX, GPS_INT_TX);

  //mavlink
  SerialMAV.begin(57600, SERIAL_8N1, MAV_RX, MAV_TX);

  // LoRa SX1262
  pinMode(LORA_SW1, OUTPUT);
  digitalWrite(LORA_SW1, HIGH);
  spiLora.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);

  // 920 MHz | BW 125 kHz | SF10 | CR 4/5 | 22 dBm | preambuła 8
  // SF10/125kHz/28B = 330 ms
  int state = radio.begin(920.0, 125.0, 10, 5,
                          RADIOLIB_SX126X_SYNC_WORD_PRIVATE, 22, 8);
  if (state == RADIOLIB_ERR_NONE) {
    radio.setDio2AsRfSwitch(true);
    Serial.println(F("[INIT] LoRa OK"));
  } else {
    Serial.printf("[INIT] BLAD LoRa: %d\n", state);
    while (true);
  }

  memset(&pkt, 0, sizeof(pkt));
}

// ----------------------------------------------------------------
void loop() {

  while (Serial1.available()) {
    gpsInternal.encode(Serial1.read());
  }
  if (gpsInternal.location.isValid()) {
    pkt.int_lat  = (int32_t)(gpsInternal.location.lat() * 1e7);
    pkt.int_lon  = (int32_t)(gpsInternal.location.lng() * 1e7);
    pkt.int_alt  = (float)gpsInternal.altitude.meters();
    pkt.status  |= 0x01;
  }

  {
    mavlink_message_t msg;
    mavlink_status_t  mav_status;

    while (SerialMAV.available()) {
      uint8_t c = SerialMAV.read();

      if (!mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &mav_status)) {
        continue; 
      }

      if (msg.msgid != SIMBA_MSG_GPS) {
        continue; 
      }

      SimbaGpsPayload gps;
      memcpy(&gps, _MAV_PAYLOAD(&msg), sizeof(SimbaGpsPayload));

      pkt.mav_lat  = gps.lat;
      pkt.mav_lon  = gps.lon;
      pkt.mav_alt  = gps.altitude_cm / 100.0f; 
      pkt.status  |= 0x02;

      Serial.printf("[MAV GPS] lat=%.7f lon=%.7f alt=%.2fm\n",
                    gps.lat / 1e7, gps.lon / 1e7, pkt.mav_alt);
    }
  }

  if (millis() - lastSend >= TX_INTERVAL_MS) {
    lastSend = millis();

    pkt._pad      = 0x00;
    pkt.checksum  = crc16((const uint8_t *)&pkt,
                           sizeof(RocketPacket) - sizeof(uint16_t));

    int txState = radio.transmit((uint8_t *)&pkt, sizeof(RocketPacket));

    if (txState == RADIOLIB_ERR_NONE) {
      Serial.printf(
        "[TX OK] INT(%.6f, %.6f, %.1fm) MAV(%.6f, %.6f, %.1fm) status=0x%02X\n",
        pkt.int_lat / 1e7, pkt.int_lon / 1e7, pkt.int_alt,
        pkt.mav_lat / 1e7, pkt.mav_lon / 1e7, pkt.mav_alt,
        pkt.status
      );
    } else {
      Serial.printf("[TX ERR] kod RadioLib: %d\n", txState);
    }

    pkt.status = 0;
  }
}
