#include "../src/Demodder.h"
#include <iostream>
#include <ctime>

void Demodder::demodulate() {
        float real0 = 1;
        float imag0 = 1;
        std::ifstream inFile("test.bin", std::ios::binary);
        u_char buf[16*32*512];
        inFile.read((char*)buf, 16*32*512);

        FFTFilter filter(0,0);
        filter.filter(buf);


        return;

            for (u_long i = 0; i + 1 < 16*32*512; i += 2) {
                float real1 = 0;
                float imag1 = 0;
                float fmSample = (real0 * (imag1 - imag0)
                                - imag0 * (real1 - real0))
                                /(real0 * real0 + imag0 * imag0);
                real0 = real1;
                imag0 = imag1;
                a.samples[0].push_back(fmSample);
            }
        std::cout << "hey" << std::endl;
}


Demodder::Demodder(IQueue<unsigned char*>* q, std::atomic<bool>* quit) : quit(quit), filter(256,20e3) {
    sampleQueue = q;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(250000);
}

Demodder::~Demodder() {
    a.save("Test.wav", AudioFileFormat::Wave);

}
