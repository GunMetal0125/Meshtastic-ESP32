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
