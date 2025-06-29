// #### 🔌 ESP32 Wiring Table

// | ESP32 Pin | SN65HVD230 Pin | Description             |
// |-----------|----------------|-------------------------|
// | 3.3V      | 3.3V           | Power supply            |
// | GND       | GND            | Ground                  |
// | GPIO5     | TX             | CAN TX (from ESP32)     |
// | GPIO4     | RX             | CAN RX (to ESP32)       |
// | —         | CANH           | Connect to other CANH   |
// | —         | CANL           | Connect to other CANL   |

#include <Arduino.h>
// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);
}

