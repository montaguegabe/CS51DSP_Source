//
//  VectorContentGraph.h
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/23/15.
//
//

#ifndef __CS51DigitalSignalProcessor__VectorContentGraph__
#define __CS51DigitalSignalProcessor__VectorContentGraph__

#include <stdio.h>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Visuals.h"
#include <math.h>
#include <exception>

typedef unsigned long long IndexType;

template <class T>

// This class draws the contents of an std::vector
class VectorContentGraph : public Component {
public:
    
    // Constructor
    VectorContentGraph();
    
    // Sets the vector to draw via pointer
    void setSource(std::vector<T>* input);
    
    // Clears the source of the grapher
    void clear();
    
    // Sets the vertical bounds the grapher
    void setHighLow(T highLow);
    
    // Sets whether 0 should be the bottom of the Y axis
    void setZeroBottom(bool zeroBottom);
    
    // Set the horizontal bounds of the grapher. These are inclusive on left, exclusive on right.
    void setLeft(IndexType left);
    void setSamplesShowing(IndexType samples);
    
    // Accessors for bounds
    T getHighLow();
    IndexType getLeft();
    IndexType getSamplesShowing();
    
private:
    // The source of the grapher. Can be null.
    std::vector<T>* mSource;
    
    // Bound properties
    T mHighLow;
    IndexType mLeft;
    IndexType mSamplesShowing;
    bool mZeroBottom;
    
    // Overrides for component
    void paint(Graphics &g) override;
    void resized() override;
    
    // Overrides for key listener
    bool keyPressed (const KeyPress &key) override;
};

// This class draws the contents of 2D spectrogram stored as a 2D std::vector
template <class T>
class Spectrogram : public Component {
public:
    
    // Constructor
    Spectrogram();
    
    // Sets the vector to draw via pointer
    void setSource(std::vector<std::vector<T>>* input);
    
    void setWhiteAmplitude(T max) { mMaxAmplitude = max; }
    
    // Clears the source of the grapher
    void clear();
    
private:
    // The source of the grapher. Can be null.
    std::vector<std::vector<T>>* mSource;
    
    // Bound properties
    T mMaxAmplitude;
    IndexType mBottom;
    IndexType mTop;
    IndexType mLeft;
    IndexType mRight;
    
    // Overrides
    void paint(Graphics &g) override;
    void resized() override;
};

#include "VectorContentGraphCpp.h"

#endif /* defined(__CS51DigitalSignalProcessor__VectorContentGraph__) */
