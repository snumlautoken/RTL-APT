#include "Demodder.h"
#include <iostream>

void Demodder::demodulate() {
    float real0 = 1;
    float imag0 = 1;
    while (!quit->load())
    {
        if (sampleQueue->size()) {
            unsigned char* arr = sampleQueue->pop();
            for (int i = 0; i + 1 < 16*32*512; i += 2*decimate) {
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

Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool> * quit) : quit(quit) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(2400000/decimate);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
