//
//  VectorContentGraph.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/23/15.
//
//

#include "VectorContentGraph.h"
#include "Visuals.h"
#include <exception>

#pragma mark Vector Content Graph

// Sets the vector to draw via pointer
/*template <class T>
void VectorContentGraph<T>::setSource(std::vector<T>* input) {
    
    if (!input) {
        throw std::invalid_argument("Tried to init graph with nullptr.");
    } else {
        mSource = input;
        
        // Size the bounds according to size
        mLeft = 0;
        mRight = input->size();
        
        // Paint
        this->paint();
    }
}*/

// Clears the source of the grapher
template <class T>
void VectorContentGraph<T>::clear() {
    mSource = nullptr;
}

// Sets the vertical bounds the grapher
template <class T>
void VectorContentGraph<T>::setHighLow(T highLow) {
    mHighLow = highLow;
}

// Set the horizontal bounds of the grapher. These are inclusive on left, exclusive on right.
template <class T>
void VectorContentGraph<T>::setHorizontalBounds(IndexType left,
                                                IndexType right) {
    mLeft = left;
    mRight = right;
}

// Accessors for bounds
template <class T>
T VectorContentGraph<T>::getHighLow() { return mHighLow; }

template <class T>
IndexType VectorContentGraph<T>::getLeft() { return mLeft; }

template <class T>
IndexType VectorContentGraph<T>::getRight() { return mRight; }


#pragma mark Component Overrides

// The painting operation
/*template <class T>
void VectorContentGraph<T>::paint(Graphics &g) {
    g.fillAll(graphBgColor);
    
    // Calculate the point x offset and middle y
    float xOffset = this->getWidth() / (mRight - mLeft);
    float yMiddle = this->getHeight() / 2;
    
    if (mSource) {
        
        // Iterate through the source vector
        for (IndexType i = mLeft; i < mRight; i++) {
            
            float x = i * xOffset;
            float y = yMiddle + yMiddle * (mSource[i] / mHighLow);
            
            g.setColour (graphPointColor);
            g.fillEllipse (x, y, graphPointSize, graphPointSize);
        }
        
    } else {
        // Draw a flat line or some other indicator
        
    }
}

// The resize operation
template <class T>
void VectorContentGraph<T>::resized() {
    this->paint();
}
 */
