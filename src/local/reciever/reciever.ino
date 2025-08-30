#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK 5
#define LORA_MISO 18
#define LORA_MOSI 23
#define LORA_SS 17
#define LORA_RST 14
#define LORA_DIO0 26

void setup() {
  Serial.begin(115200);
  while (!Serial);  
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS); 
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);  
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }  
  Serial.println("LoRa Receiver Initialized");
}
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize){    
    Serial.print("Received packet: ");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    } 
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());  
  }
} 
