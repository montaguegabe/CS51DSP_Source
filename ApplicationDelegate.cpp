//
//  ApplicationDelegate.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "ApplicationDelegate.h"
#include "JuceApplication.h"
#include "MainComponent.h"

// Called when the application delegate is created
ApplicationDelegate::ApplicationDelegate() {
    
    // Put event handlers on the JUCE application
    mJUCEApplication = (CS51DigitalSignalProcessorApplication*) JUCEApplication::getInstance();
    mJUCEApplication->setDelegate(this);
}

// Returns the sole instance of the application delegate
ApplicationDelegate& ApplicationDelegate::getInstance() {
    static ApplicationDelegate instance;
    
    // Instantiated on first use.
    return instance;
}

// Called to initialize the application
void ApplicationDelegate::init(void) {
    
    //TODO: Add GUI elements
    
    // Create main window
    mMainWindow = new MainWindow (mJUCEApplication->getApplicationName(), &mMainComp);
    mMainWindow->setVisible (true);
    
    // Create file-loading button
    mLoadFileButton.setButtonText("Load Audio File");
    mLoadFileButton.setBounds(10, 10, 100, 20);
    mMainComp.addAndMakeVisible (mLoadFileButton);
    
    // Registers the AD to have the buttonClicked function invoked by the button
    mLoadFileButton.addListener(this);
}

// Called when the application must quit
void ApplicationDelegate::shutdown() {
    
    //TODO: Remove all listeners!
    mLoadFileButton.removeListener(this);
    
    // Delete the window by nulling out its pointer (b/c autorelease)
    mMainWindow = nullptr;
}

//TODO: Define callbacks that will be activated when a user interacts with the GUI

// The one callback for any button being pressed
void ApplicationDelegate::buttonClicked (Button* button) {
    
    // Load file button has been pressed
    if (button == &mLoadFileButton) {
        printf("TODO\n");
    }
}

/*void fileSelected(String filename) {
 
// Make sure a valid file has been selected
if (...) return;

// Initialize a sound wave instance, passing the file to the constructor.
mWaveData = SoundWave(filename);

// Check for errors in initialization
if (mWaveData) {
// ...
}
else {
// ...
}
}*/

