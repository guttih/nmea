# Experiments


## Wiring Diagram

Connect two ESP32 boards to a MCP2515 CAN Bus module each, one as a sender and the other as a receiver. The wiring is shown below.

### Wiring table

| Esp32 Pin  | MCP2515 Pin | Description             |
|------------|-------------|-------------------------|
| 5V         | VCC         | Power supply (5V)       |
| GND        | GND         | Ground                  |
| G13        | SCK         | SPI Clock               |
| G23 (MOSI) | SI          | SPI Master Out Slave In |
| G19 (MISO) | SO          | SPI Master In Slave Out |
| G05        | CS          | SPI Chip Select         |
|    ----    |     ----    |           ----          |             
|            | CAN L       | CAN Low  Line           |
|            | CAN H       | CAN High Line           |

And on each MCP2515 module we short the jumper J1 to connect the 120 Ω termination resistor across the CAN bus lines (CAN H and CAN L) resulting in a total resistance of 60 Ω over CAN H and CAN L.


### Wiring Diagram

```
 ╔═══════════════╗         ╔═══════════════════╗
 ║  - SENDER  -  ║         ║  MCP2515 CAN Bus  ║
 ║     ESP32     ║         ║       Module      ║
 ║           3V3-╟         ║                   ║
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
 ║     INT   G04-╟─       ─╢- INT       CAN L -╟──────┘ │  
 ║     SCK   G13-╟─────────╢- SCK       CAN H -╟────────┘
 ║     MOSI  G23-╟─────────╢- SI               ║
 ║     MISO  G19-╟─────────╢- SO               ║
 ║     CS    G05-╟─────────╢- CS          *J1 -╟──┐   
 ║           GND-╟─────────╢- GND         *J1 -╟──┘  
 ╚═══════════════╝         ╚═══════════════════╝

 

```

 **J1** Jumper on the MCP2515 module that connects the 120 Ω termination resistor across the CAN bus lines (CAN H and CAN L). 
 