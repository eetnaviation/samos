#include <pins_arduino.h>
#include <NeoSWSerial.h>

const String moduleId = "1111";
const String moduleName = "REOTEK-LIFT";

NeoSWSerial monitoring(13, 12);

bool sormAcked = true; // Set to false in production as this skips the SORM ack check on startup

const int keyswitchMode1Pin = 2;
const int keyswitchMode2Pin = 3;
const int floor1pin = 6;
const int floor2pin = 5;
const int floor3pin = 4;
const int safetyPin = 7;

int keyswitchMode1Read;
int keyswitchMode2Read;
int floor1read;
int floor2read;
int floor3read;
int safetyread;
int curFloor = 0;

bool fault77 = false;
bool safetyChainConnected = false;

void setSafetyBool();
void writeMonitoringStatus();
void decideCurrentFloor();
void updateMonitoringInput();
int getPinMode(int p);

void setup() {
  Serial.begin(9600);
  Serial.println("---------------------------------------");
  Serial.println("INITALIZE SYS...  REOTEK (C) 2024 SAMOS");
  Serial.println(" Simple Appliance Monitoring OS - v0.1 ");
  Serial.println("- - - - - - - - - - - - - - - - - - - -");
  Serial.println(" Developed and tested by:              ");
  Serial.println("  - VELEND.EU                          ");
  Serial.println("  - eetnaviation                       ");
  Serial.println("- - - - - - - - - - - - - - - - - - - -");
  Serial.println("  - https://velend.eu/                 ");
  Serial.println("  - https://github.com/eetnaviation    ");
  Serial.println("---------------------------------------");
  Serial.println("Define pins...");
  pinMode(keyswitchMode1Pin, INPUT_PULLUP);
  pinMode(keyswitchMode2Pin, INPUT_PULLUP);
  pinMode(floor1pin, INPUT_PULLUP);
  pinMode(floor2pin, INPUT_PULLUP);
  pinMode(floor3pin, INPUT_PULLUP);
  pinMode(safetyPin, INPUT_PULLUP);
  Serial.println("Done.");
  Serial.println("Define monitoring interface...");
  monitoring.begin(9600);
  Serial.println("Done.");
  Serial.println("Sending SAMOS Online Request Message (SORM)...");
  monitoring.println("onlinereq," + moduleId + "," + moduleName);
  Serial.println("Sent SORM message.");
  Serial.println("Done.");
  Serial.println("Waiting for SORM ACK message...");
  while (!sormAcked) {

  }
  Serial.println("Done.");
  Serial.println("Check GPIO pins status...");
  for (int pin = 0; pin < 21; pin++) {
    int mode = getPinMode(pin);
    if (mode < 0) {
      Serial.println("");
      Serial.print("Pin ");
      Serial.print(pin); 
      Serial.println(" is INVALID.");
    }
    else {
      Serial.print("Pin ");
      Serial.print(pin);
      Serial.print(" is defined as ");
      if (mode == INPUT) {
        Serial.println("INPUT.");
      }
      else {
        Serial.println("OUTPUT.");
      }
    }
  }
  Serial.println("Done.");
  Serial.println("System ready.");
}

void loop() {
  updateMonitoringInput();
  writeMonitoringStatus();
}

void setSafetyBool() {
  if (safetyread == 0) {
    safetyChainConnected = true;
  } else {
    safetyChainConnected = false;
  }
}

void writeMonitoringStatus() {
  if (fault77 == true) {
    monitoring.println(String(moduleId) + "," + String(moduleName) + "," + String(curFloor) + "," + String(safetyChainConnected) + "77");
  } else {
    monitoring.println(String(moduleId) + "," + String(moduleName) + "," + String(curFloor) + "," + String(safetyChainConnected) + "xx");
  }
}

void decideCurrentFloor() {
  int zeroCount = (floor1read == 0) + (floor2read == 0) + (floor3read == 0);
  // Check if more than one is zero
  if (zeroCount > 1) {
    fault77 = true;
  } else {
    if (floor1read == 0) {
      curFloor = 1;
    } else if (floor2read == 0) {
      curFloor = 2;
    } else if (floor3read == 0) {
      curFloor = 3;
    }
  }
}

void updateMonitoringInput() {
  keyswitchMode1Read = digitalRead(keyswitchMode1Pin);
  keyswitchMode2Read = digitalRead(keyswitchMode2Pin);
  floor1read = digitalRead(floor1pin);
  floor2read = digitalRead(floor2pin);
  floor3read = digitalRead(floor3pin);
  safetyread = digitalRead(safetyPin);
  setSafetyBool();
  decideCurrentFloor();
}

int getPinMode(int p)
{
  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
      const int MAX_DIGITAL_PIN_NUMBER = 69;
  #else
      const int MAX_DIGITAL_PIN_NUMBER = 19;
  #endif
  // Check valid pin number
  if (p > MAX_DIGITAL_PIN_NUMBER) {
    return -1;
  }
  // Convert designated Arduino pin to ATMega port and pin
  uint8_t pbit  = digitalPinToBitMask(p);
  uint8_t pport = digitalPinToPort(p);
  // Read the ATmega DDR for this port
  volatile uint8_t *pmodereg = portModeRegister(pport);
  // Test the value of the bit for this pin and return 
  // 0 if it is reset and 1 if it is set
  return ((*pmodereg & pbit) != 0);
}