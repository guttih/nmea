#include <Arduino.h>
#include <SPI.h>
// #include <NMEA2000_CAN.h>
// #include <N2kMessages.h>

// // Use `NMEA2000_mcp.h` for MCP2515
// #include <NMEA2000_mcp.h>

// Example pinout
#define TEMPERATURE_PIN 14
#define SPI_INT          4
#define N2k_CAN_INT_PIN  4
#define SPI_CS           5
#define N2k_SPI_CS_PIN   5
#define SPI_SCK         13
#define SPI_MOSI        23
#define SPI_MISO        19
#define USE_MCP_CAN_CLOCK_SET 8  // if your MCP2515 crystal is 8 MHz (seems like it is)

//#define ESP32_CAN_TX_PIN GPIO_NUM_16 // If you use ESP32 and do not have TX on default IO 16, uncomment this and and modify definition to match your CAN TX pin.
//#define ESP32_CAN_RX_PIN GPIO_NUM_17 // If you use ESP32 and do not have RX on default IO 4, uncomment this and and modify definition to match your CAN TX pin.
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NMEA2000_CAN.h>     // Automatically chooses MCP2515 driver with above pins
#include <N2kMessages.h>
// DS18B20 onewire bus pin
const int oneWireBus = TEMPERATURE_PIN;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Serial.println("NMEA2000 tempreature sender");
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);  
  sensors.begin();
  Serial.print("temperature :");
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0); Serial.print(temperatureC);
  Serial.println(" °C");
  // NMEA2000 device initialization
  NMEA2000.SetProductInformation("000001", 100, "Temp Sensor Example", "1.0.0", "1.0.0");
  NMEA2000.SetDeviceInformation(12345, 130, 75, 2040);
  NMEA2000.SetMode(tNMEA2000::N2km_NodeOnly, 22);
  // (Optional: forward N2K messages to Serial for debugging)
  NMEA2000.SetForwardStream(&Serial);
  NMEA2000.SetForwardType(tNMEA2000::fwdt_Text);
  NMEA2000.SetForwardOwnMessages(true);
  NMEA2000.Open();
}

void loop() {
  // Read temperature in Celsius
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if (tempC != DEVICE_DISCONNECTED_C) {  // valid reading
    // Convert to Kelvin and send NMEA2000 temperature message
    double tempK = CToKelvin(tempC);
    tN2kMsg msg;
    SetN2kTemperature(msg, 1, 1, N2kts_MainCabinTemperature, tempK);
    NMEA2000.SendMsg(msg);
    Serial.printf("Sent temp: %.2f C (%.2f K)\n", tempC, tempK);
  } else {
    Serial.println("Temperature sensor error!");
  }
  NMEA2000.ParseMessages();  // handle N2K background tasks
  delay(1000);
}