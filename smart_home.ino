/*
 * Smart Home Automation System
 * Author: Mothi Charan Naik Desavath
 * Hardware: Arduino Mega + HC-05 Bluetooth + IR Receiver + 8-channel Relay
 * Control: Smartphone App (Bluetooth) + IR Remote + Manual Switch
 */

#include <IRremote.h>
#include <SoftwareSerial.h>

// Pins
#define IR_PIN 2
#define BT_RX 10
#define BT_TX 11

// Relay pins (active LOW)
#define RELAY1 22  // Living Room Light
#define RELAY2 24  // Bedroom Light
#define RELAY3 26  // Kitchen Light
#define RELAY4 28  // Bathroom Light
#define RELAY5 30  // Fan
#define RELAY6 32  // TV
#define RELAY7 34  // AC
#define RELAY8 36  // Gate Lock

int relayPins[] = {RELAY1, RELAY2, RELAY3, RELAY4, RELAY5, RELAY6, RELAY7, RELAY8};
bool relayStates[] = {false, false, false, false, false, false, false, false};

// IR Remote Codes (Adjust to your remote)
#define IR_1 0xFFA25D
#define IR_2 0xFF629D
#define IR_3 0xFFE21D
#define IR_4 0xFF22DD
#define IR_5 0xFF02FD
#define IR_ALL_ON  0xFF906F
#define IR_ALL_OFF 0xFFB04F

IRrecv irrecv(IR_PIN);
decode_results results;
SoftwareSerial bluetooth(BT_RX, BT_TX);

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    irrecv.enableIRIn();

    for (int i = 0; i < 8; i++) {
        pinMode(relayPins[i], OUTPUT);
        digitalWrite(relayPins[i], HIGH);  // Active LOW - start OFF
    }
    Serial.println("Smart Home System Ready");
}

void loop() {
    // Bluetooth control
    if (bluetooth.available()) {
        char cmd = bluetooth.read();
        handleBluetooth(cmd);
    }

    // IR Remote control
    if (irrecv.decode(&results)) {
        handleIR(results.value);
        irrecv.resume();
    }
}

void toggleRelay(int index) {
    relayStates[index] = !relayStates[index];
    digitalWrite(relayPins[index], relayStates[index] ? LOW : HIGH);
    Serial.println("Relay " + String(index+1) + ": " + (relayStates[index] ? "ON" : "OFF"));
}

void handleBluetooth(char cmd) {
    // App sends '1'-'8' to toggle, 'A' = all on, 'Z' = all off
    if (cmd >= '1' && cmd <= '8') toggleRelay(cmd - '1');
    else if (cmd == 'A') for (int i = 0; i < 8; i++) { relayStates[i]=true; digitalWrite(relayPins[i], LOW); }
    else if (cmd == 'Z') for (int i = 0; i < 8; i++) { relayStates[i]=false; digitalWrite(relayPins[i], HIGH); }
}

void handleIR(long code) {
    switch(code) {
        case IR_1: toggleRelay(0); break;
        case IR_2: toggleRelay(1); break;
        case IR_3: toggleRelay(2); break;
        case IR_4: toggleRelay(3); break;
        case IR_5: toggleRelay(4); break;
        case IR_ALL_ON:  handleBluetooth('A'); break;
        case IR_ALL_OFF: handleBluetooth('Z'); break;
    }
}