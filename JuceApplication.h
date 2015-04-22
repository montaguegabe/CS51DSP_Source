//
//  JuceApplication.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#ifndef __CS51DigitalSignalProcessor__JuceApplication__
#define __CS51DigitalSignalProcessor__JuceApplication__

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"
#include "ApplicationDelegate.h"
#include "MainWindow.h"

class CS51DigitalSignalProcessorApplication  : public JUCEApplication {
public:
    CS51DigitalSignalProcessorApplication() { ApplicationDelegate::getInstance(); }
    
    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }
    
    // Target-action implementation using delegation
    void setDelegate (ApplicationDelegate* ad) {
        mDelegate = ad;
    }
    
    //==============================================================================
    void initialise (const String& commandLine) override {
        if (mDelegate) mDelegate->init();
    }
    void shutdown() override {
        if (mDelegate) mDelegate->shutdown();
    }
    void systemRequestedQuit() override { quit(); }
    void anotherInstanceStarted (const String& commandLine) override {}
    
private:
    ApplicationDelegate* mDelegate;
};

#endif /* defined(__CS51DigitalSignalProcessor__JuceApplication__) */
