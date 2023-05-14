#include "Demodder.h"
#include <iostream>

void Demodder::bufferToComplex() {
    while (!quit->load()) {
        if (1 < sampleQueue->size()) {
            float iS = ((float) sampleQueue->front()) - 127.5;
            sampleQueue->pop();
            float qS = ((float) sampleQueue->front()) - 127.5;
            sampleQueue->pop();
            iQueue.push(std::complex<float>(iS, qS));
        }
    }
}

void Demodder::demodulate() {
    while (!quit->load())
    {
        if (1 < iQueue.size()) {
            std::complex<float> iq1 = iQueue.front();
            iQueue.pop();
            std::complex<float> iq0 = iQueue.front();
            float fmSample = (iq0.real()*(iq1.imag() - iq0.imag())
                            -iq0.imag()*(iq1.real()-iq0.real()))
                            /(iq0.real()*iq0.real()+iq0.imag()*iq0.imag());
            a.samples[0].push_back(fmSample);
        }

    }
}

Demodder::Demodder(IQueue<u_char>* q, std::atomic<bool> * quit) : quit(quit) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(2400000);
}

Demodder::~Demodder() {
    std::cout << a.samples[0].size() << std::endl;
    a.save("Test.wav", AudioFileFormat::Wave);

}
