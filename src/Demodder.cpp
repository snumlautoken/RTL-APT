#include "Demodder.h"
#include <iostream>

void Demodder::demodulate() {
    while (!quit->load())
    {
        double real0 = 1;
        double imag0 = 1;

        if (sampleQueue->size()) {
            unsigned char* buf = sampleQueue->pop();
            std::array<std::complex<double>, 2*ARR_SIZE> arr = filter->filter(buf);
            for (int i = 0; i + 1 < ARR_SIZE; i += 10) {
                double real1 = arr[i].real();
                double imag1 = arr[i].imag();
                double fmSample = (real0 * (imag1 - imag0)
                                - imag0 * (real1 - real0))
                                /(real0 * real0 + imag0 * imag0);
                real0 = real1;
                imag0 = imag1;
                a.samples[0].push_back(fmSample);
            }
        }
    }
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(new FFTFilter(0,0)) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(25000);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
