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
    unsigned int decimate = 1;
    IQueue<unsigned char*>* sampleQueue;
    std::atomic<bool>* quit;
    std::vector<double> fmSamples;
    std::unique_ptr<FFTFilter> filter;
    public:
    AudioFile<double> a;
    Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit);
    ~Demodder();
    void demodulate();
};
