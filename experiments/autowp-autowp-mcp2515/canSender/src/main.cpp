#include <Arduino.h>

#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;

MCP2515 mcp2515(5);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("CAN Sender started\n");
    Serial.print("Setting up CAN message1");
    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 8;
    canMsg1.data[0] = 0x8E;
    canMsg1.data[1] = 0x87;
    canMsg1.data[2] = 0x32;
    canMsg1.data[3] = 0xFA;
    canMsg1.data[4] = 0x26;
    canMsg1.data[5] = 0x8E;
    canMsg1.data[6] = 0xBE;
    canMsg1.data[7] = 0x86;

    Serial.println(", AND CAN message2 ...");
    canMsg2.can_id = 0x036;
    canMsg2.can_dlc = 8;
    canMsg2.data[0] = 0x0E;
    canMsg2.data[1] = 0x00;
    canMsg2.data[2] = 0x00;
    canMsg2.data[3] = 0x08;
    canMsg2.data[4] = 0x01;
    canMsg2.data[5] = 0x00;
    canMsg2.data[6] = 0x00;
    canMsg2.data[7] = 0xA0;
    
    // Serial.println("SPI.begin()");                   SPI.begin();
       Serial.println("SPI.begin(13, 19, 23, 5)");SPI.begin(13, 19, 23, 5);  // SCK, MISO, MOSI, SS

    //   Serial.println("SPI.begin(2, 19, 23, 5);");
    //   SPI.begin(13, 19, 23, 5);
    Serial.println("mcp2515.reset();");
    mcp2515.reset();
    
    //   mcp2515.setBitrate(CAN_125KBPS);
    //   mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
    Serial.println("mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);");
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    Serial.println("mcp2515.setNormalMode();");
    mcp2515.setNormalMode();

    Serial.println("Example: Write to CAN");
}

void loop()
{
    mcp2515.sendMessage(&canMsg1);
    mcp2515.sendMessage(&canMsg2);

    Serial.println("Messages sent");

    delay(100);
}