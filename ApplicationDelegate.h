//
//  ApplicationDelegate.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#ifndef __CS51DigitalSignalProcessor__ApplicationDelegate__
#define __CS51DigitalSignalProcessor__ApplicationDelegate__

#include <stdio.h>
#include "MainWindow.h"
#include "SoundWave.h"
#include "MainComponent.h"
#include "VectorContentGraph.h"

class CS51DigitalSignalProcessorApplication;

// The application delegate is a singleton class that mediates between the
// GUI/JUCE and the data model (our sound wave).
class ApplicationDelegate : private Button::Listener {
public:
    
    // Called when the application delegate is created
    ApplicationDelegate();
    
    // Returns the sole instance of the application delegate
    static ApplicationDelegate& getInstance();
    
    // Definitions to maintain singularity
    ApplicationDelegate(ApplicationDelegate const&) = delete;
    void operator=(ApplicationDelegate const&) = delete;
    
    // Called to initialize the application
    void init();
    
    // Called to shut down the application
    void shutdown();
    
private:
    // A pointer to the JUCE application instance
    CS51DigitalSignalProcessorApplication* mJUCEApplication;
    
    // An auto-releasing pointer to the window.
    ScopedPointer<MainWindow> mMainWindow;
    
    // A pointer to a sole sound wave that can be loaded (only one at a time)
    ScopedPointer<SoundWave> mWaveData;
    
    // GUI elements created here don't have to be released manually, but you have
    // no control over when they are released. Creating an OwnedArray type will
    // also prevent any elements in the array from having to be released manually.
    
    MainContentComponent mMainComp;
    
    TextButton mLoadFileButton;
    TextButton mPlayButton;
    
    Label mAudioTitleText;
    Label mFFText;
    
    VectorContentGraph<AmplitudeType> mAmplitudeTimeView;
    VectorContentGraph<AmplitudeType> mAmplitudeFrequencyView;
    Spectrogram<AmplitudeType> mSpectrogram;
    
    //TODO: Define callbacks that will be activated when a user interacts with the GUI
    void buttonClicked (Button* button) override;
    
};

#endif /* defined(__CS51DigitalSignalProcessor__ApplicationDelegate__) */
