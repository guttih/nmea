# 🧪 Experiments: ESP32 + MCP2515 CAN Bus

This experiment uses two ESP32 boards, each connected to an MCP2515 CAN Bus module 
with a TJA1050 transceiver. One board acts as a sender, the other as a receiver, 
communicating over the CAN bus via SPI.


## 🔌Wiring Overview
Each ESP32 connects to its MCP2515 module using SPI. The receiver also uses the INT pin to detect incoming messages.

### Wiring table

| Esp32 Pin  | MCP2515 Pin | Description                       |
|------------|--------------|----------------------------------|
|  5V         | VCC         | Power supply (5V)                |
|  GND        | GND         | Ground                           |
|  G13        | SCK         | SPI Clock                        |
|  G23 (MOSI) | SI          | SPI Master Out Slave In          |
|  G19 (MISO) | SO          | SPI Master In Slave Out          |
|  G05        | CS          | SPI Chip Select                  |
| *G04        | INT         | Interrupt Pin (Only on Receiver) |
|     ----    |     ----    |           ----                   |             
|             | CAN L       | CAN Low  Line                    |
|             | CAN H       | CAN High Line                    |

And on each MCP2515 module we short the jumper J1 to connect the 120 Ω termination resistor across the CAN bus lines (CAN H and CAN L) resulting in a total resistance of 60 Ω over CAN H and CAN L when both modules are connected.

> **Note:** `G04` (INT) is **only connected on the receiver ESP32**, where it is used to detect and handle incoming CAN messages via interrupt.  
> The sender ESP32 does **not** need this connection.


### Wiring Diagram

```
 ╔═══════════════╗         ╔═══════════════════╗
 ║  - SENDER  -  ║         ║  MCP2515 CAN Bus  ║
 ║     ESP32     ║         ║       Module      ║
 ║            5V-╟─────────╢- VCC              ║
 ║               ║         ║                   ║
 ║     INT   G04-╟         ╢- INT       CAN H -╟────────┐
 ║     SCK   G13-╟─────────╢- SCK       CAN L -╟──────┐ │
 ║     MOSI  G23-╟─────────╢- SI               ║      │ │
 ║     MISO  G19-╟─────────╢- SO               ║      │ │
 ║     CS    G05-╟─────────╢- CS           J1 -║──┐   │ │
 ║           GND-╟─────────╢- GND          J1 -║──┘   │ │
 ╚═══════════════╝         ╚═══════════════════╝      │ │
                                                      │ │
                                                      │ │
 ╔═══════════════╗         ╔═══════════════════╗      │ │
 ║  - RECIVER -  ║         ║  MCP2515 CAN Bus  ║      │ │
 ║     ESP32     ║         ║       Module      ║      │ │
 ║           3V3-╟         ║                   ║      │ │
 ║            5V-╟─────────╢- VCC              ║      │ │
 ║               ║         ║                   ║      │ │
 ║     INT   G04-╟─────────╢- INT       CAN L -╟──────┘ │  
 ║     SCK   G13-╟─────────╢- SCK       CAN H -╟────────┘
 ║     MOSI  G23-╟─────────╢- SI               ║
 ║     MISO  G19-╟─────────╢- SO               ║
 ║     CS    G05-╟─────────╢- CS          *J1 -╟──┐   
 ║           GND-╟─────────╢- GND         *J1 -╟──┘  
 ╚═══════════════╝         ╚═══════════════════╝

 

```

 **J1** Jumper on the MCP2515 module that connects the 120 Ω termination resistor across the CAN bus lines (CAN H and CAN L). 

 ## 📎 Notes

- Both MCP2515 modules are powered via **5V**, even though the ESP32 operates at **3.3V logic** — the onboard **TJA1050 transceivers** are typically 3.3V logic compatible.
- With both J1 jumpers shorted and CAN_H/CAN_L connected between modules, the bus resistance should measure ~**60 Ω** — correct for two-node termination.
- Use **short twisted-pair wires** for the CAN_H and CAN_L lines between the modules to ensure reliable signal integrity and reduce noise.

 