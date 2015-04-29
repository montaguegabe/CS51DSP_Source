//
//  DSPFunctions.h
//  CS51DigitalSignalProcessor
//
//  Created by Michael Veloso on 4/28/2015
//
//

#ifndef __CS51DigitalSignalProcessor__DSPFunctions__
#define __CS51DigitalSignalProcessor__DSPFunctions__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <math.h>
#include "SoundWave.h"

//ensuring type definitions are consistent with SoundWave.h
typedef double AmplitudeType;
typedef std::vector<AmplitudeType> AmplitudeVector;

//Adjusts volume of an AmplitudeVector by decibels
AmplitudeVector volumeChange(AmplitudeVector amplitudes, double decibels);

//Compresses an AV to the amplitude peak
AmplitudeVector compression(AmplitudeVector amplitudes, double threshold, double ratio);

//Adds delay
AmplitudeVector delay(AmplitudeVector amplitudes, float delayInSeconds, float feedback);

//Pitch shifts an AV by cents
AmplitudeVector pitchShift(AmplitudeVector amplitudes, int cents);

//Stretches an AV by percentage stretch
AmplitudeVector timeStretch(AmplitudeVector amplitudes, double stretch);

//Adjusts volume of a single sample
AmplitudeType volumeChangeSample(AmplitudeType amplitude, double decibels);

//Gets max amplitude value
double getMax(AmplitudeVector amplitudes);

//Converts raw amplitude to decibel
double rawToDecibel(double rawAmp);

//Converts decibel to raw amplitude
double decibelToRaw(double decibel);


#endif /* defined(__CS51DigitalSignalProcessor__DSPFunctions__) */