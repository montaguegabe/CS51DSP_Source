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
	bool filePathCorrect = (mAudioFile.getFullPathName() == filename);
	bool fileExists = mAudioFile.exists();
	mAudioReader = mFormatManager.createReaderFor(mAudioFile);

	//collects data about audio file
	mNumSamples = mAudioReader->lengthInSamples;
	mSampleRate = mAudioReader->sampleRate;
	mLengthInSeconds = mNumSamples / mSampleRate;
	bool fileNonZero = mNumSamples > 0;

	//Creates & checks for validity of input stream
	mInputStream = mAudioFile.createInputStream();
	bool inputStreamCorrect = (mInputStream->getFile() == mAudioFile);
	bool validInputStream = mInputStream->openedOk();
	bool inputStreamNonzero = (mInputStream->getTotalLength() > 0);

	initializedProperly = 
	   (fileExists &&
		validInputStream &&
		filePathCorrect &&
		inputStreamCorrect &&
		inputStreamNonzero &&
		fileNonZero
		);
		
}

// Returns if an error occured during initialization
bool SoundWave::errorDuringInit() {

	return !initializedProperly;
}

// Returns the sound's duration in seconds
double SoundWave::getDurationSeconds() {
		
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
	AmplitudeType sample;
	mAmplitudeTimeVector.clear();	
	

	//Readies normalization between -1.0 and 1.0
	AmplitudeType normalizedVal = 0.0;
	unsigned int bitsPerChunk = (mAudioReader->bitsPerSample);
	unsigned int bytesPerChunk = bitsPerChunk / 8;
	unsigned int bytesInFile = mNumSamples * bytesPerChunk;
	double maxValue = pow(2, (bitsPerChunk - 1));
	bool usesFloatingPointData = mAudioReader->usesFloatingPointData;

	//Creates sample buffer for one channel and entire WAV file
	AudioSampleBuffer buffer(1, bytesInFile);
	buffer.clear();

	/*
	//Adds data to vector
	if (validInputStream)
	{
		while (!mInputStream->isExhausted())
		{
			mInputStream->read(&buffer, bytesPerChunk);
			sample = buffer.getSample(0, 0);
			if (usesFloatingPointData)
			{
				mAmplitudeTimeVector.push_back(sample);
			}
			else
			{				
				normalizedVal = sample / maxValue;
				mAmplitudeTimeVector.push_back(normalizedVal);
			}
		}
	}
	*/


	int64 inputStreamLength = mInputStream->getTotalLength();
	if (inputStreamLength > 0)
	{
		mInputStream->read(&buffer, bytesInFile);
	}
	
	for (int i = 0; i < 48000; i++) {
		sample = buffer.getSample(0, i);
		mAmplitudeTimeVector.push_back(sample);
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
