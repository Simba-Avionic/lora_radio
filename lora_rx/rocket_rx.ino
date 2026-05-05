
#include "simba_headers/simba/mavlink_msg_simba_gps.h"
#include "simba_headers/simba_radio/mavlink_msg_radio_status.h"

#include <RadioLib.h>
#include <SPI.h>

// #define DEBUG    // bez ROS2


#define LORA_NSS   41
#define LORA_SCK   7
#define LORA_MOSI  9
#define LORA_MISO  8
#define LORA_RESET 42
#define LORA_BUSY  40
#define LORA_DIO1  39
#define LORA_SW1   38


#define MAV_SYS_ID        1
#define MAV_COMP_INT_GPS  1   // compid=1: GPS wbudowany w moduł LoRa
#define MAV_COMP_MAV_GPS  2   // compid=2: GPS z komputera pokładowego


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
static_assert(sizeof(RocketPacket) == 28, "Zly rozmiar RocketPacket!");

SPIClass spiLora(HSPI);
SX1262   radio = new Module(LORA_NSS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiLora);

static uint8_t  mavSeq   = 0;
static uint16_t rxErrors = 0;

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


void sendSimbaGps(uint8_t compid, int32_t lat, int32_t lon, float alt_m) {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_simba_gps_pack(
    MAV_SYS_ID, compid, &msg,
    lat,
    lon,
    (int32_t)(alt_m * 100.0f)   // m → cm
  );
  msg.seq = mavSeq++;

  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}


void sendRadioStatus(float rssi_dbm, float snr_db) {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  uint8_t rssi_u8  = (uint8_t)constrain((int)(rssi_dbm + 200.0f), 0, 254);
  uint8_t noise_u8 = (uint8_t)constrain((int)(50.0f - snr_db),    0, 254);

  mavlink_msg_radio_status_pack(
    MAV_SYS_ID, MAV_COMP_INT_GPS, &msg,
    rssi_u8,   
    0,         
    100,       
    noise_u8,  
    0,         
    rxErrors,  
    0          
  );
  msg.seq = mavSeq++;

  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}

// ----------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LORA_SW1, OUTPUT);
  digitalWrite(LORA_SW1, HIGH);
  spiLora.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);

  int state = radio.begin(920.0, 125.0, 10, 5,
                           RADIOLIB_SX126X_SYNC_WORD_PRIVATE, 10, 8);
  if (state == RADIOLIB_ERR_NONE) {
    radio.setDio2AsRfSwitch(true);
#ifdef DEBUG
    Serial.println("[INIT] LoRa RX gotowy");
    Serial.printf("[INIT] RocketPacket=%u B\n", sizeof(RocketPacket));
#endif
  } else {
#ifdef DEBUG
    Serial.printf("[INIT] BLAD LoRa: %d\n", state);
#endif
    while (true);
  }
}

// ----------------------------------------------------------------
void loop() {
  RocketPacket pkt;

  int state = radio.receive((uint8_t *)&pkt, sizeof(RocketPacket));

  if (state != RADIOLIB_ERR_NONE) {
#ifdef DEBUG
    if (state != RADIOLIB_ERR_RX_TIMEOUT) {
      Serial.printf("[RX ERR] %d\n", state);
    }
#endif
    return;
  }

  float rssi = radio.getRSSI();
  float snr  = radio.getSNR();

  // Weryfikacja CRC
  uint16_t expected = crc16((const uint8_t *)&pkt,
                             sizeof(RocketPacket) - sizeof(uint16_t));
  if (expected != pkt.checksum) {
    rxErrors++;
#ifdef DEBUG
    Serial.printf("[CRC ERR] oczekiwano=0x%04X dostano=0x%04X err#%u\n",
                  expected, pkt.checksum, rxErrors);
#endif
    sendRadioStatus(rssi, snr);  
    return;
  }

#ifdef DEBUG
  Serial.printf("[OK] RSSI=%.1f SNR=%.1f status=0x%02X\n", rssi, snr, pkt.status);
  if (pkt.status & 0x01)
    Serial.printf("  INT: %.7f %.7f %.2fm\n",
                  pkt.int_lat/1e7, pkt.int_lon/1e7, pkt.int_alt);
  if (pkt.status & 0x02)
    Serial.printf("  MAV: %.7f %.7f %.2fm\n",
                  pkt.mav_lat/1e7, pkt.mav_lon/1e7, pkt.mav_alt);
#endif

  if (pkt.status & 0x01)
    sendSimbaGps(MAV_COMP_INT_GPS, pkt.int_lat, pkt.int_lon, pkt.int_alt);

  if (pkt.status & 0x02)
    sendSimbaGps(MAV_COMP_MAV_GPS, pkt.mav_lat, pkt.mav_lon, pkt.mav_alt);

  sendRadioStatus(rssi, snr);
}
