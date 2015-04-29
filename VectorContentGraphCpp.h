//
//  VectorContentGraph.tpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/23/15.
//
//  Should not be compiled!
//

#include "VectorContentGraph.h"
#include "Visuals.h"
#include <exception>
#include <math.h>

#pragma mark Vector Content Graph

// Constructor
template <class T>
VectorContentGraph<T>::VectorContentGraph()
{
    mSource = nullptr;
    mHighLow = 2;
    mLeft = 0;
    mSamplesShowing = 100;
    mZeroBottom = false;
    this->setWantsKeyboardFocus(true);
}

// Sets the vector to draw via pointer
template <class T>
void VectorContentGraph<T>::setSource(std::vector<T>* input) {
    
    if (!input) {
        throw std::invalid_argument("Tried to init graph with nullptr.");
    } else {
        mSource = input;
        
        // Size the bounds according to size
        mLeft = 0;
        mSamplesShowing = input->size();
        
        // Paint
        this->repaint();
        
    }
}

// Clears the source of the grapher
template <class T>
void VectorContentGraph<T>::clear() {
    mSource = nullptr;
}

// Sets the vertical bounds the grapher
template <class T>
void VectorContentGraph<T>::setHighLow(T highLow) {
    mHighLow = highLow;
    repaint();
}

template <class T>
void VectorContentGraph<T>::setZeroBottom(bool zeroBottom) {
    mZeroBottom = zeroBottom;
    repaint();
}

// Set the horizontal bounds of the grapher. These are inclusive on left, exclusive on right.
template <class T>
void VectorContentGraph<T>::setLeft(IndexType left) {
    mLeft = left;
    repaint();
}

template <class T>
void VectorContentGraph<T>::setSamplesShowing(IndexType samples) {
    mSamplesShowing = samples;
    repaint();
}

// Accessors for bounds
template <class T>
T VectorContentGraph<T>::getHighLow() { return mHighLow; }

template <class T>
IndexType VectorContentGraph<T>::getLeft() { return mLeft; }

template <class T>
IndexType VectorContentGraph<T>::getSamplesShowing() { return mSamplesShowing; }

// Component overrides

// The painting operation
static IndexType xToIndex (float x, float pixelWidth, IndexType sampleWidth, IndexType sampleLeft) {
    float xScalar = x / pixelWidth;
    return sampleLeft + ((IndexType) (sampleWidth * xScalar));
}

template <class T>
void VectorContentGraph<T>::paint(Graphics &g)  {
    
    g.fillAll(graphBgColor);
    
    // Calculate the point x offset and middle y
    float yMiddle = (getHeight()) / 2;
    float width = getWidth();
    float height = getHeight();
    
    g.setColour (graphPointColor);
    
    if (mSource) {
        
        // Iterate through the source vector
        IndexType totalSamples = mSource->size();
        
        // Calculate index change
        IndexType deltaI = xToIndex(graphPixelOffset, getWidth(), mSamplesShowing, 0);
        if (deltaI < 1) deltaI = 1;
        
        float previousY = yMiddle;
        
        for (int x = 0, i = mLeft; x < width; x += graphPixelOffset, i+= deltaI) {
            
            if (i >= 0 && i < totalSamples) {
                
                // Cleared for drawing
                float value = (mSource->at(i));
                
                float yOffset = yMiddle * (value / ((float) (mHighLow)));
                float y = mZeroBottom ? height - yOffset: yMiddle - yOffset;
                
                if (x > graphPointSize && x < width - graphPointSize && y > graphPointSize && y < height - graphPointSize)
                    g.fillEllipse (x - graphPointSize / 2, y - graphPointSize / 2, graphPointSize, graphPointSize);
                g.drawLine(x - graphPixelOffset, previousY, x, y);
                
                previousY = y;
            }
        }
        
    } else {
        // Draw a flat line or some other indicator
        g.setColour(Colours::red);
        g.drawLine(0, yMiddle, width, yMiddle);
        
    }
}

// Interaction constants
#define HighLowChangeFactor 1.5
#define WindowChangeAmount 0.05

// Listener overrides
template <class T>
bool VectorContentGraph<T>::keyPressed (const KeyPress &key) {
    
    if (key == KeyPress::upKey) {
        setHighLow(mHighLow * HighLowChangeFactor);
    }
    else if (key == KeyPress::downKey) {
        setHighLow(mHighLow / HighLowChangeFactor);
    }
    else if (key == KeyPress::leftKey) {
        auto change = mSamplesShowing * WindowChangeAmount;
        if (mLeft >= change) setLeft(mLeft - change);
        else setLeft(0);
    }
    else if (key == KeyPress::rightKey) {
        auto change = mSamplesShowing * WindowChangeAmount;
        setLeft(mLeft + change);
    }
    
    // Consume event
    return true;
}

// The resize operation
template <class T>
void VectorContentGraph<T>::resized() {
    this->repaint();
}

#pragma mark Spectrogram

// Constructor
template <class T>
Spectrogram<T>::Spectrogram() {
    mSource = nullptr;
    mMaxAmplitude = 128;
    mBottom = 0;
    mTop = 100;
    mLeft = 0;
    mRight = 100;
}

// Sets the vector to draw via pointer
template <class T>
void Spectrogram<T>::setSource(std::vector<std::vector<T>>* input) {
    
    if (!input) {
        throw std::invalid_argument("Tried to init graph with nullptr.");
    } else {
        mSource = input;
        
        // Size the bounds according to size
        mLeft = 0;
        mRight = input->size();
        mTop = 0;
        mBottom = input->at(0).size();
        
        // Paint
        this->repaint();
        
    }
}

template <class T>
void Spectrogram<T>::paint(Graphics &g) {
    
    g.fillAll(graphBgColor);
    
    // Calculate the point x offset and middle y
    float xOffset = ((float) this->getWidth()) / (mRight - mLeft);
    float yOffset = ((float) this->getHeight()) / (mBottom - mTop);
    
    if (mSource) {
        
        // Iterate through the source vector
        IndexType sizeI = mSource->size();
        IndexType maxIndexI = mRight > sizeI ? sizeI : mRight;
        IndexType sizeJ = mSource->at(0).size();
        IndexType maxIndexJ = mBottom > sizeJ ? sizeJ : mBottom;
        
        for (IndexType i = mLeft; i < maxIndexI; i++) {
            
            std::vector<T> heightVector = mSource->at(i);
            
            // Check correct length
            if (heightVector.size() != sizeJ)
                throw (std::invalid_argument("2D vector has variable height."));
            
            float x = i * xOffset;
            
            for (IndexType j = 0; j < maxIndexJ; j++) {
                
                float y = j * yOffset;
                
                float scalar = ((float) heightVector.at(j)) / mMaxAmplitude;
                g.setColour(Colour::fromHSV(0.0f, 0.0f, scalar, 1.0f));
                auto rect = Rectangle<float>(x, y, xOffset, yOffset);
                g.fillRect(rect);
            }
        }
        
    } else {
        // Empty indicator
        
    }
}

template <class T>
void Spectrogram<T>::resized() {
    this->repaint();
}

