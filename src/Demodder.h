#pragma once
#include <complex>
#include <vector>
#include <fstream>

class Demodder {
    private:
    std::vector<std::complex<double>> iqSamples;
    std::ifstream* inFile;

    public:
    Demodder(std::ifstream * f) : inFile(f){}
    ~Demodder();
    void bufferToComplex();
    void demodulate();
    std::vector<double> fmSamples;
};
