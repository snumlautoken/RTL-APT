#include "../src/Demodder.h"
#include "../src/FFTFilter.h"
#include <iostream>
#include <ctime>
#include <memory>

void Demodder::demodulate() {
    double real0 = 1;
    double imag0 = 1;
    std::ifstream inFile("test.bin", std::ios::binary);
    u_char* buf = (u_char*)malloc(ARR_SIZE*2);
    while (true) {
        inFile.read((char*)buf, 2*ARR_SIZE);
        if (inFile.rdstate() & inFile.eofbit) {break;}

        std::cout << std::hex << std::showbase << buf[0] << std::endl;

        compArray* arr = filter->filter(buf);

        for (u_long i = 0; i < ARR_SIZE; i += 1) {
            double real1 = (*arr)[i].real();
            double imag1 = (*arr)[i].imag();
            double fmSample = (real0 * (imag1 - imag0)
                            - imag0 * (real1 - real0))
                            /(real0 * real0 + imag0 * imag0);
            real0 = real1;
            imag0 = imag1;
                if (i % 10 == 0)
                    a.samples[0].push_back(fmSample);
        }
    }
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(new FFTFilter(0,0)) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(25000);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
