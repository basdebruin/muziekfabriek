#include <Arduino.h>
#include <MIDIUSB.h>

#ifndef MIDI_CHANNEL
    #define MIDI_CHANNEL 1
#endif

void sendLoggedMidiControl(const char* descriptor, int val, int midi_cc) {

    // minmax val
    int fixed_val = min(max(val, 0), 127);

    // log to serial
    Serial.print('\n');
    Serial.print(descriptor);
    Serial.print('\t');
    Serial.print(fixed_val);

    // send control value

    usbMIDI.sendControlChange(midi_cc, fixed_val, MIDI_CHANNEL);

}

void sendMidiNote(int note) {
    Serial.print(note);
    usbMIDI.sendNoteOn(note, 120, MIDI_CHANNEL);
}