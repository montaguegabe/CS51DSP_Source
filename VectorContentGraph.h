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

typedef unsigned long long IndexType;

template <class T>

// This class draws the contents of an std::vector
class VectorContentGraph : public Component {
public:
    
    // Constructor
    VectorContentGraph() {
        mSource = nullptr;
        mHighLow = 128;
        mLeft = 0;
        mRight = 100;
    }
    
    // Sets the vector to draw via pointer
    void setSource(std::vector<T>* input) {
        
        if (!input) {
            throw std::invalid_argument("Tried to init graph with nullptr.");
        } else {
            mSource = input;
            
            // Size the bounds according to size
            mLeft = 0;
            mRight = input->size();
            
            // Paint
            this->repaint();
            
        }
    }
    
    // Clears the source of the grapher
    void clear();
    
    // Sets the vertical bounds the grapher
    void setHighLow(T highLow);
    
    // Set the horizontal bounds of the grapher. These are inclusive on left, exclusive on right.
    void setHorizontalBounds(IndexType left,
                             IndexType right);
    
    // Accessors for bounds
    T getHighLow();
    IndexType getLeft();
    IndexType getRight();
    
private:
    // The source of the grapher. Can be null.
    std::vector<T>* mSource;
    
    // Bound properties
    T mHighLow;
    IndexType mLeft;
    IndexType mRight;
    
    // Overrides
    // TODO: Figure out how to put these things in cpp file
    void paint(Graphics &g) override {
        
        printf("\nPAINT");
        
        g.fillAll(graphBgColor);
        
        // Calculate the point x offset and middle y
        float xOffset = this->getWidth() / (mRight - mLeft);
        float yMiddle = this->getHeight() / 2;
        
        printf("\n%f", yMiddle);
        
        if (mSource) {
            
            // Iterate through the source vector
            IndexType size = mSource->size();
            IndexType maxIndex = mRight > size ? size : mRight;
            
            for (IndexType i = mLeft; i < maxIndex; i++) {
                
                float x = i * xOffset;
                float value = (float) mSource->at(i);
                
                float yOffset = yMiddle * (value / ((float) mHighLow));
                float y = yMiddle + yOffset;
                
                g.setColour (graphPointColor);
                g.fillEllipse (x, y, graphPointSize, graphPointSize);
            }
            
        } else {
            // Draw a flat line or some other indicator
            
        }
    }
    void resized() override {
        printf("\nRESIZE");
        this->repaint();
    }
};

#endif /* defined(__CS51DigitalSignalProcessor__VectorContentGraph__) */
