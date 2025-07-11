#include <Arduino.h>

#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(5);

void setup()
{
    Serial.begin(115200);
    Serial.println("CAN Receiver started\n");
    // Serial.println("SPI.begin()");                 SPI.begin();
    Serial.println("SPI.begin(13, 19, 23, 5)");SPI.begin(13, 19, 23, 5);  // SCK, MISO, MOSI, SS
    //   mcp2515.setBitrate(CAN_125KBPS);
    //  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
    Serial.println("mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);");
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    Serial.println("mcp2515.setNormalMode();");
    mcp2515.setNormalMode();

    Serial.println("------- CAN Read ----------");
    Serial.println("ID  DLC   DATA");
}

void loop()
{
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
    {
        Serial.print(canMsg.can_id, HEX); // print ID
        Serial.print(" ");
        Serial.print(canMsg.can_dlc, HEX); // print DLC
        Serial.print(" ");

        for (int i = 0; i < canMsg.can_dlc; i++)
        { // print the data
            Serial.print(canMsg.data[i], HEX);
            Serial.print(" ");
        }

        Serial.println();
    }
}
