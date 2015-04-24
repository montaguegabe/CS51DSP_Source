//
//  SoundWave.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "SoundWave.h"

// Initializes a sound wave instance from an audio file
SoundWave::SoundWave(String filename) {
    
    //TODO: Implement
}

// Returns if an error occured during initialization
bool SoundWave::errorDuringInit() {
    
    //TODO: Implement
    return false;
}

// Returns the sound's duration in seconds
double SoundWave::getDurationSeconds() {
    
    //TODO: Implement
    return 0.0f;
    
}

// Returns a vector of the waveform
AmplitudeVector& SoundWave::getAmplitudeTimeVector() {
    
    //TODO: Implement
    
    // Dummy implementation that returns a simple sine wave
    for (int i = 0; i < 500; i++) {
        AmplitudeType value = sin(i / 7.0f) * 100;
        mAmplitudeTimeVector.push_back(value);
    }
    
    return mAmplitudeTimeVector;
}

// Returns a reference to a vector of the fourier transform
AmplitudeVector& SoundWave::getAmplitudeFrequencyVector() {
    
    //TODO: Implement
    
    // Dummy implementation that returns an abs(cosine) wave
    for (int i = 0; i < 500; i++) {
        AmplitudeType value = cos(i / 7.0f) * 100;
        if (value < 0) value = -value;
        mAmplitudeFrequencyVector.push_back(value);
    }
    
    return mAmplitudeFrequencyVector;
}