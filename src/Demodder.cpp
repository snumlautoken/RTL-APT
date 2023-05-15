#include "Demodder.h"
#include <iostream>

void Demodder::demodulate() {
    while (!quit->load())
    {
        if (sampleQueue->size()) {
            std::array<u_char, 16*32*512> arr = sampleQueue->front();
            sampleQueue->pop();
            for (int i = 0; i + 3 < 16*32*512; i += 2) {
                float real0 = ((float)arr[i]) - 127.5;
                float imag0 = ((float)arr[i+1]) - 127.5;
                float real1 = ((float)arr[i+2]) - 127.5;
                float imag1 = ((float)arr[i+3]) - 127.5;
                float fmSample = (real0 * (imag1 - imag0)
                                - imag0 * (real1 - real0))
                                /(real0 * real0 + imag0 * imag0);
                a.samples[0].push_back(fmSample);
            }
        }
    }
}

Demodder::Demodder(IQueue<std::array<u_char, 16*32*512>>* q, std::atomic<bool> * quit) : quit(quit) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(2400000);
}

Demodder::~Demodder() {
    std::cout << a.samples[0].size() << std::endl;
    a.save("Test.wav", AudioFileFormat::Wave);

}
