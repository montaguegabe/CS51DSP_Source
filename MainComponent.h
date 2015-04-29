//
//  MainComponent.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#ifndef __CS51DigitalSignalProcessor__MainComponent__
#define __CS51DigitalSignalProcessor__MainComponent__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundWave.h"

// The main component for the application. Supports vector playback
class MainContentComponent : public AudioAppComponent {
public:
    
    MainContentComponent();
    
    ~MainContentComponent();
    
    // Plays a vector
    void playVector(AmplitudeVector& vector, double sampleRate);
    
private:
    
    // The playback time
    double mTime;
    
    // The source of the vector
    AmplitudeVector* mSource;
    
    // The sample rate of the audio
    double mSampleRateAudio;
    double mSampleRateOut;
    
    void paint (Graphics& g) override;
    
    // Sound overrides
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif /* defined(__CS51DigitalSignalProcessor__MainComponent__) */
