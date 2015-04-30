//
//  SoundWave+FFT.cpp
//  CS51DigitalSignalProcessor
//
//  Created by Gabe Montague on 4/27/15.
//
//

#include "SoundWave.h"

#pragma mark Template-based Trigonometric Substitutions

template<unsigned M, unsigned N, unsigned B, unsigned A>
struct SinCosSeries {
    static double value() {
        return 1-(A*M_PI/B)*(A*M_PI/B)/M/(M+1)
        *SinCosSeries<M+2,N,B,A>::value();
    }
};

template<unsigned N, unsigned B, unsigned A>
struct SinCosSeries<N,N,B,A> {
    static double value() { return 1.; }
};

template<unsigned B, unsigned A, typename T=double>
struct Sin;

template<unsigned B, unsigned A>
struct Sin<B,A,float> {
    static float value() {
        return (A*M_PI/B)*SinCosSeries<2,24,B,A>::value();
    }
};
template<unsigned B, unsigned A>
struct Sin<B,A,double> {
    static double value() {
        return (A*M_PI/B)*SinCosSeries<2,34,B,A>::value();
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

#pragma mark Reindexing

// Reverse-binary reindexing function
template <typename T>
static void scramble(T* data, unsigned long n) {
    //n = nn<<1;
    unsigned long j, i, m, nn;
    nn = n >> 1;
    j = 1;
    for (i = 1; i < n; i+=2) {
        if (j > i) {
            std::swap<T>(data[j - 1], data[i - 1]);
            std::swap<T>(data[j], data[i]);
        }
        m = nn;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };
}

#pragma mark Main Algorithm

/*template<unsigned N, typename T=double>
class DanielsonLanczos {
    DanielsonLanczos<N/2,T> next;
public:
    void apply(T* data) {
        next.apply(data);
        next.apply(data+N);
        
        T tempr,tempi,c,s;
        
        for (unsigned i=0; i<N; i+=2) {
            c = cos(i*M_PI/N);
            s = -sin(i*M_PI/N);
            tempr = data[i+N]*c - data[i+N+1]*s;
            tempi = data[i+N]*s + data[i+N+1]*c;
            data[i+N] = data[i]-tempr;
            data[i+N+1] = data[i+1]-tempi;
            data[i] += tempr;
            data[i+1] += tempi;
        }
    }
};*/

template<unsigned N, typename T=double>
class DanielsonLanczos {
    DanielsonLanczos<N/2,T> next;
public:
    void apply(T* data) {
        next.apply(data);
        next.apply(data+N);
        
        T wtemp,tempr,tempi,wr,wi,wpr,wpi;
        wtemp = -Sin<N,1,T>::value();
        wpr = -2.0*wtemp*wtemp;
        wpi = -Sin<N,2,T>::value();
        wr = 1.0;
        wi = 0.0;
        for (unsigned i=0; i<N; i+=2) {
            tempr = data[i+N]*wr - data[i+N+1]*wi;
            tempi = data[i+N]*wi + data[i+N+1]*wr;
            data[i+N] = data[i]-tempr;
            data[i+N+1] = data[i+1]-tempi;
            data[i] += tempr;
            data[i+1] += tempi;
            
            wtemp = wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
    }
};

// For small samples it's faster to use non-optimized, hard-coded version
template<typename T>
class DanielsonLanczos<4,T> {
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
class DanielsonLanczos<2,T> {
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
class DanielsonLanczos<1,T> {
public:
    void apply(T* data) { }
};

template<unsigned P,
typename T=double>
class GFFT {
    enum { N = 1<<P };
    DanielsonLanczos<N,T> recursion;
public:
    void fft(T* data) {
        scramble<T>(data,N);
        recursion.apply(data);
    }
};

#pragma mark Sample Number-Independent Factory Interface

