#include <Arduino.h>
#include <MIDIUSB.h>
#include <RotaryEncoder.h>
#include <Button.h>
#include <Sensors.cpp>
#include <Filters.cpp>

// --- DEFINING ALL PINS ---

#define BUTTON_PIN 14

#define ULTRA_SONIC_PIN_A 15
#define ULTRA_SONIC_PIN_B 16

#define ROTARY_PIN_A 17
#define ROTARY_PIN_B 18

#define POT_PIN 19

#define VELO_PIN 20

#define LDR_PIN 21

// --- MIDI Definitions ---

#define MIDI_CHANNEL 1

// --- SETUP ---

// RotaryEncoder encoder(ROTARY_PIN_A, ROTARY_PIN_B, RotaryEncoder::LatchMode::TWO03);
// Button button(BUTTON_PIN);


void setup() {
    Serial.begin(9600);
    usbMIDI.begin();
    // Sensor setup
    // setupUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B);
    // setupVelostat(VELO_PIN);
    // setupLDR(LDR_PIN);
    // calibrateLDR(LDR_PIN);
    setupPot(POT_PIN);
}

// --- LOOP ---

void loop() {
    // Serial.print("\nVelostat:\t");
    // Serial.print(readVelostat(VELO_PIN));
    
    // Serial.print("\nLDR:\t");
    // int ldr_val = readLDR(LDR_PIN);
    // Serial.print(ldr_val);
    // usbMIDI.sendControlChange(14, map(ldr_val, 0, 1024, 0, 127), MIDI_CHANNEL);

    // Serial.print("\ncalLDR:\t");
    // Serial.print(readCalibratedLDR(LDR_PIN));

    // Serial.print("\nButton:\t");
    // Serial.print(button.pressed());

    // encoder.tick();
    // Serial.print("\nRotary(RPM):\t");
    // Serial.print(encoder.getRPM());

    Serial.print("\nPotmeter:\t");
    int pot_val = readPot(POT_PIN);
    Serial.print(pot_val);
    usbMIDI.sendControlChange(14, map(pot_val, 0, 1024, 0, 127), MIDI_CHANNEL);

    // Serial.print("\nUltra Sonic:\t");
    // Serial.print(readUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B));

    // Serial.print("\n \n \n");

    //Serial.println("note");
    //usbMIDI.sendNoteOn(42, 100, MIDI_CHANNEL);

    delay(10);
}