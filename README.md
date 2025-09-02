# LoRa ESP32 + MQTT Sistem

## 📌 Opis projekta
Ovaj projekat implementira sistem za prenos podataka pomoću **LoRa tehnologije** i **ESP32 mikrokontrolera**, sa integracijom ka **MQTT brokeru** putem WiFi mreže.  
Sistem omogućava povezivanje više čvorova (senzora) koji šalju podatke preko LoRa linka, dok gateway uređaj te podatke prosleđuje MQTT serveru radi centralizovanog prijema i obrade.  

---

## 🔹 Tok razvoja projekta

### 1. Istraživanje i analiza
- Ispitivane su mogućnosti korišćenja LoRa modula sa ESP32 mikrokontrolerom.  
- Upoređene biblioteke: **Arduino LoRa**, **PubSubClient** (za MQTT), **SPI komunikacija**.  
- Analizirana uloga ESP32 kao LoRa čvora i kao gateway-a povezanog na MQTT broker.  

### 2. Pisanje i priprema koda
Pripremljeni su odvojeni fajlovi za pojedinačne komponente sistema:
- **Sender (čvor)** – slanje poruka preko LoRa modula  
- **Receiver** – prijem poruka i ispis na serijski monitor  
- **Gateway** – prijem LoRa poruka i prosleđivanje na MQTT broker putem WiFi mreže  
- **Node** – dodatni čvor sa telemetrijom  

Kod je razvijan modularno kako bi se greške lakše uočavale i ispravljale.  

### 3. Povezivanje hardverskih komponenti
- ESP32 moduli povezani su sa **RFM95 LoRa modulima** pomoću **lemnih provodnika**.  
- Korišćen je ESP32 base board za stabilno napajanje i lako programiranje preko USB-a.  
- Posebna pažnja posvećena je povezivanju:
  - SPI pinova (**MOSI, MISO, SCK, CS**)  
  - kontrolnih pinova (**RST, DIO0**)  

### 4. Testiranje funkcionalnosti
- Testirana osnovna komunikacija između **Sender** i **Receiver** uređaja.  
- Uveden gateway povezan na MQTT broker (**HiveMQ**).  
- Proverena komunikacija u lancu:  
  **LoRa čvor → Gateway → MQTT server**  
- Izvršeno stres testiranje sa više paketa i merenjem **RSSI** vrednosti.  

### 5. Iteracije i optimizacija
- Prilagođena učestalost slanja paketa i format poruka  
- Dodata serijska dijagnostika radi lakšeg otklanjanja grešaka  
- Testirana stabilnost WiFi konekcije i komunikacije sa MQTT brokerom  

### 6. Finalizacija sistema
- Više čvorova uspešno šalje podatke na centralni MQTT server preko gateway-a  
- Dokumentovana hardverska šema i funkcionalna podela koda  

---

## ⚙️ Hardver
- ESP32 razvojne ploče  
- RFM95 LoRa moduli (868 MHz)  
- Lemljeni provodnici za povezivanje  
- ESP32 Base board  

---

## 🛠️ Softver
- Arduino IDE  
- Biblioteke:
  - [Arduino LoRa](https://github.com/sandeepmistry/arduino-LoRa)  
  - [PubSubClient](https://pubsubclient.knolleary.net/)  

---

## 🚀 Pokretanje
1. Klonirati repo:  
   ```bash
   git clone https://github.com/username/lorawan-esp32-mqtt.git
