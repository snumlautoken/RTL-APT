#include "../src/Demodder.h"
#include "../src/FFTFilter.h"
#include <iostream>
#include <ctime>
#include <memory>

void Demodder::demodulate() {
    std::ifstream inFile("xab", std::ios::binary);
    u_char* buf = (u_char*)malloc(ARR_SIZE*2);
    while (true) {
        inFile.read((char*)buf, 2*ARR_SIZE);
        if (inFile.rdstate() & inFile.eofbit) {break;}

        compArray* arr = filter->filter(buf);

        for (u_long i = ARR_START; i < ARR_END-1; i++) {
            double real0 = (*arr)[i].real();
            double imag0 = (*arr)[i].imag();
            double real1 = (*arr)[i+1].real();
            double imag1 = (*arr)[i+1].imag();
            double fmSample = (real0 * (imag1 - imag0)
                            - imag0 * (real1 - real0))
                            /(real0 * real0 + imag0 * imag0);
            if (i % decimate == 0)
                a.samples[0].push_back(fmSample);
        }
    }

    std::cout << "FINISHED" << std::endl;
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(new FFTFilter(0,0)) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(250000);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
