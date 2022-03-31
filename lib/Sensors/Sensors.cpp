#include <Arduino.h>

// --- VELOSTAT ---
// src: https://forum.arduino.cc/t/arduino-nano-and-velostat/536370/2


void setupVelostat(int pin) {
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, HIGH);
}

int readVelostat(int pin) {
    int val = analogRead(pin);
    return val;
}

// --- BUTTON ---

void setupButton(int pin) {
	pinMode(pin, OUTPUT);
}

int readButton(int pin) {
	return digitalRead(pin);
}

// --- ULTRA SONIC SENSOR ---

void setupUltraSonic(int echoPin, int trigPin) {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
	pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

int readUltraSonic(int echoPin, int trigPin) {
    // Clears the trigPin condition
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	long duration = pulseIn(echoPin, HIGH);
	// Calculating the distance
	int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    return distance;
}

// --- LDR ---
// using pull up resistor

void setupLDR(int pin) {
	pinMode(pin, INPUT_PULLUP);
}

int readLDR(int pin) {
	int val = analogRead(pin);
	return val;
}

// calibrated LDR read

int calibrationValue = 0;
void calibrateLDR(int pin) {
	calibrationValue = readLDR(pin);
}

int readCalibratedLDR(int pin) {
	return (int) map(readLDR(pin), calibrationValue, 1024, 0, 1024);
}

// --- Potmeter ---

void setupPot(int pin) {
	pinMode(pin, INPUT);
}

int readPot(int pin) {
	return analogRead(pin);
}
