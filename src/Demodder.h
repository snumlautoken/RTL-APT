#pragma once
#include <complex>
#include <vector>
#include <queue>
#include <atomic>
#include <array>
#include "../debug/AudioFile.h"
#include "IQueue.h"

class Demodder {
    private:
    IQueue<std::array<u_char, 16*32*512>>* sampleQueue;
    std::atomic<bool>* quit;
    u_int decimate = 4;
    public:
    AudioFile<float> a;
    Demodder(IQueue<std::array<u_char, 16*32*512>>* q, std::atomic<bool> * quit);
    ~Demodder();
    void bufferToComplex();
    void demodulate();
    std::vector<float> fmSamples;
};
