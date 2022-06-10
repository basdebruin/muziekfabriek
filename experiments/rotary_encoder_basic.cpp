#include <Arduino.h>
#include <Sensors.cpp>
#include <RotaryEncoder.h>

#define R_PIN_1 14
#define R_PIN_2 15

// rotary encoder
// src: https://github.com/mathertel/RotaryEncoder
RotaryEncoder encoder(R_PIN_1, R_PIN_2, RotaryEncoder::LatchMode::TWO03);

void setup() {
    Serial.begin(9600);
}

void loop() {
    encoder.tick();

    Serial.print("\n Position: ");
    Serial.print(encoder.getPosition());
    Serial.print("\t Direction: ");
    Serial.print((int) encoder.getDirection());
    Serial.print("\t RPM: ");
    Serial.print(encoder.getRPM());

    delay(1);
}