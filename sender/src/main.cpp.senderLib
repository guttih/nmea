//Sender - from LIB
#include <mcp_can.h>
#include <SPI.h>

// Your wiring:
#define CAN_CS     10  // MCP2515 CS (GPIO10)
#define CAN_INT     4  // MCP2515 INT (GPIO4)
#define SPI_MOSI   11  // MCP2515 SI
#define SPI_MISO   13  // MCP2515 SO
#define SPI_SCK    12  // MCP2515 SCK

MCP_CAN CAN0(CAN_CS);  // Set CS pin for MCP_CAN

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println("CAN Sender starting...");

  // Use custom SPI pinout
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, CAN_CS);

  // Initialize MCP2515 at 8MHz crystal with 500kbps
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else {
    Serial.println("Error Initializing MCP2515...");
    while (1);
  }

  CAN0.setMode(MCP_NORMAL);   // Normal mode (not loopback)
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  // Send data: ID = 0x100, Standard frame, 8 bytes
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);
}
