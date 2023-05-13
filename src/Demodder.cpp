#include "Demodder.h"
#include "../debug/AudioFile.h"
#include <iostream>

void Demodder::bufferToComplex() {
    std::vector<u_char> bytes(
        (std::istreambuf_iterator<char>(*inFile)),
        (std::istreambuf_iterator<char>()));
    // Decimate by factor 4
    for (long i = 0; i + 7 < bytes.size(); i += 8) {
        double iS = ((double) bytes[i]) - 127.5;
        double qS = ((double) bytes[i+1]) - 127.5;
        iqSamples.push_back(std::complex<double>(iS,qS));
    }
}

void Demodder::demodulate() {
    for (long i = 0; i + 1 < iqSamples.size(); i++) {
        std::complex<double> iq0 = iqSamples[i];
        std::complex<double> iq1 = iqSamples[i+1];
        double fmSample = (iq0.real()*(iq1.imag() - iq0.imag())
                        -iq0.imag()*(iq1.real()-iq0.real()))
                        /(iq0.real()*iq0.real()+iq0.imag()*iq0.imag());
        fmSamples.push_back(fmSample);
    }
}

Demodder::~Demodder() {
    inFile->close();
    delete inFile;
}

int main() {
    Demodder dem(new std::ifstream("myfile.bin", std::ios::binary));
    dem.bufferToComplex();
    dem.demodulate();

    AudioFile<double> a;
    a.setNumChannels(1);
    a.isMono();
    a.setSampleRate(2400000/20);

    for (int i = 0; i + 5 < dem.fmSamples.size(); i += 5) {
        a.samples[0].push_back(dem.fmSamples[i]);
    }

    a.save("Test.wav", AudioFileFormat::Wave);
}
