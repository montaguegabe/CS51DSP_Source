//
//  DSPFunctions.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Michael Veloso on 4/28/2015
//
//

#include "DSPEffects.h"

#pragma mark Static Helpers

// Changes volume of a single sample
static AmplitudeType volumeChangeSample(AmplitudeType amplitude, float decibels) {
    double mult = pow(2, (decibels / 6));
    double newAmp = amplitude * mult;
    return newAmp;
}

// Changes volume of a vector
static void volumeChange(AmplitudeVector& amplitudes, float decibels) {
    
    auto numSamples = amplitudes.size();
    for (int i = 0; i < numSamples; i++) {
        amplitudes[i] = volumeChangeSample(amplitudes[i], decibels);
    }
}

// Gets maximum amplitude in a vector
static double getMax(AmplitudeVector& amplitudes) {
    double maxValue = 0.0;
    auto size = amplitudes.size();
    for (int i = 0; i < size; i++) {
        if (amplitudes[i] > maxValue){
            maxValue = amplitudes[i];
        }
    }
    return maxValue;
}

// Converts raw amplitude to decibel value, with max Amplitude = 0 db
static double rawToDecibel(double rawAmp, AmplitudeType amplitudeRange) {
    double dBValue = 0.0;
    double normalizedAmp = std::abs(rawAmp) / amplitudeRange;
    dBValue = 6 * (log2(normalizedAmp));
    return dBValue;
}

// Converts decibel value to raw amplitude, with max Amplitude = 0 db
static double decibelToRaw(double decibel, AmplitudeType amplitudeRange) {
    double rawAmp = 0.0;
    rawAmp = pow(2, (decibel/6)) * amplitudeRange;
    return rawAmp;
}

#pragma mark Effect Implementations

void DSPEffect::apply(SoundWave& target) { }
DSPEffect::~DSPEffect() { }

// Adjusts volume of an AmplitudeVector by decibels
void VolumeChangeEffect::apply(SoundWave& target) {
    
    AmplitudeVector& amplitudes = target.getAmplitudeTimeVector();
    volumeChange(amplitudes, mDecibels);
}
VolumeChangeEffect::~VolumeChangeEffect() { }

// Compresses an AV to the amplitude peak; threshold should be in decibels
// with 0dB as max; ratio assumes float:1
void CompressorEffect::apply(SoundWave &target) {
    
    AmplitudeVector& amplitudes = target.getAmplitudeTimeVector();
    
	// Finds max amplitude in vector
	double maxValue = getMax(amplitudes);
	double currentDB = 0.0;

	// Shrinks all amplitudes above threshold by ratio
	double shrinkValue = 0.0;
    auto size = amplitudes.size();
	for (int i = 0; i < size; i++) {
		currentDB = rawToDecibel(amplitudes[i], maxValue);
		if (currentDB > mThreshold){
			shrinkValue = (currentDB - ((mThreshold - currentDB) * (mRatio - 1 / mRatio)));
			amplitudes[i] = volumeChangeSample(amplitudes[i], shrinkValue);
		}
	};

	// Finds new max amplitude in altered vector
	double newMaxValue = getMax(amplitudes);

	// Expands all amplitudes by difference in previous and new maxValue
    //TODO: Figure out what the second argument should be for rawToDecibel!
	double expandValue = rawToDecibel(maxValue, maxValue * 2) - rawToDecibel(newMaxValue, maxValue * 2);
	volumeChange(amplitudes, expandValue);
}
CompressorEffect::~CompressorEffect() { }

// TODO: Change below to match the format above. See header file for instance
// variables of each effect.

//Adds delay
AmplitudeVector delay
  (AmplitudeVector& amplitudes, float delayInSeconds, float feedback);

//Pitch shifts an AV by cents
AmplitudeVector pitchShift(AmplitudeVector amplitudes, int cents);

//Stretches an AV by percentage stretch
AmplitudeVector timeStretch(AmplitudeVector amplitudes, float stretch);