#include <Arduino.h>
#include <MIDIUSB.h>
#include <RotaryEncoder.h>
#include <Button.h>
#include <Sensors.cpp>
#include <Filters.cpp>
#include <MidiTools.cpp>

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

#ifndef MIDI_CHANNEL
    #define MIDI_CHANNEL 1
#endif

// --- SETUP ---

RotaryEncoder encoder(ROTARY_PIN_A, ROTARY_PIN_B, RotaryEncoder::LatchMode::TWO03);
//Button button(BUTTON_PIN);


void setup() {
    Serial.begin(9600);
    usbMIDI.begin();
    // Sensor setup
    setupUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B);
    setupVelostat(VELO_PIN);
    setupLDR(LDR_PIN);
    calibrateLDR(LDR_PIN);
    setupPot(POT_PIN);
    setupButton(BUTTON_PIN);
}

// --- LOOP ---

void loop() {
    // Serial.print("\nVelostat:\t");
    // Serial.print(readVelostat(VELO_PIN));

    // VELO
    sendLoggedMidiControl(
        "Velo",
        map(readVelostat(VELO_PIN), 600, 30, 0, 127),
        13
    );
    
    // Serial.print("\nLDR:\t");
    // int ldr_val = readLDR(LDR_PIN);
    // Serial.print(ldr_val);

    // LDR
    sendLoggedMidiControl(
        "LDR",
        map(readCalibratedLDR(LDR_PIN), 0, 700, 0, 127),
        14
    );

    // Serial.print("\nButton:\t");
    // Serial.print(digitalRead(BUTTON_PIN));

    // Button
    sendLoggedMidiControl(
        "Button",
        readButton(BUTTON_PIN) * 127,
        15
    );

    // encoder.tick();
    // Serial.print("\nRotary(RPM):\t");
    // Serial.print(encoder.getRPM());

    encoder.tick();
    sendLoggedMidiControl(
        "Rotary",
        map(encoder.getRPM(), 0, 28, 0, 127),
        16
    );

    // Serial.print("\nPotmeter:\t");
    // int pot_val = readPot(POT_PIN);
    // Serial.print(pot_val);
    //usbMIDI.sendControlChange(14, map(pot_val, 0, 1024, 0, 127), MIDI_CHANNEL);

    // POTMETER
    sendLoggedMidiControl(
        "Potmeter",
        map(readPot(POT_PIN), 0, 1024, 0, 127),
        17
    );

    // Serial.print("\nUltra Sonic:\t");
    // Serial.print(readUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B));

    // Ultra sonic
    sendLoggedMidiControl(
        "Ultra Sonic",
        map(readUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B), 3, 30, 0, 127),
        18
    );

    Serial.print("\n \n \n");

    //sendMidiNote(42);

    delay(100);
}