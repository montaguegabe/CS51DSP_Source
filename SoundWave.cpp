//
//  SoundWave.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "SoundWave.h"
#include "SoundWaveFFT.h"
#include "FastIntPowerOperations.h"

// Initializes a sound wave instance from an audio file
SoundWave::SoundWave(String filename) {
    
    // Initialize variables
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
    
    // Set the discrete spectrogram interval to around an eigth of a second
    // (2^12 is around 5000 samples, which is around 1/8 of a second)
    mLog2DiscreteInterval = 12; //12;
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
        //mLog2Samples = ceil(log2(mNumSamples));
        mLog2Samples = log2Int(mNumSamples) + 1;
        int sampleCap = 1<<mLog2Samples;
        
        for (int i = 0; i < mNumSamples; i++) {
            sample = 0.0;
            for (int j = 0; j < mNumChannels; j++) {
                sample = sample + buffer.getSample(j, i);
            }
            sample = sample / mNumChannels;
            mAmplitudeTimeVector.push_back(sample);
        }
        
        for (int i = mNumSamples; i < sampleCap; i++) {
            mAmplitudeTimeVector.push_back(0);
        }
    }

    return mAmplitudeTimeVector;
}

// Returns a reference to a vector of the fourier transform
AmplitudeVector& SoundWave::getAmplitudeFrequencyVector() {
    
    // Calculate if not already there
    if (mAmplitudeFrequencyVector.size() == 0) {
        
        // Copy amplitude time vector over
        const unsigned int outputElements = 1 << (mLog2Samples + 1);
        const unsigned int inputSamples = 1 << mLog2Samples;
        
        // Complex input should be 0
        mAmplitudeFrequencyVector.resize(outputElements, 0);
        for (int i = 0; i < inputSamples; i++) {
            mAmplitudeFrequencyVector[i * 2] = mAmplitudeTimeVector[i];
        }
        
        fftVariableSamplePow2(mAmplitudeFrequencyVector, mLog2Samples);
        
        // Discard imaginary
        for (int i = 0; i < outputElements; i++) {
            mAmplitudeFrequencyVector[i] = std::abs(mAmplitudeFrequencyVector[i * 2]);
        }
        mAmplitudeFrequencyVector.resize(inputSamples);
    }
    
    return mAmplitudeFrequencyVector;
}

// Returns the spectrogram data, that is, a vector of Fourier transform vectors
// for each small window of time throughout the audio.
std::vector<AmplitudeVector>& SoundWave::getSpectrogramData() {
    
    // Lazy calculation
    if (mSpectrogramData.size() == 0) {
        
        // Get amplitude time vector as an array
        AmplitudeType* amplitudeTime = getAmplitudeTimeVector().data();
        
        // Number of blocks
        unsigned int samplesPerBlock = 1 << mLog2DiscreteInterval;
        unsigned int numBlocks = (1 << mLog2Samples) / samplesPerBlock;
        //if (numBlocks > 0) numBlocks--;
        
        for (int i = 0; i < numBlocks; i++) {
            
            // Allocate new vector for the slice and copy over values
            AmplitudeVector slice(samplesPerBlock * 2, 0);
            for (int j = 0; j < samplesPerBlock; j++) {
                slice[j * 2] = amplitudeTime[i * samplesPerBlock + j];
            }
            
            // Transform slice to fourier transform
            fftVariableSamplePow2(slice, mLog2DiscreteInterval);
            
            // Discard imaginary
            for (int j = 0; j < samplesPerBlock; j++) {
                slice[j] = std::abs(slice[j * 2]);
            }
            slice.resize(samplesPerBlock);
            
            // Add transformed slice to spectrogram data
            mSpectrogramData.push_back(slice);
        }
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
        int maxIndex = 0;
        
        int size = mAmplitudeFrequencyVector.size();
        for (int i = 0; i < size / 2; i++) {
            AmplitudeType value = mAmplitudeFrequencyVector[i];
            if (value > maximum) {
                maximum = value;
                maxIndex = i;
            }
        }
        
        mFF = maxIndex;
    }
    
    return mFF;
}