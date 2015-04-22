//
//  MainWindow.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#ifndef __CS51DigitalSignalProcessor__MainWindow__
#define __CS51DigitalSignalProcessor__MainWindow__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

// A simple window class with a single content component. Non-resizable, and
// quits the app when closed.
class MainWindow : public DocumentWindow {
public:
    MainWindow (String name, Component* mainContent);
    void closeButtonPressed() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

#endif /* defined(__CS51DigitalSignalProcessor__MainWindow__) */
