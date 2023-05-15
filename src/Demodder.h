#pragma once
#include <complex>
#include <vector>
#include <queue>
#include <atomic>
#include "../debug/AudioFile.h"
#include "IQueue.h"

class Demodder {
    private:
    IQueue<unsigned char*>* sampleQueue;
    std::atomic<bool>* quit;
    u_int decimate = 4;
    public:
    AudioFile<float> a;
    Demodder(IQueue<unsigned char*>* q, std::atomic<bool> * quit);
    ~Demodder();
    void bufferToComplex();
    void demodulate();
    std::vector<float> fmSamples;
};
