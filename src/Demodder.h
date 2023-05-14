#pragma once
#include <complex>
#include <vector>
#include <queue>
#include <atomic>
#include "../debug/AudioFile.h"
#include "IQueue.h"

class Demodder {
    private:
    IQueue<u_char>* sampleQueue;
    IQueue<std::complex<float>> iQueue;
    std::atomic<bool>* quit;
    public:
    AudioFile<float> a;
    Demodder(IQueue<u_char>* q, std::atomic<bool> * quit);
    ~Demodder();
    void bufferToComplex();
    void demodulate();
    std::vector<float> fmSamples;
};
