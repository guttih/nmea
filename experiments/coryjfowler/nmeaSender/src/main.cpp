#include <Arduino.h>
#include <SPI.h>
// #include <NMEA2000_CAN.h>
// #include <N2kMessages.h>

// // Use `NMEA2000_mcp.h` for MCP2515
// #include <NMEA2000_mcp.h>

// Example pinout
#define TEMPERATURE_PIN 14
#define SPI_INT 4
#define N2k_CAN_INT_PIN 4
#define SPI_CS 5
#define N2k_SPI_CS_PIN 5
#define SPI_SCK 13
#define SPI_MOSI 23
#define SPI_MISO 19
#define USE_MCP_CAN_CLOCK_SET 8 // if your MCP2515 crystal is 8 MHz (seems like it is)

// #define ESP32_CAN_TX_PIN GPIO_NUM_16 // If you use ESP32 and do not have TX on default IO 16, uncomment this and and modify definition to match your CAN TX pin.
// #define ESP32_CAN_RX_PIN GPIO_NUM_17 // If you use ESP32 and do not have RX on default IO 4, uncomment this and and modify definition to match your CAN TX pin.
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NMEA2000_CAN.h> // Automatically chooses MCP2515 driver with above pins
#include <N2kMessages.h>
// DS18B20 onewire bus pin
const int oneWireBus = TEMPERATURE_PIN;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(115200);
    Serial.println("NMEA2000 tempreature sender");
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);
    sensors.begin();
    sensors.setWaitForConversion(false);
    Serial.print("temperature :");
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print(temperatureC);
    Serial.println(" °C");
    // NMEA2000 device initialization
    NMEA2000.SetProductInformation("000001", 100, "Temp Sensor Example", "1.0.0", "1.0.0");
    NMEA2000.SetDeviceInformation(12345, 130, 75, 2040);
    //   NMEA2000.SetMode(tNMEA2000::N2km_NodeOnly, 22);
    NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode, 22);
    // (Optional: forward N2K messages to Serial for debugging)
    NMEA2000.SetForwardStream(&Serial);
    NMEA2000.SetForwardType(tNMEA2000::fwdt_Text);
    NMEA2000.SetForwardOwnMessages(true);
    bool ok = NMEA2000.Open();
    if (ok)
    {
        Serial.println("✅ NMEA2000.Open() success!");
    }
    else
    {
        Serial.println("❌ NMEA2000.Open() failed!");
    }
}

unsigned long lastTempRequest = 0;
float lastTempC = DEVICE_DISCONNECTED_C;
const unsigned long TEMP_INTERVAL_MS = 1000;
bool tempRequested = false;
bool sendSuccess = false;

bool readSensorAndUpdate(float &newTempOut)
{
    unsigned long now = millis();

    // Step 1: Trigger temp read every interval
    if (!tempRequested && now - lastTempRequest >= TEMP_INTERVAL_MS)
    {
        sensors.requestTemperatures();
        tempRequested = true;
        lastTempRequest = now;
        return false; // Not ready yet
    }

    // Step 2: Check if conversion is done
    if (tempRequested && sensors.isConversionComplete())
    {
        tempRequested = false;
        float tempC = sensors.getTempCByIndex(0);
        if (tempC != DEVICE_DISCONNECTED_C)
        {
            lastTempC = tempC;
            newTempOut = tempC;
            return true;
        }
    }

    return false; // No update ready
}

void loop()
{
    float tempC;
    if (readSensorAndUpdate(tempC))
    {
        double tempK = CToKelvin(tempC);
        tN2kMsg msg;
        SetN2kTemperature(msg, 1, 1, N2kts_MainCabinTemperature, tempK, N2kDoubleNA);
        sendSuccess = NMEA2000.SendMsg(msg);
        Serial.printf("temp: %.2f°C ", tempC);
        if (sendSuccess)
            Serial.println(" sent.");
        else
            Serial.println(" ❌ sending failed!");
    }

    NMEA2000.ParseMessages();
}