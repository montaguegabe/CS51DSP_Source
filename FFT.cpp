//
//  FFT.cpp
//  
//
//  Created by Peter Della-Rocca on 4/22/15.
//
//

#include "FFT.h"
#include <complex>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//define imaginary number
complex<float> i (0,1);


//helper function to return even indices
vector<complex<float>> even (vector<complex<float>> input_even)
{
    int length_even = input_even.size();
    vector<complex<float>> return_even ((length_even/2), 0);
    for (int j = 0; j < length_even; j += 2)
    {
        return_even[j/2] = input_even[j];
    }
    return return_even;
}

//helper function to return odd indices
vector<complex<float>> odd (vector<complex<float>> input_odd)
{
    int length_odd = input_odd.size();
    vector<complex<float>> return_odd ((length_odd/2), 0);
    for (int j = 1; j < length_odd; j++)
    {
        if (j % 2 == 0)
            continue;
        else
            return_odd[j] = input_odd[j];
    }
    return return_odd;
}

//helper function to define omega in FFT function
complex<float> omega (float p, float q)
{
    //convert constants to real part of complex number
    complex<float> E_real (M_E);
    complex<float> PI_real (M_PI);
    complex<float> p_real (p);
    complex<float> q_real (q);
    complex<float> two_real (2.0);
    
    return pow(E_real, (i * (two_real*PI_real)*(q_real/p_real)));
}

//define FFT
vector<complex<float>> fft (vector<complex<float>> inputvector)
{
    int n = inputvector.size();
    vector<complex<float>> combined (n, (0));
    if (n == 1)
        return vector<complex<float>> (1, (n));
    else
    {
        vector<complex<float>> fourierEven;
        fourierEven = fft(even(inputvector));
        vector<complex<float>> fourierOdd;
        fourierOdd = fft(odd(inputvector));
        for (int m = 0; m < (n/2); m++)
        {
            combined[m] = fourierEven[m] + omega(n, -m) * fourierOdd[m];
            combined[m +n/2] = fourierEven[m] - omega(n, -m) * fourierOdd[m];
        }
    }
    return combined;
}