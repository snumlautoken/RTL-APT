#pragma once
#include <complex>
#include <fftw3.h>
#include <array>
#include <iostream>

const int ARR_SIZE = 8*32*512;

typedef std::array<std::complex<double>,2*ARR_SIZE> compArray;

class FFTFilter {
    private:
    unsigned int sampleRate;
    unsigned int length;
    int cutoff;
    compArray sampleArr, filterOut;
    fftw_plan p, ip;
    public:
    compArray filter(unsigned char input[ARR_SIZE*2]);
    FFTFilter(unsigned int filterLength, int freqCutoff);
};
