//
//  SoundWave.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#ifndef __CS51DigitalSignalProcessor__SoundWave__
#define __CS51DigitalSignalProcessor__SoundWave__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>

// Some type definitions
typedef int AmplitudeType;
typedef std::vector<AmplitudeType> AmplitudeVector;

// A container class for sound data, capable of analysis
class SoundWave {
public:
    // Initializes a sound wave instance from an audio file
    SoundWave(String filename);
    
    // Returns if an error occured during initialization
    bool errorDuringInit();
    
    // Returns the sound's duration in seconds
    double getDurationSeconds();
    
    // Returns a reference to a vector of the waveform
    AmplitudeVector& getAmplitudeTimeVector();
    
    // Returns a reference to a vector of the fourier transform
    AmplitudeVector& getAmplitudeFrequencyVector();
    
    //TODO: Other analysis definitions
    
private:
    
    // Holds amplitude over time
    AmplitudeVector mAmplitudeTimeVector;
    
    // Holds amplitude over frequency
    AmplitudeVector mAmplitudeFrequencyVector;
    
    //TODO: Declare private methods/variables, e.g. sampling rate
};

#endif /* defined(__CS51DigitalSignalProcessor__SoundWave__) */
