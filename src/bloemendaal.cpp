#include <Arduino.h>
#include <MIDIUSB.h>
#include <RotaryEncoder.h>
#include <Sensors.cpp>
#include <Filters.cpp>

// --- DEFINING ALL PINS ---

// --- DOOS #1 ---
// Slider
#define ULTRA_SONIC_PIN_A 0
#define ULTRA_SONIC_PIN_B 1
// Knop rotary
#define ROTARY_PIN_A 2
#define ROTARY_PIN_B 3
// Knop potmeter
#define POT_PIN 14
// Velostat zijkant
#define VELO_PIN 15
// LDR
#define LDR_PIN 16

// --- DOOS #2 --- KAAS ---
// Velostat kaas
#define D2_VELO_PIN 17
// LDR's
#define D2_LDR_1_PIN 18
#define D2_LDR_2_PIN 19
#define D2_LDR_3_PIN 20
// Knoppen Rotary
#define D2_ROTARY_PIN_1_A 4
#define D2_ROTARY_PIN_1_B 5

#define D2_ROTARY_PIN_2_A 6
#define D2_ROTARY_PIN_2_B 7

#define D2_ROTARY_PIN_3_A 8
#define D2_ROTARY_PIN_3_B 9


// --- MIDI Definitions ---

#define MIDI_CHANNEL 1

#define TO_127 0.125

// --- SETUP ---
// -- DOOS #1 ---
RotaryEncoder d1_encoder(ROTARY_PIN_A, ROTARY_PIN_B, RotaryEncoder::LatchMode::TWO03);
// --- DOOS #2 ---
RotaryEncoder d2_encoder_1(D2_ROTARY_PIN_2_A, D2_ROTARY_PIN_2_B, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder d2_encoder_2(D2_ROTARY_PIN_1_A, D2_ROTARY_PIN_1_B, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder d2_encoder_3(D2_ROTARY_PIN_3_A, D2_ROTARY_PIN_3_B, RotaryEncoder::LatchMode::TWO03);


// convenience function for serial printing and sending midi control
void send(const String name, int val, uint8_t control) {
    Serial.print("\n" + name + "\t\t" + val);
    usbMIDI.sendControlChange(control, val, MIDI_CHANNEL);
}

void setup() {
    Serial.begin(9600);
    usbMIDI.begin();

    // --- DOOS #1 ---
    //setupUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B); 

    setupVelostat(VELO_PIN);

    setupLDR(LDR_PIN);      calibrateLDR(LDR_PIN, 0);

    setupPot(POT_PIN);

    // --- DOOS #2 ---

    setupLDR(D2_LDR_1_PIN); calibrateLDR(D2_LDR_1_PIN, 1);
    setupLDR(D2_LDR_2_PIN); calibrateLDR(D2_LDR_2_PIN, 2);
    setupLDR(D2_LDR_3_PIN); calibrateLDR(D2_LDR_3_PIN, 3);
}

// --- LOOP ---

void loop() {

    // --- DOOS #1

    send(
        "D1 Velostat",
        readVelostat(VELO_PIN),
        14
    );

    send(
        "D1 LDR",
        readCalibratedLDR(LDR_PIN, 0),
        15
    );
    
    d1_encoder.tick();
    send(
        "D1 Knop Rotary",
        d1_encoder.getRPM() * 2,
        16
    );

    send(
        "D1 Knop Potmeter",
        readPot(POT_PIN),
        17
    );

    // send(
    //     "D1 Slider",
    //     readUltraSonic(ULTRA_SONIC_PIN_A, ULTRA_SONIC_PIN_B),
    //     18
    // );

    // -- DOOS #2

    send(
        "D2 LDR 1",
        readCalibratedLDR(D2_LDR_1_PIN, 1),
        20
    );
    send(
        "D2 LDR 2",
        readCalibratedLDR(D2_LDR_2_PIN, 2),
        21
    );
    send(
        "D2 LDR 3",
        readCalibratedLDR(D2_LDR_3_PIN, 3),
        22
    );

    d2_encoder_1.tick();
    send(
        "D2 Knop Rotary 1",
        d2_encoder_1.getRPM() * 2,
        23
    );
    d2_encoder_2.tick();
    send(
        "D2 Knop Rotary 2",
        d2_encoder_2.getRPM() * 2,
        24
    );
    d2_encoder_3.tick();
    send(
        "D2 Knop Rotary 3",
        d2_encoder_3.getRPM() * 2,
        25
    );

    Serial.print("\n\n\n");

    delay(100);
}