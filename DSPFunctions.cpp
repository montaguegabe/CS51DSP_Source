//
//  DSPFunctions.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Michael Veloso on 4/28/2015
//
//

#include "DSPFunctions.h"

//dummy starting values; get these from SoundWave
double amplitudeRange = 1.0; 
int numSamples = 1024;
double sampleRate = 48000.0;

//Adjusts volume of an AmplitudeVector by decibels
AmplitudeVector volumeChange(AmplitudeVector amplitudes, double decibels){
	for (int i = 0; i < numSamples; i++) {
		amplitudes[i] = volumeChangeSample(amplitudes[i], decibels);
	}
	return amplitudes;
}

//Compresses an AV to the amplitude peak; threshold should be in decibels
//with 0dB as max; ratio assumes float:1
//More sophsticated would be adding an attack and release for applying the compression
AmplitudeVector compression
(AmplitudeVector amplitudes, double threshold, double ratio){
	//finds max amplitude in vector
	double maxValue = getMax(amplitudes);
	double currentDB = 0.0;

	//shrinks all amplitudes above threshold by ratio
	double shrinkValue = 0.0;
	for (int i = 0; i < numSamples; i++) {
		currentDB = rawToDecibel(amplitudes[i]);
		if (currentDB > threshold){
			shrinkValue = (threshold - currentDB) * ((ratio - 1) / ratio);
			amplitudes[i] = volumeChangeSample(amplitudes[i], shrinkValue);
		}
	};

	//finds new max amplitude in altered vector
	double newMaxValue = getMax(amplitudes);

	//expands all amplitudes by difference in previous and new maxValue
	double expandValue = rawToDecibel(maxValue) - rawToDecibel(newMaxValue);
	amplitudes = volumeChange(amplitudes, expandValue);

	return amplitudes;
}

//Adds delay; feedback should be a value between 0.0 and 1.0;
//stops adding delay when quieter than -24 dB

AmplitudeVector delay
(AmplitudeVector amplitudes, double delayInSeconds, double feedback)
{
	AmplitudeVector delayTemp = amplitudes;
	int sampleSize = int(delayInSeconds * sampleRate);
	int sampleOffset = sampleSize;
	int delayTempSize = delayTemp.capacity();
	double delayReductionInDB = rawToDecibel(feedback) / amplitudeRange;
	do{
		int vectorCapacity = amplitudes.capacity();
		int newSize = (vectorCapacity + delayTempSize + sampleSize);
		amplitudes.resize(newSize);
		delayTemp = volumeChange(delayTemp, delayReductionInDB);
		amplitudes = sumTwoVectors(amplitudes, delayTemp, sampleOffset);
		sampleOffset += sampleSize;
	} while (getMax(delayTemp) > amplitudeRange / 8);

	amplitudes.shrink_to_fit();

	return amplitudes;
}

//Pitch shifts an AV by cents; no time preservation
AmplitudeVector pitchShift(AmplitudeVector amplitudes, int cents);

//Stretches an AV by percentage stretch; no pitch preservation
AmplitudeVector timeStretch(AmplitudeVector amplitudes, double stretch);

//Changes volume of a single sample
AmplitudeType volumeChangeSample(AmplitudeType amplitude, double decibels){
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

//Sums two amplitude vectors at some offset, capping values at amplitudeRange
AmplitudeVector sumTwoVectors
(AmplitudeVector amplitudes1, AmplitudeVector amplitudes2, int offset){
	for (int i = 0; i < numSamples; i++){
		amplitudes1[i + offset] += amplitudes2[i];
		if (amplitudes1[i + offset] > amplitudeRange)
		{
			amplitudes1[i + offset] = amplitudeRange;
		}
		else if (amplitudes1[i + offset] < -amplitudeRange){
			amplitudes1[i + offset] = -amplitudeRange;
		}
	}

	return amplitudes1;
}