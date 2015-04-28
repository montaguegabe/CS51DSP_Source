//
//  SoundWave+FFT.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/27/15.
//
//

#include <complex>
#include <math.h>
#include "SoundWave.h"

// Define a complex vector
typedef std::vector<std::complex<AmplitudeType>> ComplexVector;

// Define complex number
typedef std::complex<AmplitudeType> ComplexAmplitude;

// Index type
typedef signed long ComplexSizeType;

// Define imaginary number
std::complex<AmplitudeType> i (0,1);

// Helper function to define omega in FFT function
ComplexAmplitude omega2 (long p, long q)
{
    //convert constants to real part of complex number
    ComplexAmplitude E_real (M_E);
    ComplexAmplitude PI_real (M_PI);
    ComplexAmplitude p_real (p);
    ComplexAmplitude q_real (q);
    ComplexAmplitude two_real (2.0);
    
    //printf("Omega called: %li, %li\n", p, q);
    
    return pow(E_real, (i * (two_real * PI_real) * (q_real / p_real)));
}

static ComplexVector fftRec(ComplexVector& v, ComplexSizeType num, ComplexSizeType everyN, ComplexSizeType offsetN) {
    
    if (num == 1) {
        // Do nothing?
    } else {
        ComplexVector fEven = fftRec(v, num >> 1, everyN << 1, offsetN);
        ComplexVector fOdd = fftRec(v, num >> 1, everyN << 1, offsetN + 1);
        
        for (ComplexSizeType m = offsetN; m < (num * everyN) / 2; m += everyN) {
            long tmp = -m;
            ComplexAmplitude omega = omega2(num, tmp);
            v[m] = fEven[m] + fOdd[m] * omega;
            v[m + (num * everyN) / 2] = fEven[m] - fOdd[m] * omega;
        }
    }
    
    return v;
}

// Define method for turning real vectors to complex, vice versa
static ComplexVector realVectorToComplex(AmplitudeVector v) {
    
    const auto size = v.size();
    ComplexVector newVector (size, i);
    
    for (int i = 0; i < size; i++) {
        newVector[i] = v[i];
    }
    
    return newVector;
}

static AmplitudeVector complexVectorToReal(ComplexVector v) {
    
    const auto size = v.size();
    AmplitudeVector newVector (size, 0);
    
    for (int i = 0; i < size; i++) {
        newVector[i] = v[i].real();
    }
    
    return newVector;
}