#include "FFTFilter.h"
#include "../debug/SampleFilters.h"

compArray* FFTFilter::filter(unsigned char input[ARR_SIZE*2]) {

    for (int i = 0; i < ARR_START; i++) {
        sampleArr[i] = overlap[i];
    }

    for (int i = 0; i < ARR_SIZE*2; i+=2) {
        sampleArr[ARR_START+i/2] = std::complex<double>(double(input[i])-127.5, double(input[i+1])-127.5);
        sampleArr[ARR_SIZE+i/2] = 0.0;
    }

    for (int i = 0; i < ARR_START; i++) {
        overlap[i] = sampleArr[ARR_SIZE+i];
    }

    fftw_execute(p);

    for (int i = 0; i < ARR_SIZE*2; i++) {
        sampleArr[i] *= filterOut[i];
    }

    fftw_execute(ip);

    for (int i = 0; i < ARR_END; i++) {
        sampleArr[i] /= abs(sampleArr[i]);
    }

    return &sampleArr;
}

FFTFilter::FFTFilter(unsigned int filterLength, int freqCutoff) 
: length(filterLength), cutoff(freqCutoff) {
    std::cout << "Initializing fft-filter" << std::endl;
    p  = fftw_plan_dft_1d(ARR_SIZE*2, reinterpret_cast<fftw_complex*>(&sampleArr[0]), reinterpret_cast<fftw_complex*>(&sampleArr[0]), FFTW_FORWARD, FFTW_ESTIMATE);
    ip = fftw_plan_dft_1d(ARR_SIZE*2, reinterpret_cast<fftw_complex*>(&sampleArr[0]), reinterpret_cast<fftw_complex*>(&sampleArr[0]), FFTW_BACKWARD, FFTW_ESTIMATE);

    std::array<double,2*ARR_SIZE> filterIn;
    fftw_plan fp = fftw_plan_dft_r2c_1d(ARR_SIZE*2, filterIn.data(), reinterpret_cast<fftw_complex*>(&filterOut[0]), FFTW_ESTIMATE);

    filterIn.fill(0.0);
    for (int i = 0; i < 513; i++) {
        filterIn[i] = filterVals[i];
    }

    fftw_execute(fp);

    fftw_destroy_plan(fp);

    for (int i = ARR_SIZE; i < ARR_SIZE*2; i++) {
        std::complex<double> symm = filterOut[ARR_SIZE*2-i-1];
        filterOut[i] = std::conj(symm);
    }
    overlap.fill(1);
    
    std::cout << "Finished initializing fft-filter" << std::endl;
}
