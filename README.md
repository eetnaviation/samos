# SAMOS - Simple Appliance Monitoring Operating System
REOTEK Simple Appliance Monitoring OS (SAMOS) is a simple firmware for Arduino microcontrollers
to monitor simple appliances through the GPIO pins. All transmissions from the SAMOS unit are
in serial.

## Pinouts

### SAMOS Monitoring Serial (SOMMS - SAMOS Online Monitoring Messaging System) interface pinout
Arduino UNO:
- D13 , D12

### SAMOS For Advanced REOTEK Lifts (SORAL - SAMOS Online management for Reotek Advanced Lifts) interface pinout
Arduino UNO: (Refer to SOMMS pinout for monitoring pinout.)
- D7 - Safety
- D6 - Floor 1
- D5 - Floor 2
- D4 - Floor 3
- D3 - Keyswitch MODE 2
- D2 - Keyswitch MODE 1

## Powering the SAMOS unit
There are 3 ways to power an Arduino UNO based SAMOS unit.
### Barrel jack
Refer to Arduino official specifications for barrel jack usage.
### USB-B Port
Use a standard USB-B cable.
### VIN Pin
Apply 5V DC to the VIN (Voltage INput) pin. Connect the GND to GND.
