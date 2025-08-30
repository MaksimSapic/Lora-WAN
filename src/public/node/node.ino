#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

unsigned long packetIndex = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if(!LoRa.begin(868E6)) { Serial.println("LoRa failed"); while(1); }

  Serial.println("LoRa Node ready");
}

void loop() {
  String message = "Node1 Packet#" + String(packetIndex++);
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println("Sent: " + message);
  delay(5000);
}