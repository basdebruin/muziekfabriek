#include <Arduino.h>
#include <Sensors.cpp>
#include <Filters.cpp>

#define VELO 14

void setup() {
    Serial.begin(9600);

    setupVelostat(VELO);
}

// --- LOOP ---

void loop() {
    int velo_data = readVelostat(VELO);
    Serial.print("\n");
    Serial.print(velo_data);
    Serial.print('\t');

    for (int i = 0; i < velo_data; i+=10) {
        Serial.print('|');
    }

    delay(30);
}