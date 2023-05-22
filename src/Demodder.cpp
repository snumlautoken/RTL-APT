#include "Demodder.h"
#include <iostream>

void Demodder::demodulate() {
    double real0 = 1;
    double imag0 = 1;
    while (!quit->load())
    {
        if (sampleQueue->size()) {
            unsigned char* buf = sampleQueue->pop();
            std::cout << "\rCongestion: " << sampleQueue->size() << " " << std::flush;
            std::array<std::complex<double>, 2*ARR_SIZE> arr = filter->filter(buf);
            for (int i = 0; i + 1 < ARR_SIZE; i += decimate) {
                double real1 = arr[i].real();
                double imag1 = arr[i].imag();
                double fmSample = (real0 * (imag1 - imag0)
                                - imag0 * (real1 - real0))
                                /(real0 * real0 + imag0 * imag0);
                real0 = real1;
                imag0 = imag1;
                if (i % 10 == 0)
                    a.samples[0].push_back(fmSample);
            }
        }
    }
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(new FFTFilter(0,0)) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(250000/decimate);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
