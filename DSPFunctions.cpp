//
//  DSPFunctions.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Michael Veloso on 4/28/2015
//
//

#include "DSPFunctions.h"

double amplitudeRange = 1.0;
int numSamples = 0;

//Adjusts volume of an AmplitudeVector by decibels
AmplitudeVector volumeChange(AmplitudeVector amplitudes, float decibels){
	for (int i = 0; i < numSamples; i++) {
		amplitudes[i] = volumeChangeSample(amplitudes[i], decibels);
	}
	return amplitudes;
}

//Compresses an AV to the amplitude peak; threshold should be in decibels
//with 0dB as max; ratio assumes float:1
AmplitudeVector compression
  (AmplitudeVector amplitudes, float threshold, float ratio){
	//finds max amplitude in vector
	double maxValue = getMax(amplitudes);
	double currentDB = 0.0;

	//shrinks all amplitudes above threshold by ratio
	double shrinkValue = 0.0;
	for (int i = 0; i < numSamples; i++) {
		currentDB = rawToDecibel(amplitudes[i]);
		if (currentDB > threshold){
			shrinkValue = (currentDB - ((threshold - currentDB) * (ratio - 1 / ratio)));
			amplitudes[i] = volumeChangeSample(amplitudes[i], shrinkValue);
		}
	};

	//finds new max amplitude in altered vector
	double newMaxValue = getMax(amplitudes);

	//expands all amplitudes by difference in previous and new maxValue
	double expandValue = rawToDecibel(maxValue) - rawToDecibel(newMaxValue);
	volumeChange(amplitudes, expandValue);

	return amplitudes;
}

//Adds delay
AmplitudeVector delay
  (AmplitudeVector amplitudes, float delayInSeconds, float feedback);

//Pitch shifts an AV by cents
AmplitudeVector pitchShift(AmplitudeVector amplitudes, int cents);

//Stretches an AV by percentage stretch
AmplitudeVector timeStretch(AmplitudeVector amplitudes, float stretch);

//Changes volume of a single sample
AmplitudeType volumeChangeSample(AmplitudeType amplitude, float decibels){
	double mult = pow(2, (decibels / 6));
	double newAmp = amplitude * mult;
	return newAmp;
}

//Gets maximum amplitude in a vector
double getMax(AmplitudeVector amplitudes){
	double maxValue = 0.0;
	for (int i = 0; i < numSamples; i++){
		if (amplitudes[i] > maxValue){
			maxValue = amplitudes[i];
		}
	}
	return maxValue;
}

//converts raw amplitude to decibel value, with max Amplitude = 0 db
double rawToDecibel(double rawAmp){
	double dBValue = 0.0;
	double normalizedAmp = abs(rawAmp) / amplitudeRange;
	dBValue = 6 * (log2(normalizedAmp));
	return dBValue;
}

//converts decibel value to raw amplitude, with max Amplitude = 0 db
double decibelToRaw(double decibel){
	double rawAmp = 0.0;
	rawAmp = pow(2, (decibel/6)) * amplitudeRange;
	return rawAmp;
}