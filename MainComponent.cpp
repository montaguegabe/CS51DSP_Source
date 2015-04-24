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
}

MainContentComponent::~MainContentComponent() {

}

void MainContentComponent::paint (Graphics& g) {
    
    // Drawing code goes here
    g.fillAll (Colours::black);
}