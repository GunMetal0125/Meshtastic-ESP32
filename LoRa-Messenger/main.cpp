#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// SX1262 Pin Definitions
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS     5
#define LORA_RST   14
#define LORA_DIO1  33
#define LORA_BUSY  32

#define LORA_FREQ  915E6

void setup() {
  Serial.begin(115200);
  delay(1000);

  // OLED INIT
  Wire.begin(21, 22);  // SDA=21, SCL=22
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed!");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("LoRa Messenger");
  display.println("Initializing...");
  display.display();

  // SPI + LoRa INIT
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO1);

  if (!LoRa.begin(LORA_FREQ)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("LoRa FAILED!");
    display.display();
    while (true);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LoRa Ready!");
  display.println("Listening...");
  display.display();
}

void loop() {
  // Send message every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sending...");
    display.display();

    LoRa.beginPacket();
    LoRa.print("Hello from ESP32 LoRa Messenger!");
    LoRa.endPacket();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sent!");
    display.println("Listening...");
    display.display();
  }

  // Receive messages
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";

    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.print("Received: ");
    Serial.println(incoming);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Received:");
    display.println(incoming);
    display.display();
  }
}
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// SX1262 Pin Definitions
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS     5
#define LORA_RST   14
#define LORA_DIO1  33
#define LORA_BUSY  32

#define LORA_FREQ  915E6

void setup() {
  Serial.begin(115200);
  delay(1000);

  // OLED INIT
  Wire.begin(21, 22);  // SDA=21, SCL=22
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed!");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("LoRa Messenger");
  display.println("Initializing...");
  display.display();

  // SPI + LoRa INIT
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO1);

  if (!LoRa.begin(LORA_FREQ)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("LoRa FAILED!");
    display.display();
    while (true);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LoRa Ready!");
  display.println("Listening...");
  display.display();
}

void loop() {
  // Send message every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sending...");
    display.display();

    LoRa.beginPacket();
    LoRa.print("Hello from ESP32 LoRa Messenger!");
    LoRa.endPacket();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sent!");
    display.println("Listening...");
    display.display();
  }

  // Receive messages
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";

    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.print("Received: ");
    Serial.println(incoming);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Received:");
    display.println(incoming);
    display.display();
  }
}
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPSPlus.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// GPS
TinyGPSPlus gps;
HardwareSerial GPSserial(1);  // UART1

// SX1262 Pins
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS     5
#define LORA_RST   14
#define LORA_DIO1  33
#define LORA_BUSY  32

#define LORA_FREQ  915E6

void showText(const String &text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // OLED INIT
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  showText("LoRa Messenger\nGPS Init...");

  // GPS INIT
  GPSserial.begin(9600, SERIAL_8N1, 16, 17);
  showText("GPS Ready");

  // LoRa INIT
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO1);

  if (!LoRa.begin(LORA_FREQ)) {
    showText("LoRa FAILED!");
    while (true);
  }

  showText("LoRa Ready\nListening...");
}

void loop() {
  // Read GPS data
  while (GPSserial.available()) {
    gps.encode(GPSserial.read());
  }

  // Send GPS every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();

    if (gps.location.isValid()) {
      double lat = gps.location.lat();
      double lon = gps.location.lng();

      String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);

      showText("Sending GPS...\n" + msg);

      LoRa.beginPacket();
      LoRa.print(msg);
      LoRa.endPacket();

      showText("Sent!\nListening...");
    } else {
      showText("GPS Invalid\nWaiting...");
    }
  }

  // Receive LoRa packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.println("Received: " + incoming);
    showText("Received:\n" + incoming);
  }
}
// Simple XOR "encryption" with shared key
const char *SHARED_KEY = "MySecretKey123";  // change this, same on all devices

String encrypt(const String &plain) {
  String out = plain;
  int keyLen = strlen(SHARED_KEY);
  for (int i = 0; i < out.length(); i++) {
    out[i] = out[i] ^ SHARED_KEY[i % keyLen];
  }
  return out;
}

String decrypt(const String &cipher) {
  // XOR again with same key to get original
  return encrypt(cipher);
}
String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);
String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);
String enc = encrypt(msg);

LoRa.beginPacket();
LoRa.print(enc);
LoRa.endPacket();
int packetSize = LoRa.parsePacket();
if (packetSize) {
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  Serial.println("Received: " + incoming);
  showText("Received:\n" + incoming);
}
int packetSize = LoRa.parsePacket();
if (packetSize) {
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  String plain = decrypt(incoming);

  Serial.println("Received (enc): " + incoming);
  Serial.println("Decrypted: " + plain);
  showText("Received:\n" + plain);
}
#include <Crypto.h>
#include <AES.h>
#include <string.h>

AES128 aes;

// 16‑byte AES key (must match on all devices)
uint8_t aesKey[16] = {
  'M','y','S','e','c','r','e','t','K','e','y','1','2','3','4'
};

// AES needs 16‑byte blocks
String aesEncrypt(const String &plain) {
  int len = plain.length();
  int paddedLen = ((len + 15) / 16) * 16;

  uint8_t input[paddedLen];
  uint8_t output[paddedLen];

  memset(input, 0, paddedLen);
  memcpy(input, plain.c_str(), len);

  for (int i = 0; i < paddedLen; i += 16) {
    aes.encryptBlock(output + i, input + i, aesKey);
  }

  String encoded = "";
  for (int i = 0; i < paddedLen; i++) {
    encoded += (char)output[i];
  }

  return encoded;
}

String aesDecrypt(const String &cipher) {
  int len = cipher.length();
  uint8_t input[len];
  uint8_t output[len];

  memcpy(input, cipher.c_str(), len);

  for (int i = 0; i < len; i += 16) {
    aes.decryptBlock(output + i, input + i, aesKey);
  }

  String decoded = "";
  for (int i = 0; i < len; i++) {
    decoded += (char)output[i];
  }

  return decoded;
}
String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);
String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);
String enc = aesEncrypt(msg);

LoRa.beginPacket();
LoRa.print(enc);
LoRa.endPacket();
String incoming = "";
String incoming = "";
while (LoRa.available()) {
  incoming += (char)LoRa.read();
}

String plain = aesDecrypt(incoming);

Serial.println("Received (AES): " + incoming);
Serial.println("Decrypted: " + plain);
showText("Received:\n" + plain);
NODE:12345|ID:9981|TTL:3|GPS:41.123456,-73.543210
#include <map>

String NODE_ID = String((uint32_t)ESP.getEfuseMac());  // unique per ESP32
std::map<String, bool> seenPackets;  // store packet IDs
String buildPacket(const String &payload) {
  String packetID = String(random(1000, 999999));
  int ttl = 3;  // number of hops allowed

  String packet = "NODE:" + NODE_ID +
                  "|ID:" + packetID +
                  "|TTL:" + String(ttl) +
                  "|" + payload;

  return packet;
}
struct MeshPacket {
  String node;
  String id;
  int ttl;
  String payload;
};

MeshPacket parsePacket(const String &raw) {
  MeshPacket p;

  int n1 = raw.indexOf("NODE:");
  int i1 = raw.indexOf("|ID:");
  int t1 = raw.indexOf("|TTL:");
  int p1 = raw.indexOf("|", t1 + 5);

  p.node = raw.substring(n1 + 5, i1);
  p.id = raw.substring(i1 + 4, t1);
  p.ttl = raw.substring(t1 + 5, p1).toInt();
  p.payload = raw.substring(p1 + 1);

  return p;
}
void forwardPacket(const MeshPacket &p) {
  if (p.ttl <= 0) return;

  MeshPacket newP = p;
  newP.ttl--;

  String out = "NODE:" + newP.node +
               "|ID:" + newP.id +
               "|TTL:" + String(newP.ttl) +
               "|" + newP.payload;

  LoRa.beginPacket();
  LoRa.print(out);
  LoRa.endPacket();
}
String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6);
String packet = buildPacket(msg);
String enc = aesEncrypt(packet);

LoRa.beginPacket();
LoRa.print(enc);
LoRa.endPacket();
int packetSize = LoRa.parsePacket();
if (packetSize) {
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  String plain = aesDecrypt(incoming);
  MeshPacket p = parsePacket(plain);

  // Ignore duplicates
  if (seenPackets[p.id]) return;
  seenPackets[p.id] = true;

  // Display payload
  Serial.println("Mesh RX: " + p.payload);
  showText("Mesh RX:\n" + p.payload);

  // Forward packet to next node
  forwardPacket(p);
}
ACK:<packetID>
std::map<String, bool> ackReceived;   // packetID → true/false
std::map<String, unsigned long> ackTimeout;  // packetID → timestamp
String buildAck(const String &packetID) {
  return "ACK:" + packetID;
}
String buildPacket(const String &payload, const String &destNode) {
  String packetID = String(random(1000, 999999));
  int ttl = 3;

  String packet = "TYPE:DATA" 
                  "|SRC:" + NODE_ID +
                  "|DEST:" + destNode +
                  "|ID:" + packetID +
                  "|TTL:" + String(ttl) +
                  "|" + payload;

  // Track ACK timeout
  ackReceived[packetID] = false;
  ackTimeout[packetID] = millis() + 5000;  // 5 seconds

  return packet;
}
struct MeshPacket {
  String type;
  String src;
  String dest;
  String id;
  int ttl;
  String payload;
};

MeshPacket parsePacket(const String &raw) {
  MeshPacket p;

  int t1 = raw.indexOf("TYPE:");
  int s1 = raw.indexOf("|SRC:");
  int d1 = raw.indexOf("|DEST:");
  int i1 = raw.indexOf("|ID:");
  int ttl1 = raw.indexOf("|TTL:");
  int p1 = raw.indexOf("|", ttl1 + 5);

  p.type = raw.substring(t1 + 5, s1);
  p.src = raw.substring(s1 + 5, d1);
  p.dest = raw.substring(d1 + 6, i1);
  p.id = raw.substring(i1 + 4, ttl1);
  p.ttl = raw.substring(ttl1 + 5, p1).toInt();
  p.payload = raw.substring(p1 + 1);

  return p;
}
void sendAck(const String &packetID, const String &destNode) {
  String ackPacket = "TYPE:ACK"
                     "|SRC:" + NODE_ID +
                     "|DEST:" + destNode +
                     "|ID:" + packetID +
                     "|TTL:3"
                     "|OK";

  String enc = aesEncrypt(ackPacket);

  LoRa.beginPacket();
  LoRa.print(enc);
  LoRa.endPacket();
}
int packetSize = LoRa.parsePacket();
if (packetSize) {
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  String plain = aesDecrypt(incoming);
  MeshPacket p = parsePacket(plain);

  // Ignore duplicates
  if (seenPackets[p.id]) return;
  seenPackets[p.id] = true;

  // If ACK packet
  if (p.type == "ACK") {
    ackReceived[p.id] = true;
    showText("ACK received\nID:" + p.id);
    return;
  }

  // If DATA packet addressed to me → process + ACK
  if (p.dest == NODE_ID) {
    showText("RX:\n" + p.payload);
    sendAck(p.id, p.src);
  }

  // Forward packet through mesh
  forwardPacket(p);
}
for (auto &entry : ackTimeout) {
  String packetID = entry.first;
  unsigned long timeout = entry.second;

  if (!ackReceived[packetID] && millis() > timeout) {
    showText("Retrying...\nID:" + packetID);

    // Re-send last message (simple version)
    // You can store full packets if you want more advanced retries
    // For now, just notify user
    ackTimeout[packetID] = millis() + 5000;
  }
}
Battery + → R1 → ADC pin → R2 → GND
#define BATTERY_PIN 34   // ADC pin

float readBatteryVoltage() {
  int raw = analogRead(BATTERY_PIN);
  float voltage = (raw / 4095.0) * 3.3;  // ADC → voltage
  voltage *= 2.0;  // undo voltage divider
  return voltage;
}

int batteryPercent(float v) {
  // Simple LiPo curve
  if (v >= 4.20) return 100;
  if (v >= 4.00) return 90;
  if (v >= 3.85) return 75;
  if (v >= 3.70) return 50;
  if (v >= 3.55) return 25;
  if (v >= 3.40) return 10;
  return 0;
}
analogReadResolution(12);
analogSetAttenuation(ADC_11db);  // allows up to ~3.6V input
float v = readBatteryVoltage();
int pct = batteryPercent(v);

display.setCursor(0, 50);
display.print("Bat: ");
display.print(v, 2);
display.print("V ");
display.print(pct);
display.println("%");
display.display();
float v = readBatteryVoltage();
int pct = batteryPercent(v);

String msg = "GPS:" + String(lat, 6) + "," + String(lon, 6) +
             "|BAT:" + String(pct) + "%";
if (p.payload.indexOf("BAT:") != -1) {
  int idx = p.payload.indexOf("BAT:");
  String bat = p.payload.substring(idx + 4);
  Serial.println("Battery from node: " + bat);
}
if (pct <= 10) {
  showText("LOW BATTERY!\n" + String(pct) + "%");
}
