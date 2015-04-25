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
	mFormatManager.registerBasicFormats();
	mAudioFile = File(filename);
	initializedProperly = mAudioFile.exists();
	mAudioReader = mFormatManager.createReaderFor(mAudioFile);
}

// Returns if an error occured during initialization
bool SoundWave::errorDuringInit() {
	return !initializedProperly;
	//TODO: Implement
}

// Returns the sound's duration in seconds
double SoundWave::getDurationSeconds() {

	mNumSamples = mAudioReader->lengthInSamples;
	mSampleRate = mAudioReader->sampleRate;
	mLengthInSeconds = mNumSamples / mSampleRate;
	return mLengthInSeconds;

}

// Returns a vector of the waveform
AmplitudeVector& SoundWave::getAmplitudeTimeVector() {
    
    
    
	/* NEED TO TEST:
	 * How is data stored in WAVs? Spec says possibly ints or floats, depending.
	     - buffer.GetSample() returns a float, so maybe the conversion is automatic?
	 * What happens when non-32-bit samples are stored in the buffer?
	 * Is this iterating through the file correctly?
	 * How can we print debug messages?
	 * Does mInputStream.read() move the read head automatically?
	 */

	//initialize variables
	float sample = 0.0f;
	mAmplitudeTimeVector.clear();

	/*

	//Creates & checks for validity of input stream
	mInputStream = mAudioFile.createInputStream();
	bool validInputStream = mInputStream->openedOk();

	//Creates sample buffer for one channel and one 32-bit sample
	AudioSampleBuffer buffer(1, 1);

	//Readies normalization
	AmplitudeType normalizedVal = 0.0;
	unsigned int bitsPerChunk = (mAudioReader->bitsPerSample);
	unsigned int bytesPerChunk = bitsPerChunk / 8;
	double maxValue = pow(2, (bitsPerChunk - 1));

	//Adds data to vector
	if (validInputStream)
	{
		while (!mInputStream->isExhausted())
		{
			mInputStream->read(&buffer, bytesPerChunk);
			sample = buffer.getSample(0, 0);
			if (mAudioReader->usesFloatingPointData)
			{
				mAmplitudeTimeVector.push_back(sample);
			}
			else
			{				
				normalizedVal = sample / maxValue;
				mAmplitudeTimeVector.push_back(sample);
			}
		}
	}
	*/

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
    
    mAmplitudeFrequencyVector.clear();
    
    // Dummy implementation that returns an abs(cosine) wave
    for (int i = 0; i < 500; i++) {
        AmplitudeType value = cos(i / 7.0f) * 100;
        if (value < 0) value = -value;
        mAmplitudeFrequencyVector.push_back(value);
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
// PRIVATE methods
