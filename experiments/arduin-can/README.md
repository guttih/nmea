# Experiments


## Wiring Diagram

Connect two ESP32 boards to a SN65HVD230 CAN Bus module each, one as a sender and the other as a receiver. The wiring is shown below.

### Wiring table

| ESP32 Pin | SN65HVD230 Pin | Description             |
|-----------|----------------|-------------------------|
| 3.3V      | 3.3V           | Power supply            |
| GND       | GND            | Ground                  |
| GPIO5     | TX             | CAN TX (from ESP32)     |
| GPIO4     | RX             | CAN RX (to ESP32)       |
| —         | CANH           | Connect to other CANH   |
| —         | CANL           | Connect to other CANL   |


### Wiring Diagram

```
 ╔═══════════════╗         ╔═══════════════════╗
 ║  - SENDER  -  ║         ║     SN65HVD230    ║
 ║     ESP32     ║         ║   Can Bus module  ║
 ║               ║         ║                   ║
 ║          3V3 -╟─────────╢- VCC              ║
 ║          GND -╟─────────╢- GND              ║
 ║          G04 -╟─────────╢- RX               ║
 ║          G05 -╟─────────╢- TX               ║
 ║               ║         ║                   ║
 ║               ║         ║            CAN H -╟────────┐
 ║               ║         ║            CAN L -╟──────┐ │
 ╚═══════════════╝         ╚═══════════════════╝      │ │
                                                      │ │
                                                      │ │
 ╔═══════════════╗         ╔═══════════════════╗      │ │
 ║  - RECIVER -  ║         ║     SN65HVD230    ║      │ │
 ║     ESP32     ║         ║   Can Bus module  ║      │ │
 ║               ║         ║                   ║      │ │
 ║               ║         ║            CAN L -╟──────┘ │
 ║               ║         ║            CAN H -╟────────┘
 ║          3V3 -╟─────────╢- VCC              ║
 ║          GND -╟─────────╢- GND              ║
 ║          G04 -╟─────────╢- RX               ║
 ║          G05 -╟─────────╢- TX               ║
 ║               ║         ║                   ║
 ╚═══════════════╝         ╚═══════════════════╝
```

## Library to use

Simple _Send/recieve Hello world_ using the [sandeepmistry/CAN](https://registry.platformio.org/libraries/sandeepmistry/CAN) library. 
 
 library is used for CAN communication. It can be installed via PlatformIO by adding the following line to your `platformio.ini` file:

```ini
lib_deps = sandeepmistry/CAN@^0.3.1
``` 