# Smart Home Automation System

> Arduino-based home automation with Bluetooth app, IR remote, and relay control

## Features
- Control 8 home appliances independently
- Bluetooth smartphone app control
- IR remote control
- Manual toggle support
- Real-time status feedback via Serial

## Hardware
| Component | Purpose |
|-----------|---------|
| Arduino Mega 2560 | Main controller |
| HC-05 Bluetooth | Smartphone control |
| IR Receiver (VS1838B) | Remote control |
| 8-Channel Relay Module | Appliance switching |
| 5V Power Supply | System power |

## Controlled Appliances
1. Living Room Light
2. Bedroom Light
3. Kitchen Light
4. Bathroom Light
5. Fan
6. TV
7. AC
8. Gate Lock

## Bluetooth App
Use MIT App Inventor or Bluetooth Controller app. Send characters:
- 1-8: Toggle individual appliance
- A: All ON
- Z: All OFF

## Author
**Mothi Charan Naik Desavath** - Embedded Systems Engineer
NITK-STEP Internship Project