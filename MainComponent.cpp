//
//  MainComponent.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "MainComponent.h"
#include "Visuals.h"

MainContentComponent::MainContentComponent() {
    
    setSize (windowWidth, windowHeight);
    mTime = 0.0f;
    setAudioChannels (2, 2);
}

MainContentComponent::~MainContentComponent() {

}

// Plays a vector
void MainContentComponent::playVector(AmplitudeVector& vector, double sampleRate) {
    
    mSource = &vector;
    mTime = 0.0;
    mSampleRateAudio = sampleRate;
}

void MainContentComponent::paint (Graphics& g) {
    
    // Drawing code goes here
    g.fillAll (Colours::black);
}

// Sound-producing overrides
void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    mSampleRateOut = sampleRate;
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    
    if (!mSource) {
        bufferToFill.clearActiveBufferRegion();
    }
    else {
        
        double timeIncrement = mSampleRateOut / mSampleRateAudio;
        
        bufferToFill.clearActiveBufferRegion();
        
        if ((int) (mTime + bufferToFill.numSamples * timeIncrement + 1) >= mSource->size()) {
            mSource = nullptr;
        }
        else {
            
            const double blockStartTime = mTime;
            
            for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan) {
                
                mTime = blockStartTime;
                
                float* const channelData = bufferToFill.buffer->getWritePointer (chan, bufferToFill.startSample);
                
                long index;
                for (int i = 0; i < bufferToFill.numSamples ; ++i) {
                    
                    index = mTime;
                    channelData[i] = mSource->at(index);
                    mTime += timeIncrement;
                }
            }
        }
    }
}

void MainContentComponent::releaseResources() {
    
}

