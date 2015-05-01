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
#include "DSPEffects.h"

#include <math.h>
#include <string>

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
    
    // Create label with name of audio file
    mAudioTitleText.setColour(mAudioTitleText.textColourId, textColor);
    mAudioTitleText.setText("CS51 Digital Signal Processor by Gabe, Peter, and Michael", dontSendNotification);
    mAudioTitleText.setBounds(10, 10, 790, 30);
    mMainComp.addAndMakeVisible(mAudioTitleText);
    
    // Create FF label
    mFFText.setColour(mAudioTitleText.textColourId, textColor);
    mFFText.setText("FF: ", dontSendNotification);
    mFFText.setBounds(10, 110, 100, 20);
    mMainComp.addAndMakeVisible(mFFText);
    
    // Create file-loading button
    mLoadFileButton.setButtonText("Load Audio File");
    mLoadFileButton.setBounds(10, 50, 100, 20);
    mMainComp.addAndMakeVisible (mLoadFileButton);
    
    // Create play button
    mPlayButton.setButtonText("Play");
    mPlayButton.setBounds(10, 80, 100, 20);
    mMainComp.addAndMakeVisible (mPlayButton);
    
    // Create volume up button
    mplusButton.setButtonText("Vol +");
    mplusButton.setBounds(10, 140, 100, 20);
    mMainComp.addAndMakeVisible (mplusButton);
    
    // Create volume down button
    mminusButton.setButtonText("Vol -");
    mminusButton.setBounds(10, 170, 100, 20);
    mMainComp.addAndMakeVisible (mminusButton);
    
    // Create remove noise button
    mNoiseButton.setButtonText("Remove Noise");
    mNoiseButton.setBounds(10, 200, 100, 20);
    mMainComp.addAndMakeVisible (mNoiseButton);
    
    // Create delay button
    mDelayButton.setButtonText("Add Delay");
    mDelayButton.setBounds(10, 230, 100, 20);
    mMainComp.addAndMakeVisible (mDelayButton);
    
    // Create a vector content graph for the amplitude-time
    mAmplitudeTimeView.setBounds(120, 50, 670, 100);
    mMainComp.addAndMakeVisible (mAmplitudeTimeView);
    
    // Create a vector content graph for the amplitude-freq
    mAmplitudeFrequencyView.setBounds(120, 160, 670, 100);
    mAmplitudeFrequencyView.setZeroBottom(true);
    mMainComp.addAndMakeVisible (mAmplitudeFrequencyView);
    
    // Create spectrogram
    mSpectrogram.setBounds(120, 270, 300, 300);
    mMainComp.addAndMakeVisible(mSpectrogram);
    
    // Registers the AD to have the buttonClicked function invoked by the button
    mLoadFileButton.addListener(this);
    mPlayButton.addListener(this);
    mplusButton.addListener(this);
    mminusButton.addListener(this);
    mNoiseButton.addListener(this);
    mDelayButton.addListener(this);
}

// Called when the application must quit
void ApplicationDelegate::shutdown() {
    
    //TODO: Remove all listeners!
    mLoadFileButton.removeListener(this);
    mPlayButton.removeListener(this);
    mplusButton.removeListener(this);
    mminusButton.removeListener(this);
    mNoiseButton.removeListener(this);
    mDelayButton.removeListener(this);
    
    // Delte our sound wave object
    mWaveData = nullptr;
    
    // Delete the window by nulling out its pointer (b/c autorelease)
    mMainWindow = nullptr;
}

//TODO: Define callbacks that will be activated when a user interacts with the GUI

// The one callback for any button being pressed
void ApplicationDelegate::buttonClicked (Button* button) {
    
    if (button != &mLoadFileButton && !mWaveData) return;
    
    // Load file button has been pressed
    if (button == &mLoadFileButton) {
        FileChooser myChooser ("Choose a WAV audio file",
                               File::getSpecialLocation (File::userHomeDirectory),
                               "*.wav");
        
        if (myChooser.browseForFileToOpen())
        {
            // Convert File to string.
            File audioFile (myChooser.getResult());
            String path = audioFile.getFullPathName();
            
            // Free the old sound wave
            mWaveData = nullptr;
            
            // Initialize a sound wave instance, passing the file to the constructor.
            mWaveData = new SoundWave(path);
            
            // Check for errors in initialization
            if (mWaveData->errorDuringInit()) {
                
                // Free the mWaveData object by nilling it out.
                mWaveData = nullptr;
                mAudioTitleText.setText("Error loading file.",
                                        dontSendNotification);
            }
            else {
                
                // Set the text to match
                mAudioTitleText.setText(audioFile.getFileNameWithoutExtension(),
                                        dontSendNotification);
                
                // Update the graphs to be connected to the SoundWave object
                auto vectorPointer = &(mWaveData->getAmplitudeTimeVector());
                mAmplitudeTimeView.setSource(vectorPointer);
                vectorPointer = &(mWaveData->getAmplitudeFrequencyVector());
                mAmplitudeFrequencyView.setSource(vectorPointer);
                
                auto vector2DPointer = &(mWaveData->getSpectrogramData());
                mSpectrogram.setSource(vector2DPointer);
                
                // Update the FF labeling
                String ff = "FF: " + mWaveData->getNote();
                mFFText.setText(ff, dontSendNotification);
                mAmplitudeFrequencyView.setFreqHilite(mWaveData->getFFIndex());
            }
        }
    }
    else if (button == &mPlayButton) {
        if (mWaveData) {
            mMainComp.playVector(mWaveData->getAmplitudeTimeVector(), mWaveData->getSampleRate());
        }
    }
    else if (button == &mplusButton) {
        VolumeChangeEffect effect (1.0f);
        SoundWave* waveData = mWaveData;
        effect.apply(*waveData);
    }
    
    else if (button == &mminusButton) {
        VolumeChangeEffect effect (-1.0f);
        SoundWave* waveData = mWaveData;
        effect.apply(*waveData);
    }
    
    else if (button == &mNoiseButton) {
        CompressorEffect effect (-1.0f, 2.0f);
        SoundWave* waveData = mWaveData;
        effect.apply(*waveData);
        
        // Mark for recalculation
        mWaveData->recalcFourier();
    }
    
    else if (button == &mDelayButton) {
        DelayEffect effect (0.5f, 0.5f);
        SoundWave* waveData = mWaveData;
        effect.apply(*waveData);
        
        mWaveData->recalcFourier();
    }
    
    // Update graphs
    mAmplitudeFrequencyView.repaint();
    mAmplitudeTimeView.repaint();
    mSpectrogram.repaint();
}
