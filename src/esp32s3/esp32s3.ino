#include <SPI.h>
#include <RadioLib.h>     // from RadioLib by Jan Gromes v7.6.0
#include <TinyGPS++.h>    // from TinyGPSPlus by Mikal Hart v1.0.3
#include "simba_headers/simba/mavlink.h" // generated from simba.xml
#include <WiFi.h>         // from the ESP32 Arduino framework
#include <WebServer.h>    // from the ESP32 Arduino framework
#include "LoRaQueue.hpp"

#define DEBUG

#define MODE_RECEIVER     0
#define MODE_TRANSMITTER  1
#define MODE_TRANSCEIVER  2
#define MODULE_MODE       MODE_RECEIVER

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
#define TX_INTERVAL_TRANSCEIVER_MS 5000UL
#define TX_GNSS_TO_COMPUTER_INTERVAL_MS 1000UL
#define TX_RADIO_STATS_TO_COMPUTER_INTERVAL_MS 1000
#define READ_NOISE_INTERVAL_MS 50UL
#define LOOP_DELAY_MS 10UL      // main loop delay

#define UART_RING_BUFFER_SIZE 8096 // zabezpieczenie przed burstami danych

#define WIFI_AP_SSID "LoRa-GPS"
#define WIFI_AP_PASS "simba1234"
#define WIFI_AP_IP   "192.168.10.131"
#define WEB_REFRESH_SEC 10

#define LAT_SETUP_AREA 35.342322
#define LON_SETUP_AREA -117.825152

LoRaQueue loraQueue;
WebServer webServer(80);

mavlink_simba_gps_t loraRxRocketGps = {};

bool loraRxValid = false;
unsigned long loraRxLastUpdateMs = 0;

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

void readNoise();

void readMavlinkUART();

void sendBytesToComputer(uint8_t* data, size_t length);
void handleWebRoot();

volatile bool radioEvent = false;
void radioEventCallback() {
  radioEvent = true;
}

void updateRadioStatus();

inline void ledOn() { digitalWrite(LED_BUILTIN, LOW); }

inline void ledOff() { digitalWrite(LED_BUILTIN, HIGH); }

enum RadioMode
{
  RECEIVER = 0,
  TRANSMITTER,
  TRANSCEIVER
};

struct RadioStatus
{
  bool TXdone = true;
  bool TXsending = false;
  bool RXdone = true;
  bool RXreceiving = false;

  uint16_t rxErrors = 0;

  float noise_level = 0.0f;
  float rssi_last_msg = 0.0f;
  float snr_last_msg = 0.0f;
  
  bool hasGNSSModule = false;
  bool hasReceivedLoRaMessage = false;
  unsigned long lastReceivedLoRaMessageTime = 0;
  RadioMode mode = (RadioMode)MODULE_MODE;
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

  if (radioStatus.mode == RadioMode::TRANSCEIVER) {
    IPAddress ip, gateway, subnet;
    ip.fromString(WIFI_AP_IP);
    gateway.fromString(WIFI_AP_IP);
    subnet.fromString("255.255.255.0");
    WiFi.softAPConfig(ip, gateway, subnet);
    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASS);
    Serial.printf("[INIT] WiFi AP: %s  IP: %s\n", WIFI_AP_SSID, WIFI_AP_IP);

    webServer.on("/", handleWebRoot);
    webServer.begin();
  }
}

void loop() {
  unsigned long loopStart = millis();

  // update radio status based on events
  updateRadioStatus();

  // try to read noise level
  readNoise();

  // read InternalGNSS bytes
  readInternalGPSPos();
  sendInternalGPSToComputer();

  // read Main computer mavlink bytes & queue up for transmiton
  readMavlinkUART();

  // #if MODULE_MODE == MODE_TRANSMITTER
  if (radioStatus.mode == RadioMode::TRANSMITTER || radioStatus.mode == RadioMode::TRANSCEIVER) {
    // queue up InternalGPSPos for transmition once per X millis
    sendInternalGPSPos();
    // send radio transmission
    sendRadioTransmission();
  }
  // #endif

  // #if MODULE_MODE == MODE_RECEIVER              // later this define should be replaced by a boot pin check and even later by synchronization beetween the two sides
  if (radioStatus.mode == RadioMode::RECEIVER || radioStatus.mode == RadioMode::TRANSCEIVER) {
    // read radio transmission
    readRadioTransmission();
  }
  // #endif

  // send link stats to Serial once in a while
  sendRadioStatsToComputer();

  if (radioStatus.mode == RadioMode::TRANSCEIVER) {
    webServer.handleClient();
  }

  // count delay and imply a delay so it is a LOOP_DELAY_MS delay between the start of each loop iteration
  unsigned long loopDuration = millis() - loopStart;
  if (loopDuration < LOOP_DELAY_MS) {
    delay(LOOP_DELAY_MS - loopDuration);
  }
}

void updateRadioStatus()
{
  static bool turnOffLedInNextLoop = false;
  if (turnOffLedInNextLoop) {
    turnOffLedInNextLoop = false;
    ledOff();
  }
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
      turnOffLedInNextLoop = true;
      radioStatus.hasReceivedLoRaMessage = true;
      radioStatus.lastReceivedLoRaMessageTime = millis();
    }

    // RX is done for RX_DONE, CRC_ERR, HEADER_ERR, TIMEOUT
    if ((irq & RADIOLIB_SX126X_IRQ_RX_DONE) ||
          (irq & RADIOLIB_SX126X_IRQ_CRC_ERR) ||
            (irq & RADIOLIB_SX126X_IRQ_HEADER_ERR) ||
              (irq & RADIOLIB_SX126X_IRQ_TIMEOUT))
    {
      if ((irq & RADIOLIB_SX126X_IRQ_CRC_ERR) ||
           (irq & RADIOLIB_SX126X_IRQ_HEADER_ERR)) { radioStatus.rxErrors++; }
      radioStatus.RXdone = true;
      turnOffLedInNextLoop = true;
    }
  }
}

void readInternalGPSPos()
{
  while (Serial1.available() > 0)
  {
    radioStatus.hasGNSSModule = true;
    gpsInternal.encode(Serial1.read());
  }
}

void sendInternalGPSPos()
{
  if (!radioStatus.hasGNSSModule) {
    return; // no GNSS module, nothing to send
  }

  static unsigned long lastSend = 0;

  unsigned long interval = (radioStatus.mode == RadioMode::TRANSCEIVER)
                             ? TX_INTERVAL_TRANSCEIVER_MS
                             : TX_INTERVAL_MS;
  if (millis() - lastSend < interval) {
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
  if (!radioStatus.hasGNSSModule) {
    return; // no GNSS module, nothing to send
  }

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

  float rssi = radioStatus.rssi_last_msg;
  float noise = radioStatus.noise_level;
  float weird_noise = radioStatus.rssi_last_msg - radioStatus.snr_last_msg;

  // Serial.printf("\nRSSI: %.2f, Noise: %.2f, WeirdNoise: %.2f\n", rssi, noise, weird_noise);
  // Serial.printf("SNR: %.2f  True SNR: %.2f\n", radioStatus.snr_last_msg, rssi - noise);

  if (rssi < -200) rssi = -200;
  if (noise < -200) noise = -200;
  if (weird_noise < -200) weird_noise = -200;
  if (rssi > 55) rssi = 55;
  if (noise > 55) noise = 55;
  if (weird_noise > 55) weird_noise = 55;

  // convert rssi and noise to 0-255 range by adding 200
  uint8_t rssiByte = (uint8_t)(rssi + 200);
  uint8_t noiseByte = (uint8_t)(noise + 200);
  uint8_t weirdNoiseByte = (uint8_t)(weird_noise + 200);

  uint8_t txBuffer[300];
  // reliable rssi and link quality stats
  mavlink_msg_radio_status_pack(1, 221, &msg, rssiByte, 0, (uint8_t)loraQueue.getFillPercentage(), weirdNoiseByte, 0, radioStatus.rxErrors, 0);
  uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &msg);
  sendBytesToComputer(txBuffer, len);
  
  if (radioStatus.mode == RadioMode::TRANSMITTER) {
    return; // in transmitter mode we don't listen to the ether, so we don't know what is in there
  }
  // estimated, randomly tried noise floor value
  mavlink_msg_radio_status_pack(1, 222, &msg, rssiByte, 0, (uint8_t)loraQueue.getFillPercentage(), noiseByte, 0, radioStatus.rxErrors, 0);
  len = mavlink_msg_to_send_buffer(txBuffer, &msg);
  sendBytesToComputer(txBuffer, len);
}

void readNoise()
{
  static unsigned long lastRead = 0;

  if (millis() - lastRead < READ_NOISE_INTERVAL_MS) {
    return; // not time to read yet
  }
  lastRead = millis();
  
  float noiseCandidate = radio.getRSSI(false);
  if (noiseCandidate < radioStatus.rssi_last_msg - radioStatus.snr_last_msg - 3.0) {
    radioStatus.noise_level = noiseCandidate;
  }
  else if (radioStatus.snr_last_msg < 6.0) {
    radioStatus.noise_level = radioStatus.rssi_last_msg - radioStatus.snr_last_msg;
  }
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

    radioStatus.rssi_last_msg = radio.getRSSI(true);
    radioStatus.snr_last_msg = radio.getSNR();

    byte data[300];
    int numBytes = radio.getPacketLength();
    int state = radio.readData(data, numBytes);

    if (state == RADIOLIB_ERR_NONE) {
      // no errors
      // send bytes to the computer
      sendBytesToComputer(data, numBytes);

      // parse for SIMBA_GPS to update the web page (transceiver only)
      if (radioStatus.mode == RadioMode::TRANSCEIVER) {
        static mavlink_message_t rxMsg;
        static mavlink_status_t  rxStatus;
        for (int i = 0; i < numBytes; i++) {
          if (mavlink_parse_char(MAVLINK_COMM_1, data[i], &rxMsg, &rxStatus)) {
            if (rxMsg.msgid == MAVLINK_MSG_ID_SIMBA_GPS) {
              if (rxMsg.sysid == 1 && rxMsg.compid == 200){
                mavlink_msg_simba_gps_decode(&rxMsg, &loraRxRocketGps);
              }
              loraRxValid = true;
              loraRxLastUpdateMs = millis();
            }
          }
        }
      }
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

void handleWebRoot()
{
  String html = F("<!DOCTYPE html><html><head>"
    "<meta charset='utf-8'>"
    "<title>LoRa GPS</title>"
    "<style>body{font-family:monospace;max-width:620px;margin:40px auto;padding:0 16px}"
    "h2{margin-bottom:4px}table{border-collapse:collapse;width:100%}"
    "td{padding:6px 10px;border:1px solid #ccc}th{padding:6px 10px;background:#eee;border:1px solid #ccc}"
    "a{color:#1a73e8}.stale{color:#999}</style>"
    "<script>setInterval(function(){window.location='/';},");
  html += (WEB_REFRESH_SEC * 1000);
  html += F(");</script>"
    "</head><body>"
    "<h2>LoRa GPS Tracker</h2>");

  html += F("<h3>Rocket (LoRa RX)</h3>");
  if (loraRxValid) {
    double lat = loraRxRocketGps.lat / 1e7;
    double lon = loraRxRocketGps.lon / 1e7;
    float  alt = loraRxRocketGps.altitude / 100.0f;
    html += F("<table><tr><th>Lat</th><th>Lon</th></tr><tr>");
    html += "<td>" + String(lat, 7) + "</td>";
    html += "<td>" + String(lon, 7) + "</td>";
    html += "<td>" + String(alt, 1) + "</td></tr></table>";
    html += "<p><a href='https://maps.google.com/?q=" +
            String(lat, 7) + "," + String(lon, 7) +
            "' target='_blank'>Open in Google Maps</a></p>";
  } else {
    html += F("<p class='stale'>No data received yet.</p>");
  }

  html += F("<hr>");
  html += F("<h3>Setup area)</h3>");
  html += F("<table><tr><th>Lat</th><th>Lon</th><th>Alt (m)</th></tr><tr>");
  html += "<td>" + String(LAT_SETUP_AREA, 7) + "</td>";
  html += "<td>" + String(LON_SETUP_AREA, 7) + "</td></tr></table>";
  html += "<p><a href='https://maps.google.com/?q=" +
          String(LAT_SETUP_AREA, 7) + "," + String(LON_SETUP_AREA, 7) +
          "' target='_blank'>Open in Google Maps</a></p>";

  html += F("<p style='color:#999;font-size:0.85em'>Refreshes every ");
  html += WEB_REFRESH_SEC;
  html += F(" s</p></body></html>");
  webServer.send(200, "text/html", html);
}