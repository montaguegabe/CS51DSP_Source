//
//  MainWindow.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/12/15.
//
//

#include "MainWindow.h"
#include "MainComponent.h"
#include "Visuals.h"

MainWindow::MainWindow (String name, Component* mainContent): DocumentWindow (name,
                  Colours::lightgrey,
                  DocumentWindow::allButtons) {
    setUsingNativeTitleBar (true);
    setContentOwned(mainContent, true);
    setResizable (false, false);
    centreWithSize (windowWidth, windowHeight);
}

// This is called when the user tries to close this window.
void MainWindow::closeButtonPressed() {
    JUCEApplication::getInstance()->systemRequestedQuit();
}