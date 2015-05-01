//
//  SoundWave+FFT.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/27/15.
//
//

#include "SoundWave.h"
#include "Loki/Typelist.h"
#include "Loki/Factory.h"
#include <exception>
#include <math.h>

#pragma mark Template-based Trigonometric Substitutions

// Recursive template structure for trig functions.
// Caches results of sine/cosine series

template<unsigned M, unsigned N, unsigned B, unsigned A>
struct SinCosSeries {
    static double value() {
        return 1 - (A*M_PI/B) * (A*M_PI/B) / M / (M+1)
        *SinCosSeries<M+2,N,B,A>::value();
    }
};

template<unsigned N, unsigned B, unsigned A>
struct SinCosSeries<N,N,B,A> {
    static double value() { return 1.0; }
};

template<unsigned B, unsigned A, typename T=double>
struct Sin;

template<unsigned B, unsigned A>
struct Sin<B,A,float> {
    static float value() {
        return (A * M_PI / B) * SinCosSeries<2,24,B,A>::value();
    }
};
template<unsigned B, unsigned A>
struct Sin<B,A,double> {
    static double value() {
        return (A*M_PI/B) * SinCosSeries<2,34,B,A>::value();
    }
};

template<unsigned B, unsigned A, typename T=double>
struct Cos;

template<unsigned B, unsigned A>
struct Cos<B,A,float> {
    static float value() {
        return SinCosSeries<1,23,B,A>::value();
    }
};
template<unsigned B, unsigned A>
struct Cos<B,A,double> {
    static double value() {
        return SinCosSeries<1,33,B,A>::value();
    }
};

#pragma mark Main Algorithm

template<unsigned N, typename T=double>
class Radix2DIT {
    Radix2DIT<N/2,T> next;
public:
    void apply(T* data) {
        next.apply(data);
        next.apply(data + N);
        
        T wtemp,tempr,tempi,wr,wi,wpr,wpi;
        wtemp = -Sin<N,1,T>::value();
        wpr = -2.0*wtemp*wtemp;
        wpi = -Sin<N,2,T>::value();
        wr = 1.0;
        wi = 0.0;
        
        for (unsigned i = 0; i < N; i += 2) {
            
            tempr = data[i+N] * wr - data[i+N+1] * wi;
            tempi = data[i+N] * wi + data[i+N+1] * wr;
            data[i+N] = data[i] - tempr;
            data[i+N+1] = data[i+1] - tempi;
            data[i] += tempr;
            data[i+1] += tempi;
            
            wtemp = wr;
            wr += wr * wpr - wi*wpi;
            wi += wi * wpr + wtemp*wpi;
        }
    }
};

// For small samples it's faster to use non-optimized, hard-coded version
template<typename T>
class Radix2DIT<4,T> {
public:
    void apply(T* data) {
        T tr = data[2];
        T ti = data[3];
        data[2] = data[0]-tr;
        data[3] = data[1]-ti;
        data[0] += tr;
        data[1] += ti;
        tr = data[6];
        ti = data[7];
        data[6] = data[5]-ti;
        data[7] = tr-data[4];
        data[4] += tr;
        data[5] += ti;
        
        tr = data[4];
        ti = data[5];
        data[4] = data[0]-tr;
        data[5] = data[1]-ti;
        data[0] += tr;
        data[1] += ti;
        tr = data[6];
        ti = data[7];
        data[6] = data[2]-tr;
        data[7] = data[3]-ti;
        data[2] += tr;
        data[3] += ti;
    }
};

template<typename T>
class Radix2DIT<2,T> {
public:
    void apply(T* data) {
        T tr = data[2];
        T ti = data[3];
        data[2] = data[0]-tr;
        data[3] = data[1]-ti;
        data[0] += tr;
        data[1] += ti;
    }
};

template<typename T>
class Radix2DIT<1,T> {
public:
    void apply(T* data) { }
};

#pragma mark Algorithm Template Implementation

template<typename T>
class AbstractFFT {
public:
    virtual void fft(T*) = 0;
};

class EmptyFFT { };

template<unsigned P, typename T=double,
class FactoryPolicy=EmptyFFT>
class GFFT:public FactoryPolicy {
    enum { N = 1<<P };
    Radix2DIT<N,T> recursion;
    
    // Scrambles the data into input for the Radix2
    // Data starts out as real, imaginary alternations
    void scramble(T* data) {
        int i,m,j=1;
        for (i = 1; i < 2 * N; i += 2) {
            if (j > i) {
                std::swap<T>(data[j-1], data[i-1]);
                std::swap<T>(data[j], data[i]);
            }
            m = N;
            while (m >= 2 && j > m) {
                j -= m;
                m >>= 1;
            }
            j += m;
        }
    }
public:
    enum { id = P };
    static FactoryPolicy* Create() {
        return new GFFT<P,T,FactoryPolicy>();
    }
    void fft(T* data) {
        scramble(data);
        recursion.apply(data);
    }
};

#pragma mark Loki Factory Methods

// Functionality for creating a factory of precompiled "matrices" for the FFT
// operation to use at runtime.

template<class TList>
struct FactoryInit;

template<class H, class T>
struct FactoryInit<Loki::Typelist<H,T> > {
    template<class Fact>
    static void apply(Fact& f) {
        f.Register(H::id,H::Create);
        FactoryInit<T>::apply(f);
    }
};

template<>
struct FactoryInit<Loki::NullType> {
    template<class Fact>
    static void apply(Fact&) { }
};

template<
template<unsigned,class,class> class FFT,
unsigned Begin, unsigned End,
typename T=double,
class FactoryPolicy=AbstractFFT<T> >
struct GFFTList {
    typedef Loki::Typelist<FFT<Begin,T,FactoryPolicy>,
    typename GFFTList<FFT,Begin+1,End,T,
    FactoryPolicy>::Result> Result;
};

template<
template<unsigned,class,class> class FFT,
unsigned End, typename T, class FactoryPolicy>
struct GFFTList<FFT,End,End,T,FactoryPolicy> {
    typedef Loki::NullType Result;
};

#pragma mark Final FFT Function

// NOTE that this function ONLY takes inputs with power of 2 sample numbers
// NOTE TOO that the input vector must be alternating real/complex
static void fftVariableSamplePow2(AmplitudeVector& input, unsigned int powerOf2) {
    
    Loki::Factory<AbstractFFT<AmplitudeType>,unsigned int> gfft_factory;
    FactoryInit<GFFTList<GFFT,10,27>::Result>::apply(gfft_factory);
    AbstractFFT<AmplitudeType>* gfft = gfft_factory.CreateObject(powerOf2);
    
    input.push_back(0);
    gfft->fft(input.data());
}