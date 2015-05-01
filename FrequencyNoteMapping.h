//
//  FrequencyNoteMapping.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/30/15.
//
//

#ifndef CS51DigitalSignalProcessor_FrequencyNoteMapping_h
#define CS51DigitalSignalProcessor_FrequencyNoteMapping_h

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>

struct Note {
    String mName;
    float mFreq;
};

typedef std::vector<Note> NoteVector;

static void addNote(NoteVector& v, String name, float freq) {
    Note note {name, freq};
    v.push_back(note);
}

static NoteVector getMappingNoteVector() {
    
    NoteVector v;
    
    addNote(v, "C0", 16.35);
    addNote(v, "C#0/Db0", 17.32);
    addNote(v, "D0", 18.35);
    addNote(v, "D#0/Eb0", 19.45);
    addNote(v, "E0", 20.60);
    addNote(v, "F0", 21.83);
    addNote(v, "F#0/Gb0", 23.12);
    addNote(v, "G0", 24.50);
    addNote(v, "G#0/Ab0", 25.96);
    addNote(v, "A0", 27.50);
    addNote(v, "A#0/Bb0", 29.14);
    addNote(v, "B0", 30.87);
    addNote(v, "C1", 32.70);
    addNote(v, "C#1/Db1", 34.65);
    addNote(v, "D1", 36.71);
    addNote(v, "D#1/Eb1", 38.89);
    addNote(v, "E1", 41.20);
    addNote(v, "F1", 43.65);
    addNote(v, "F#1/Gb1", 46.25);
    addNote(v, "G1", 49.00);
    addNote(v, "G#1/Ab1", 51.91);
    addNote(v, "A1", 55.00);
    addNote(v, "A#1/Bb1", 58.27);
    addNote(v, "B1", 61.74);
    addNote(v, "C2", 65.41);
    addNote(v, "C#2/Db2", 69.30);
    addNote(v, "D2", 73.42);
    addNote(v, "D#2/Eb2", 77.78);
    addNote(v, "E2", 82.41);
    addNote(v, "F2", 87.31);
    addNote(v, "F#2/Gb2", 92.50);
    addNote(v, "G2", 98.00);
    addNote(v, "G#2/Ab2", 103.83);
    addNote(v, "A2", 110.00);
    addNote(v, "A#2/Bb2", 116.54);
    addNote(v, "B2", 123.47);
    addNote(v, "C3", 130.81);
    addNote(v, "C#3/Db3", 138.59);
    addNote(v, "D3", 146.83);
    addNote(v, "D#3/Eb3", 155.56);
    addNote(v, "E3", 164.81);
    addNote(v, "F3", 174.61);
    addNote(v, "F#3/Gb3", 185.00);
    addNote(v, "G3", 196.00);
    addNote(v, "G#3/Ab3", 207.65);
    addNote(v, "A3", 220.00);
    addNote(v, "A#3/Bb3", 233.08);
    addNote(v, "B3", 246.94);
    addNote(v, "C4", 261.63);
    addNote(v, "C#4/Db4", 277.18);
    addNote(v, "D4", 293.66);
    addNote(v, "D#4/Eb4", 311.13);
    addNote(v, "E4", 329.63);
    addNote(v, "F4", 349.23);
    addNote(v, "F#4/Gb4", 369.99);
    addNote(v, "G4", 392.00);
    addNote(v, "G#4/Ab4", 415.30);
    addNote(v, "A4", 440.00);
    addNote(v, "A#4/Bb4", 466.16);
    addNote(v, "B4", 493.88);
    addNote(v, "C5", 523.25);
    addNote(v, "C#5/Db5", 554.37);
    addNote(v, "D5", 587.33);
    addNote(v, "D#5/Eb5", 622.25);
    addNote(v, "E5", 659.25);
    addNote(v, "F5", 698.46);
    addNote(v, "F#5/Gb5", 739.99);
    addNote(v, "G5", 783.99);
    addNote(v, "G#5/Ab5", 830.61);
    addNote(v, "A5", 880.00);
    addNote(v, "A#5/Bb5", 932.33);
    addNote(v, "B5", 987.77);
    addNote(v, "C6", 1046.50);
    addNote(v, "C#6/Db6", 1108.73);
    addNote(v, "D6", 1174.66);
    addNote(v, "D#6/Eb6", 1244.51);
    addNote(v, "E6", 1318.51);
    addNote(v, "F6", 1396.91);
    addNote(v, "F#6/Gb6", 1479.98);
    addNote(v, "G6", 1567.98);
    addNote(v, "G#6/Ab6", 1661.22);
    addNote(v, "A6", 1760.00);
    addNote(v, "A#6/Bb6", 1864.66);
    addNote(v, "B6", 1975.53);
    addNote(v, "C7", 2093.00);
    addNote(v, "C#7/Db7", 2217.46);
    addNote(v, "D7", 2349.32);
    addNote(v, "D#7/Eb7", 2489.02);
    addNote(v, "E7", 2637.02);
    addNote(v, "F7", 2793.83);
    addNote(v, "F#7/Gb7", 2959.96);
    addNote(v, "G7", 3135.96);
    addNote(v, "G#7/Ab7", 3322.44);
    addNote(v, "A7", 3520.00);
    addNote(v, "A#7/Bb7", 3729.31);
    addNote(v, "B7", 3951.07);
    addNote(v, "C8", 4186.01);
    addNote(v, "C#8/Db8", 4434.92);
    addNote(v, "D8", 4698.63);
    addNote(v, "D#8/Eb8", 4978.03);
    addNote(v, "E8", 5274.04);
    addNote(v, "F8", 5587.65);
    addNote(v, "F#8/Gb8", 5919.91);
    addNote(v, "G8", 6271.93);
    addNote(v, "G#8/Ab8", 6644.88);
    addNote(v, "A8", 7040.00);
    addNote(v, "A#8/Bb8", 7458.62);
    addNote(v, "B8", 7902.13);
    
    return v;
}

#endif
