#include <SPI.h>
#include <RadioLib.h>     // from RadioLib by Jan Gromes v7.6.0
#include <TinyGPS++.h>    // from TinyGPSPlus by Mikal Hart v1.0.3
#include <MAVLink.h>
#include "simba_headers/simba/simba.h" // generated from simba.xml

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

int debugInt = 0;

LoRaQueue loraQueue;

SPIClass spiLora(HSPI);
SX1262   radio = new Module(LORA_NSS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiLora);
TinyGPSPlus gpsInternal;
HardwareSerial SerialMAV(2);

void readInternalGPSPos();
void sendInternalGPSPos();
void readRadioTransmission();
void sendRadioTransmission();
void readMavlinkUART();

void sendBytesToComputer(uint8_t* data, size_t length);

volatile bool radioEvent = false;
void radioEventCallback() {
  radioEvent = true;
}

void updateRadioStatus();

struct RadioStatus
{
  bool TXdone = true;
  bool TXsending = false;
  bool RXdone = true;
  bool RXreceiving = false;
} radioStatus;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
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
  // update radio status based on events
  updateRadioStatus();

  // read InternalGNSS bytes
  readInternalGPSPos();

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

  delay(10);
}

void updateRadioStatus()
{
  if (radioEvent) {
    radioEvent = false;
    // get irq status
    uint32_t irq = radio.getIrqFlags();
    radio.clearIrqFlags(irq);
    if (irq & RADIOLIB_SX126X_IRQ_TX_DONE) radioStatus.TXdone = true;
    if (irq & RADIOLIB_SX126X_IRQ_RX_DONE) radioStatus.RXdone = true;
  }
}

void readInternalGPSPos()
{
  while (Serial1.available() > 0)
    gpsInternal.encode(Serial1.read());

  if (gpsInternal.time.isUpdated())
  {
    // Serial.print("Time: ");
    // Serial.print(gpsInternal.time.hour());
    // Serial.print(":");
    // Serial.print(gpsInternal.time.minute());
    // Serial.print(":");
    // Serial.println(gpsInternal.time.second());
  }
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
  #ifdef DEBUG
    Serial.println("Enqueue, queue size: " + String(loraQueue.getFillPercentage()) + "%");
  #endif
}

void readMavlinkUART()
{
  static mavlink_message_t msg;
  static mavlink_status_t mav_status;
  static uint8_t txBuffer[300];

  // read mavlink bytes and queue up for transmission
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
  
  #ifdef DEBUG
    Serial.println("Dequeue, queue size: " + String(loraQueue.getFillPercentage()) + "%");
  #endif
  
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