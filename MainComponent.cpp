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
    mPlayIndex = 0.0f;
    
    setAudioChannels (2, 2);
}

MainContentComponent::~MainContentComponent() {

}

void MainContentComponent::paint (Graphics& g) {
    
    // Drawing code goes here
    g.fillAll (Colours::black);
}

// Sound-producing overrides
void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    
    if (false) {
        bufferToFill.clearActiveBufferRegion();
    }
    else  {
        
        bufferToFill.clearActiveBufferRegion();
        const float originalPhase = mPlayIndex;
        
        for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan)
        {
            mPlayIndex = originalPhase;
            
            float* const channelData = bufferToFill.buffer->getWritePointer (chan, bufferToFill.startSample);
            
            for (int i = 0; i < bufferToFill.numSamples ; ++i)
            {
                channelData[i] = 0.01f * std::abs(std::sin (mPlayIndex));
                
                // increment the phase step for the next sample
                mPlayIndex = std::fmod (mPlayIndex + 0.02f, float_Pi * 2.0f);
            }
            
        }
    }
}

void MainContentComponent::releaseResources() {
    
}

