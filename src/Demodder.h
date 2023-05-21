#pragma once
#include <vector>
#include <atomic>
#include <array>
#include <memory>
#include "../debug/AudioFile.h"
#include "FFTFilter.h"
#include "IQueue.h"

class Demodder {
    private:
    IQueue<unsigned char*>* sampleQueue;
    std::atomic<bool>* quit;
    std::vector<float> fmSamples;
    std::unique_ptr<FFTFilter> filter;
    public:
    AudioFile<float> a;
    Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit);
    ~Demodder();
    void demodulate();
};
