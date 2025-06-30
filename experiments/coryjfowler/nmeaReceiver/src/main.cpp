#include <Arduino.h>
#include <SPI.h>
#include <NMEA2000_CAN.h> // Will use MCP2515 driver under the hood
#include <N2kMessages.h>

#define SPI_CS 5
#define SPI_SCK 13
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_INT 4

// Optional, but helps for debugging
#define USE_MCP_CAN_CLOCK_SET 8 // 8 MHz crystal on MCP2515

// This callback is called for every incoming PGN
void HandleNMEA2000Msg(const tN2kMsg &msg)
{
    Serial.println(F("==================================="));
    Serial.printf("PGN: %lu | Priority: %u | Src: %u | Dest: %u | Len: %u\n",
                  msg.PGN, msg.Priority, msg.Source, msg.Destination, msg.DataLen);

    // Always dump raw data, even if we parse something
    Serial.print(F("Raw Data: "));
    for (int i = 0; i < msg.DataLen; i++)
    {
        if (msg.Data[i] < 0x10)
            Serial.print("0");
        Serial.print(msg.Data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Try to parse PGN 130312 (Temperature)
    if (msg.PGN == 130312)
    {
        unsigned char sid;
        unsigned char instance;
        tN2kTempSource source;
        double actualTemp;
        double setTemp;

        if (ParseN2kTemperature(msg, sid, instance, source, actualTemp, setTemp))
        {
            Serial.printf("✅ Parsed 130312 Temperature: %.2f °C (Instance: %u, Source: %u)\n",
                          KelvinToC(actualTemp), instance, source);
        }
        else
        {
            Serial.println(F("⚠️  Failed to parse 130312 PGN"));
        }
    }

    Serial.println(F("==================================="));
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("NMEA2000 Listener ready");

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  NMEA2000.SetProductInformation("000002", 100, "NMEA Listener", "1.0.0", "1.0.0");
  NMEA2000.SetDeviceInformation(54321, 130, 75, 2046);

  NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode, 22);  // 🔥 REQUIRED
  NMEA2000.SetForwardType(tNMEA2000::fwdt_Text);
  NMEA2000.SetForwardOwnMessages(true);
  NMEA2000.SetForwardStream(&Serial);
  NMEA2000.SetMsgHandler(HandleNMEA2000Msg);

  if (NMEA2000.Open()) {
    Serial.println("✅ NMEA2000 opened successfully.");
  } else {
    Serial.println("❌ NMEA2000 failed to open!");
  }
}


void loop()
{
    NMEA2000.ParseMessages();
    delay(5);
}