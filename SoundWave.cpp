//
//  SoundWave.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "SoundWave.h"
#include "SoundWaveFFT.h"

// Initializes a sound wave instance from an audio file
SoundWave::SoundWave(String filename) {
    
    mFF = -1;
	mFormatManager.registerBasicFormats();
	mAudioFile = File(filename);
	bool filePathCorrect = (mAudioFile.getFullPathName() == filename);
	bool fileExists = mAudioFile.exists();
	mAudioReader = mFormatManager.createReaderFor(mAudioFile);

	// Collects data about audio file
	mNumSamples = mAudioReader->lengthInSamples;
	mSampleRate = mAudioReader->sampleRate;
	mNumChannels = mAudioReader->numChannels;
	mLengthInSeconds = mNumSamples / mSampleRate;
	bool fileNonZero = mNumSamples > 0;


	mInitializedProperly =
	   (fileExists &&
		filePathCorrect &&
		fileNonZero
		);
		
}

// Returns if an error occured during initialization
bool SoundWave::errorDuringInit() {

	return !mInitializedProperly;
}

// Returns the sound's duration in seconds
double SoundWave::getDurationSeconds() {
		
	return mLengthInSeconds;

}

// Returns a vector of the waveform
AmplitudeVector& SoundWave::getAmplitudeTimeVector() {

    // Only populate vector on first call (lazily do work)
    if (mAmplitudeTimeVector.size() == 0) {
        
        // Initialize variables
        AmplitudeType sample;
        
        // Creates & fills sample buffer equal to the length of a file
        AudioSampleBuffer buffer(mNumChannels, mNumSamples);
        buffer.clear();
        mAudioReader->read(&buffer, 0, mNumSamples, 0, true, true);
        
        /* Fills a vector with samples from the buffer, normalized between
         * -1.0 and 1.0. For multichannel tracks, all samples at a given time
         * are averaged. Better would be an array of vector of each individual
         * channel, so we could perform an FFT on each and display each channel's
         * specific spectrogram, but that's way out of scope */
        
        // Rounds down to a power of 2. Not ideal
        // TODO: Fix
        mLog2Samples = floor(log2(mNumSamples));
        int sampleCap = pow(2, mLog2Samples);
        
        for (int i = 0; i < sampleCap; i++) {
            sample = 0.0;
            for (int j = 0; j < mNumChannels; j++) {
                sample = sample + buffer.getSample(j, i);
            }
            sample = sample / mNumChannels;
            mAmplitudeTimeVector.push_back(sample);
        }
    }

    return mAmplitudeTimeVector;
}

// Returns a reference to a vector of the fourier transform
AmplitudeVector& SoundWave::getAmplitudeFrequencyVector() {
    
    // Calculate if not already there
    if (mAmplitudeFrequencyVector.size() == 0) {
        
        // Copy amplitude time vector over
        mAmplitudeFrequencyVector = mAmplitudeTimeVector;
        fftVariableSamplePow2(mAmplitudeFrequencyVector, mLog2Samples);
    }
    
    return mAmplitudeFrequencyVector;
}

// Returns the spectrogram data, that is, a vector of Fourier transform vectors
// for each small window of time throughout the audio.
std::vector<AmplitudeVector>& SoundWave::getSpectrogramData() {
    
    //TODO: Implement
    
    mSpectrogramData.clear();
    
    // Dummy implementation that returns some nice blobs
    for (int i = 0; i < 500; i++) {
        
        AmplitudeVector newVector;
        for (int j = 0; j < 500; j++) {
            
            AmplitudeType value = sin(i / 7.0f) * cos(j / 7.0f) * 128;
            newVector.push_back(value);
        }
        
        mSpectrogramData.push_back(newVector);
    }
    
    return mSpectrogramData;
}

double::SoundWave::getSampleRate() {
    return mSampleRate;
}

// Lazy returning
int SoundWave::getFF() {
    
    // Calculate if not already
    if (mFF == -1) {
        
        AmplitudeType maximum = 0;
        int maxFreq = 0;
        
        int size = mAmplitudeFrequencyVector.size();
        for (int i = 0; i < size; i++) {
            AmplitudeType value = mAmplitudeFrequencyVector[i];
            if (value > maximum) {
                maximum = value;
                maxFreq = i;
            }
        }
        
        mFF = maxFreq;
    }
    
    return mFF;
}