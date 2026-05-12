#include <RadioLib.h>
#include <SPI.h>
// #include <TinyGPS++.h>

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

SPIClass spiLora(HSPI);
SX1262   radio = new Module(LORA_NSS, LORA_DIO1, LORA_RESET, LORA_BUSY, spiLora);
HardwareSerial SerialMAV(2);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World");

  // INIT GPS'a XIAO (LoRa GNSS)
  Serial1.begin(9600, SERIAL_8N1, GPS_INT_RX, GPS_INT_TX);
}

void loop() {
  while (Serial1.avaliable())
  {
    Serial.print(Serial1.read());
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}
