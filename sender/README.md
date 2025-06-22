# Sender

Sending temprature values over can bus using the nmea2000 protocol.

## Hardware

- **Microcontroller** Esp32-s3-n8r8 
    - [Esp32-s3-n8r8 in gpart](https://parts.guttih.com/parts/view/67ebe956b6aaa30612227ec6)
- **Sensor** DS18B20 Stainless Steel Temperature Sensor
    - [DS18B20 sensor in gpart](https://parts.guttih.com/parts/view/5bfc0d3c9d562468dda61c82)
- **Transceiver module**  MCP2515 CAN Bus Modules with TJA1050 Receiver - SPI Protocol
    - [MCP2515 module in gpart](https://parts.guttih.com/parts/view/684b0fa8ce2439071290c1c8)


## External Libraries

Using libraries fro. [ttlappalainen](https://github.com/ttlappalainen)
 - [NMEA2000](https://github.com/ttlappalainen/NMEA2000)
 - [CAN_BUS_Shield](https://github.com/ttlappalainen/CAN_BUS_Shield)
 - [NMEA2000_mcp](https://github.com/ttlappalainen/NMEA2000_mcp)


## Wiring

###  Sensor

__Wiring diagram__
```
 ╔═══════════╗                        ╔═══════════╗
 ║   ESP32   ║                        ║  DS18B20  ║
 ║           ║                        ║  Sensor   ║
 ║           ║                        ║           ║
 ║    GND   -╟────────────────────────╢-  Green  -║
 ║    3V3   -╟──┬─────────────────────╢-   Red   -║
 ║           ║  │  ╔═══════════╗      ║           ║
 ║           ║  │  ║-Resistor -║      ║           ║
 ║           ║  └──╢-  4.7kΩ  -╟──┬───╢- Yellow  -║
 ║           ║     ╚═══════════╝  │   ╚═══════════╝
 ║    G21   -╟────────────────────┘
 ╚═══════════╝
```

### Can Bus Module

The CAN Bus module requires a 5 V power supply, which can be provided by the ESP32. It communicates with the ESP32 over SPI, but when powered at 5 V, its GPIO lines (MISO and INT) may output 5 V—too high for the ESP32’s 3.3 V inputs.

To protect your ESP32, you need a TXB0102 level shifter between the ESP32 and the MCP2515 module. The TXB0102 is a bidirectional level translator with an Output Enable (OE) pin that must be held high (to 3.3 V) in order to enable signal conversion. When OE is low or floating, the TXB0102 goes into a high-impedance state and no signals pass through. 

__Wiring diagram__


```

                    ┌────────────────────────┐
                    │                        │     
 ╔══════════════╗   │   ╔════════════════╗   │   ╔═══════════════════╗
 ║   ESP32      ║   │   ║    TXB0102     ║   │   ║  MCP2515 CAN Bus  ║
 ║              ║   │   ║      LLC       ║   │   ║       Module      ║
 ║           5V-╟───┘   ║                ║   │   ║                   ║
 ║          3V3-╟───┬───╢-VA         VB -╟───┴───╢- VCC              ║
 ║              ║   └───╢-OE             ║       ║                   ║
 ║     INT  G04-╟───────╢-A4         B4 -╟───────╢- INT       CAN H -║
 ║     SCK  G12-╟───────╢-A5         B5 -╟───────╢- SCK       CAN L -║
 ║     MOSI G11-╟───────╢-A6         B7 -╟───────╢- SI               ║
 ║     MISO G13-╟───────╢-A7         B7 -╟───────╢- SO               ║
 ║     CS   G10-╟───────╢-A8         B8 -╟───────╢- CS               ║
 ║          GND-╟───┐   ║           GND -╟───┬───╢- GND              ║
 ╚══════════════╝   │   ╚════════════════╝   │   ╚═══════════════════╝
                    │                        │
                    └────────────────────────┘
   

```

Mesuring resistance of the CAN bus when shorting the Jumper J1 on the MCP2515 module.

Jumper J1 on the MCP2515 

| Sender shorted  | Reciver shorted  | Mesured sender CAN | Mesured reciver CAN |
| --------------: | :--------------  | :------------------| :-------------------|
|  false           | false           |  44.3 Ω            |  44.3 Ω             |
|  true            | false           | 119.4 Ω            | 120.1 Ω             |
|  false           | true            | 121.0 Ω            | 119.7 Ω             |
|  true            | true            |  60.4 Ω            |  60.3 Ω             |

When testing in the lab, the best results were achieved with the jumper J1 shorted on the sender and not shorted on the receiver. This resulted in a resistance of 60.4 Ω on the sender and 60.3 Ω on the receiver.

