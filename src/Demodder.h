#pragma once
#include <vector>
#include <atomic>
#include <array>
#include "../debug/AudioFile.h"
#include "IQueue.h"
#include "FFTFilter.h"

class Demodder {
    private:
    IQueue<unsigned char*>* sampleQueue;
    std::atomic<bool>* quit;
    std::vector<float> fmSamples;
    std::array<float,16*32*512> convolve(unsigned char iqBuf[], const float filter[]);
    FFTFilter filter;
    public:
    AudioFile<float> a;
    Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit);
    ~Demodder();
    void demodulate();
};
