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

class MainContentComponent : public AudioAppComponent {
public:
    
    MainContentComponent();
    
    ~MainContentComponent();
    
    void paint (Graphics& g) override;
    
    
private:
    
    float mPlayIndex;
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif /* defined(__CS51DigitalSignalProcessor__MainComponent__) */
