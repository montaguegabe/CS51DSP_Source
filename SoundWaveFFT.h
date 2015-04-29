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
typedef ComplexVector::size_type ComplexSizeType;

// Define imaginary number
std::complex<AmplitudeType> i (0,1);

#define M_PI 3.14159265358979323846264338327950288

// Helper function to define omega in FFT function
ComplexAmplitude omega(ComplexSizeType p, ComplexSizeType q)
{
    //convert constants to real part of complex number
    ComplexAmplitude pComplex (p);
    ComplexAmplitude qComplex (q);
    
    //printf("Omega called: %li, %li\n", p, q);
    
    ComplexAmplitude exponent = (i * 2.0 * M_PI * qComplex) / pComplex;
    return std::exp(exponent);
}

ComplexVector even(ComplexVector input) {
    ComplexVector result;
    ComplexSizeType n = input.size();
    for (int i = 0; i < n; i += 2) {
        result.push_back(input[i]);
    }
    return result;
}

ComplexVector odd(ComplexVector input) {
    ComplexVector result;
    ComplexSizeType n = input.size();
    for (int i = 1; i < n; i += 2) {
        result.push_back(input[i]);
    }
    return result;
}

ComplexVector fft(ComplexVector input) {
    
    ComplexVector::size_type n = input.size();
    
    if (n == 1) {
        ComplexVector result(n, input[0]);
        return result;
    }
    else {
        ComplexVector evens = even(input);
        ComplexVector odds = odd(input);
        ComplexVector fEven;
        fEven = fft(evens);
        ComplexVector fOdd;
        fOdd = fft(odds);
        
        ComplexVector result (n, 0);
        for (int i = 0; i < n / 2; i++) {
            ComplexAmplitude omega2 = omega(n, -i);
            result[i] = fEven[i] + omega2 * fOdd[i];
            result[i + n / 2] = fEven[i] - omega2 * fOdd[i];
        }
        
        return result;
    }
}

// Define method for turning real vectors to complex, vice versa
ComplexVector realVectorToComplex(AmplitudeVector v) {
    
    const auto size = v.size();
    ComplexVector newVector (size, i);
    
    for (int i = 0; i < size; i++) {
        newVector[i] = v[i];
    }
    
    return newVector;
}

AmplitudeVector complexVectorToReal(ComplexVector v) {
    
    const auto size = v.size();
    AmplitudeVector newVector (size, 0);
    
    for (int i = 0; i < size; i++) {
        newVector[i] = v[i].real();
    }
    
    return newVector;
}