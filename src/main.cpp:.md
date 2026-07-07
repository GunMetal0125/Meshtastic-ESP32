#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// SX1262 Pin Definitions
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS     5
#define LORA_RST   14
#define LORA_DIO1  33
#define LORA_BUSY  32

// LoRa frequency (change if needed)
#define LORA_FREQ  915E6   // 915 MHz for US

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== LoRa Messenger Starting ===");

  // SPI setup
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  // LoRa setup
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO1);

  Serial.println("Initializing LoRa...");
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed! Check wiring.");
    while (true);
  }

  Serial.println("LoRa init OK!");
  Serial.println("Device ready to send and receive messages.");
}

void loop() {
  // Send a message every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();

    Serial.println("Sending message...");
    LoRa.beginPacket();
    LoRa.print("Hello from ESP32 LoRa Messenger!");
    LoRa.endPacket();
  }

  // Receive messages
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received: ");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println();
  }
}
