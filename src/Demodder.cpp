#include "Demodder.h"
#include <iostream>

void Demodder::demodulate() {
    while (!quit->load())
    {
        float real0 = 1;
        float imag0 = 1;

        if (sampleQueue->size()) {
            unsigned char* arr = sampleQueue->pop();
            for (int i = 0; i + 1 < 16*32*512; i += 2) {
                float real1 = ((float)arr[i]) - 127.5;
                float imag1 = ((float)arr[i+1]) - 127.5;
                float fmSample = (real0 * (imag1 - imag0)
                                - imag0 * (real1 - real0))
                                /(real0 * real0 + imag0 * imag0);
                real0 = real1;
                imag0 = imag1;
                a.samples[0].push_back(fmSample);
            }
        }
    }
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(256,20e3) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(250000);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
