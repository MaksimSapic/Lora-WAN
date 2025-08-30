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
  while (!Serial);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Sender Initialized");
}

void loop() {
  Serial.print("Sending packet #");
  Serial.println(packetIndex);

  LoRa.beginPacket();
  LoRa.print("Packet #");
  LoRa.print(packetIndex);
  LoRa.print(" - Hello from Nikola Lalic at ");
  LoRa.print(millis());
  LoRa.endPacket();

  packetIndex++;  
  delay(5000);    
}
