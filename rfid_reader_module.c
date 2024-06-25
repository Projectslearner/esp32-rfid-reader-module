/*
   Project name: ESP32 RFID Reader Module
   Modified Date: 25-06-2024
   Code by: Projectslearner
   Website: https://projectslearner.com/learn/esp32-rfid-reader
*/

#include <SPI.h>
#include <MFRC522.h>

// Define the pins for the RFID module
#define SS_PIN 5  // GPIO 5 for the Slave Select pin (SDA)
#define RST_PIN 27  // GPIO 27 for the Reset pin (RST)

// Create an instance of the MFRC522 class
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin();        // Initialize SPI bus
  rfid.PCD_Init();    // Initialize RFID module

  Serial.println("Place your RFID card/tag near the reader...");
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Print the UID of the card
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();

  // Halt the RFID card
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
