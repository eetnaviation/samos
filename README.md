# SAMOS - Simple Appliance Monitoring Operating System
Simple Appliance Monitoring OS (SAMOS) is a simple firmware for Arduino microcontrollers
to monitor simple appliances through the GPIO pins. All transmissions from the SAMOS unit are
in serial.

## SOMMS Messaging protocol
The SOMMS (SAMOS Online Monitoring Messaging System) is used by SAMOS to communicate from the
SAMOS unit to a connected Serial UART device.

### SOMMS Standard Messaging
When the system is at normal state and no faults are present SOMMS will send the following message
every CPU cycle:
SAMOS Module ID (MID) (STR) , SAMOS Module Name (MNA) (STR) , Current Position (INT) , Safety Chain Present (BOOL) , xx (Just "xx" represents no faults.)

A basic message would look like this:
1122,testmodule,3,true,xx
This would mean that the device has a module id of 1122, is called testmodule is at position 3, the safety chain is connected (true)
and there are no faults present (xx).

When faults appear the same message is sent but instead of "xx" there is the fault code. If multiple faults are present the service recieveing
SAMOS unit communications is responsible for tracking active faults.

### Reseting SOMMS faults

If a SAMOS unit detects a fault and reports it using SOMMS Standard Messaging the only way to clear the fault
is to go to the SAMOS unit that had or has a fault present and reset it with the fault no longer present.
This is due to safety measures so that no SAMOS reported fault goes uninvestigated.

## SORM Message and Acknowledging the SORM Message

The SORM Message is critical in bringing the SAMOS unit online. This does not utilize te SOMMS protocol.

### Initial SORM Message from SAMOS Unit

The first message a SAMOS unit sends is this:

onlinereq, SAMOS Module ID (MID) (STR) , SAMOS Module Name (MNA) (STR)

An example message looks like this:

onlinereq,1122,testmodule

This message would mean that the module called testmodule with an ID of 1122
is requesting to be online.

### SORM Message Acknowledging

In order for the SAMOS Unit to become online the SORM Message must be acknowledged.

This can be done like this:

onlineack, SAMOS Module ID (MID) (STR) , SAMOS Module Name (MNA) (STR)

An example message looks like this:

onlineack,1122,testmodule

This message would mean that the module called testmodule with an ID of 1122
has been acknowledged and is now online.

## Pinouts

### SAMOS Monitoring Serial (SOMMS - SAMOS Online Monitoring Messaging System) interface pinout
Arduino UNO:
- D13 , D12

### SAMOS For Advanced REOTEK Lifts (SODAL - SAMOS Online management for Digital Advanced Lifts) interface pinout

WARNING!!! THE SODAL INTERFACE MODE IS ONLY COMPATIBLE WITH DALs ( DIGITAL ADVANCED LIFTS ) THAT ONLY PROVIDE
A DIGITAL OUTPUT. THE SAMOS UNIT WILL NOT TAKE ANALOG INPUTS.

Arduino UNO: (Refer to SOMMS pinout for monitoring pinout.)
- D7 - Safety
- D6 - Floor 1
- D5 - Floor 2
- D4 - Floor 3
- D3 - Keyswitch MODE 2
- D2 - Keyswitch MODE 1

## Powering the SAMOS unit
There are 3 ways to power an Arduino UNO based SAMOS unit. Please always check power supply voltage.
Refer to Arduino official specifications for any voltages.
### Barrel jack
Refer to Arduino official specifications for barrel jack usage.
### USB-B Port
Use a standard USB-B cable.
### VIN Pin
Apply correct voltage DC to the VIN (Voltage INput) pin. Connect the GND to GND.
