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

#pragma mark Base Class

// A class representing an effect
class DSPEffect {
public:
    // Destructor
    virtual ~DSPEffect();
    
    // Applies the effect to a SoundWave object, mutating its data
    virtual void apply(SoundWave& target);
};

#pragma mark Volume Change

class VolumeChangeEffect : DSPEffect {
public:
    VolumeChangeEffect(float decibels) { mDecibels = decibels; }
    ~VolumeChangeEffect() override;
    
    void apply(SoundWave& target) override;
    
private:
    float mDecibels;
};

#pragma mark Compressor

class CompressorEffect : DSPEffect {
public:
    CompressorEffect(float threshold, float ratio) {
        mThreshold = threshold;
        mRatio = ratio;
    }
    ~CompressorEffect() override;
    
    void apply(SoundWave& target) override;
    
private:
    float mThreshold;
    float mRatio;
};

#pragma mark Delay

class DelayEffect : DSPEffect {
public:
    DelayEffect(float delayInSeconds, float feedback) {
        mDelayInSeconds = delayInSeconds;
        mFeedback = feedback;
    }
    ~DelayEffect() override;
    
    void apply(SoundWave& target) override;
    
private:
    float mDelayInSeconds;
    float mFeedback;
};

#pragma mark Pitch Shift

class PitchShiftEffect : DSPEffect {
public:
    PitchShiftEffect(int cents) { mCents = cents; }
    ~PitchShiftEffect() override;
    
    void apply(SoundWave& target) override;
    
private:
    int mCents;
};

#pragma mark Time Stretch

class TimeStretch : DSPEffect {
public:
    TimeStretch(double stretch) { mStretch = stretch; }
    ~TimeStretch() override;
    
    void apply(SoundWave& target) override;
    
private:
    double mStretch;
};

#endif /* defined(__CS51DigitalSignalProcessor__DSPFunctions__) */