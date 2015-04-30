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
typedef double AmplitudeType;
typedef std::vector<AmplitudeType> AmplitudeVector;

// Limit for samples
#define log2SampleMax 27
#define sampleMax 134217728
#define log2SampleMin 10
#define sampleMin 1024

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
    
    // Returns the spectrogram data, that is, a vector of Fourier transform vectors
    // for each small window of time throughout the audio.
    std::vector<AmplitudeVector>& getSpectrogramData();
    
    // Fundamental frequency
    int getFF();
    unsigned int getFFIndex();
    
    // Get sample rate
    double getSampleRate();
    
private:

    // File loading variables
	AudioFormatManager mFormatManager;
	AudioFormatReader* mAudioReader;
	File mAudioFile;
	FileInputStream* mInputStream;
    
    // Samples/rate/channels
	int64 mNumSamples;
    unsigned int mLog2Samples;
	double mSampleRate;
	double mLengthInSeconds;
    int mNumChannels;
    
    // Whether the object was initialized properly
	bool mInitializedProperly;
    
    // The fundamental freq of the sound
    int mFF;
    
    // Holds amplitude over time
    AmplitudeVector mAmplitudeTimeVector;
    
    // Holds spectrogram data
    std::vector<AmplitudeVector> mSpectrogramData;
    unsigned int mLog2DiscreteInterval;
    
    // Holds amplitude over frequency
    AmplitudeVector mAmplitudeFrequencyVector;
};

#endif /* defined(__CS51DigitalSignalProcessor__SoundWave__) */
