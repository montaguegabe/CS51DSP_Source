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

class MainContentComponent : public Component {
public:
    
    MainContentComponent();
    
    ~MainContentComponent();
    
    void paint (Graphics& g) override;
    
    
private:    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif /* defined(__CS51DigitalSignalProcessor__MainComponent__) */
