#include <complex>
#include <fftw3.h>
#include <array>
#include <iostream>

const int ARR_SIZE = 8*32*512;

class FFTFilter {
    private:
    unsigned short decimation = 1;
    unsigned int sampleRate;
    unsigned int length;
    int cutoff;
    std::array<std::complex<double>,ARR_SIZE> in, out;
    fftw_plan p;
    fftw_plan ip;
    public:
    std::array<std::complex<double>, ARR_SIZE> filter(unsigned char input[ARR_SIZE*2]);
    FFTFilter(unsigned int filterLength, int freqCutoff);
};
