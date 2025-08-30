#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>

const char* ssid = "ssid-mreze";
const char* password = "sifra-mreze";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "myhome/lora";

WiFiClient espClient;
PubSubClient client(espClient);

#define LORA_SCK 5
#define LORA_MISO 18
#define LORA_MOSI 23
#define LORA_SS 17
#define LORA_RST 14
#define LORA_DIO0 26

void callback(char* topic, byte* payload, unsigned int length) {
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Pokušavam MQTT konekciju...");
    if (client.connect("ESP32Gateway")) {
      Serial.println("spojen na MQTT broker!");
    } else {
      Serial.print("neuspješno, rc=");
      Serial.print(client.state());
      Serial.println(" pokušavam ponovo za 5 sekundi");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Pokrećem ESP32 LoRa gateway...");

  WiFi.begin(ssid, password);
  Serial.print("Spajam se na WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi spojen!");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if(!LoRa.begin(868E6)) {
    Serial.println("LoRa inicijalizacija neuspješna!");
    while(1);
  }
  Serial.println("LoRa inicijalizirana!");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int packetSize = LoRa.parsePacket();
  if(packetSize) {
    String message = "";
    while(LoRa.available()) {
      message += (char)LoRa.read();
    }
    Serial.print("Primljeno: ");
    Serial.println(message);

    if(client.publish(mqtt_topic, message.c_str())) {
      Serial.println("Poruka poslana na MQTT");
    } else {
      Serial.println("Greška pri slanju na MQTT");
    }
  }
  delay(100);
}
