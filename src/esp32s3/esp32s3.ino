#include <SPI.h>
#include <RadioLib.h>     // from RadioLib by Jan Gromes v7.6.0
#include <TinyGPS++.h>    // from TinyGPSPlus by Mikal Hart v1.0.3
#include "simba_headers/simba/mavlink.h" // generated from simba.xml

#include "LoRaQueue.hpp"

#define DEBUG

#define MODE_RECEIVER     0
#define MODE_TRANSMITTER  1
#define MODULE_MODE       MODE_TRANSMITTER

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

#define TX_INTERVAL_MS 2000UL
#define TX_GNSS_TO_COMPUTER_INTERVAL_MS 1000UL
#define TX_RADIO_STATS_TO_COMPUTER_INTERVAL_MS 1000UL
#define LOOP_DELAY_MS 10UL      // main loop delay

#define UART_RING_BUFFER_SIZE 8096 // zabezpieczenie przed burstami danych

LoRaQueue loraQueue;

SPIClass spiLora(HSPI);
SX1262   radio = new Module(LORA_NSS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiLora);
TinyGPSPlus gpsInternal;
HardwareSerial SerialMAV(2);

void readInternalGPSPos();
void sendInternalGPSPos();
void sendInternalGPSToComputer();

void sendRadioStatsToComputer();

void readRadioTransmission();
void sendRadioTransmission();

void readMavlinkUART();

void sendBytesToComputer(uint8_t* data, size_t length);

volatile bool radioEvent = false;
void radioEventCallback() {
  radioEvent = true;
}

void updateRadioStatus();

inline void ledOn() { digitalWrite(LED_BUILTIN, LOW); }

inline void ledOff() { digitalWrite(LED_BUILTIN, HIGH); }

struct RadioStatus
{
  bool TXdone = true;
  bool TXsending = false;
  bool RXdone = true;
  bool RXreceiving = false;
} radioStatus;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ledOff();

  Serial.setRxBufferSize(UART_RING_BUFFER_SIZE);
  Serial1.setRxBufferSize(UART_RING_BUFFER_SIZE);
  SerialMAV.setRxBufferSize(UART_RING_BUFFER_SIZE);

  Serial.begin(57600);

  Serial1.begin(9600, SERIAL_8N1, GPS_INT_RX, GPS_INT_TX);

  //mavlink
  SerialMAV.begin(57600, SERIAL_8N1, MAV_RX, MAV_TX);

  // LoRa SX1262
  pinMode(LORA_SW1, OUTPUT);
  digitalWrite(LORA_SW1, HIGH);
  spiLora.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);

  // 920 MHz | BW 125 kHz | SF10 | CR 4/5 | 22 dBm 
  // SF10/125kHz/28B = 330 ms
  int state = radio.begin(920.0, 125.0, 10, 5,
                          RADIOLIB_SX126X_SYNC_WORD_PRIVATE, 22, 8);
  if (state == RADIOLIB_ERR_NONE) {
    radio.setDio2AsRfSwitch(true);
    radio.setDio1Action(radioEventCallback);
    Serial.println(F("[INIT] LoRa OK"));
  } else {
    Serial.printf("[INIT] BLAD LoRa: %d\n", state);
    while (true);
  }
}

void loop() {
  unsigned long loopStart = millis();

  // update radio status based on events
  // HAS delay(1) INSIDE
  updateRadioStatus();

  // read InternalGNSS bytes
  readInternalGPSPos();
  sendInternalGPSToComputer();

  // read Main computer mavlink bytes & queue up for transmiton
  readMavlinkUART();

  #if MODULE_MODE == MODE_TRANSMITTER
    // queue up InternalGPSPos for transmition once per X millis
    sendInternalGPSPos();
    // send radio transmission
    sendRadioTransmission();
  #endif

  #if MODULE_MODE == MODE_RECEIVER              // later this define should be replaced by a boot pin check and even later by synchronization beetween the two sides
    // read radio transmission
    readRadioTransmission();
  #endif

  // send link stats to Serial once in a while
  sendRadioStatsToComputer();

  // count delay and imply a delay so it is a LOOP_DELAY_MS delay between the start of each loop iteration
  unsigned long loopDuration = millis() - loopStart;
  if (loopDuration < LOOP_DELAY_MS) {
    delay(LOOP_DELAY_MS - loopDuration);
  }
}

void updateRadioStatus()
{
  if (radioEvent) {
    radioEvent = false;
    // get irq status
    uint32_t irq = radio.getIrqFlags();
    radio.clearIrqFlags(irq);
    if (irq & RADIOLIB_SX126X_IRQ_TX_DONE) 
    {
      radioStatus.TXdone = true;
      ledOff();
    }

    // header is valid, we are receiving a message
    if (irq & RADIOLIB_SX126X_IRQ_HEADER_VALID)
    {
      ledOn();
      delay(1);
    }

    // RX is done for RX_DONE, CRC_ERR, HEADER_ERR, TIMEOUT
    if ((irq & RADIOLIB_SX126X_IRQ_RX_DONE) ||
          (irq & RADIOLIB_SX126X_IRQ_CRC_ERR) ||
            (irq & RADIOLIB_SX126X_IRQ_HEADER_ERR) ||
              (irq & RADIOLIB_SX126X_IRQ_TIMEOUT))
    {
      radioStatus.RXdone = true;
      ledOff();
    }
  }
}

void readInternalGPSPos()
{
  while (Serial1.available() > 0)
    gpsInternal.encode(Serial1.read());
}

void sendInternalGPSPos()
{
  static unsigned long lastSend = 0;

  if (millis() - lastSend < TX_INTERVAL_MS) {
    return; // not time to send yet
  }
  lastSend = millis();
  static mavlink_message_t msg;
  static mavlink_status_t mav_status;
  mavlink_msg_simba_gps_pack(1, 221, &msg, gpsInternal.location.lat() * 1e7, gpsInternal.location.lng() * 1e7, gpsInternal.altitude.meters() * 100);
  uint8_t txBuffer[300];
  uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
  LoRaQueue::Status status = loraQueue.enqueue(txBuffer, len);
}

void sendInternalGPSToComputer()
{
  static unsigned long lastSend = 0;

  if (millis() - lastSend < TX_GNSS_TO_COMPUTER_INTERVAL_MS) {
    return; // not time to send yet
  }
  lastSend = millis();
  static mavlink_message_t msg;
  static mavlink_status_t mav_status;

  mavlink_msg_l76k_gps_pack(1, 221, &msg, gpsInternal.date.value(), gpsInternal.time.value(), gpsInternal.location.lat() * 1e7, gpsInternal.location.lng() * 1e7, gpsInternal.speed.mps(),
                              gpsInternal.course.deg(), gpsInternal.altitude.meters() * 100, gpsInternal.satellites.value(), gpsInternal.hdop.value(), gpsInternal.sentencesWithFix());
  uint8_t txBuffer[300];
  uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
  sendBytesToComputer(txBuffer, len);
}

void sendRadioStatsToComputer()
{
  static unsigned long lastSend = 0;

  if (millis() - lastSend < TX_RADIO_STATS_TO_COMPUTER_INTERVAL_MS) {
    return; // not time to send yet
  }
  lastSend = millis();
  static mavlink_message_t msg;
  static mavlink_status_t mav_status;

  float rssi = radio.getRSSI();
  float snr = radio.getSNR();
  float noise = rssi - snr;

  if (rssi < -200) rssi = -200;
  if (noise < -200) noise = -200;
  if (rssi > 55) rssi = 55;
  if (noise > 55) noise = 55;

  // convert rssi and noise to 0-255 range by adding 200
  uint8_t rssiByte = (uint8_t)(rssi + 200);
  uint8_t noiseByte = (uint8_t)(noise + 200);

  mavlink_msg_radio_status_pack(1, 221, &msg, rssiByte, 0, (uint8_t)loraQueue.getFillPercentage(), noiseByte, 0, 0, 0);
  uint8_t txBuffer[300];
  uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
  sendBytesToComputer(txBuffer, len);
}

void readMavlinkUART()
{
  static mavlink_message_t msg;
  static mavlink_status_t mav_status;
  static uint8_t txBuffer[300];

  // read mavlink bytes FROM UART and queue up for transmission
  while (SerialMAV.available())
  {
    uint8_t c = SerialMAV.read();

    if (!mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &mav_status)) {
      continue; 
    }

    // mamy pełną ramkę MAVLink

    uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
    LoRaQueue::Status status = loraQueue.enqueue(txBuffer, len);
  }

  // read mavlink bytes FROM USB and queue up for transmission
  while (Serial.available())
  {
    uint8_t c = Serial.read();

    if (!mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &mav_status)) {
      continue; 
    }

    // mamy pełną ramkę MAVLink

    uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
    LoRaQueue::Status status = loraQueue.enqueue(txBuffer, len);
  }
}

void readRadioTransmission()
{
  if (!radioStatus.RXdone) {
    return; // reception is still in progress, wait for it to finish
  }

  if (radioStatus.RXreceiving && radioStatus.RXdone) {
    // finish reception
    radioStatus.RXreceiving = false;
    radio.finishReceive();

    byte data[300];
    int numBytes = radio.getPacketLength();
    int state = radio.readData(data, numBytes);

    if (state == RADIOLIB_ERR_NONE) {
      // no errors
      // send bytes to the computer
      sendBytesToComputer(data, numBytes);
    }
  }

  // start new reception
  radioStatus.RXreceiving = true;
  radioStatus.RXdone = false;
  radio.startReceive();
}

void sendRadioTransmission()
{
  if (!radioStatus.TXdone) {
    return; // transmission is still in progress, wait for it to finish
  }

  if (radioStatus.TXsending && radioStatus.TXdone) {
    // finish transmission
    radioStatus.TXsending = false;
    radio.finishTransmit();
  }

  byte data[300];
  int length;
  LoRaQueue::Status status = loraQueue.dequeue(data, length);
  if (length == 0) {
    return; // no message to send
  }

  ledOn();
  radioStatus.TXdone = false;
  radioStatus.TXsending = true;
  radio.startTransmit(data, length);
}

void sendBytesToComputer(uint8_t* data, size_t length)
{
  // USB serial                   (mission control)
  Serial.write(data, length);
  // also the mavlink serial      (rocket)
  SerialMAV.write(data, length);
}