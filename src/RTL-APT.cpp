#include <iostream>
#include <rtl-sdr.h>
#include <thread>
#include <csignal>
#include "IQueue.h"
#include "Device.h"
#include "Demodder.h"

std::atomic<bool> quit;

void signalHandler( int signum ) {
    quit.store(true);
}


int main(int argc, char **argv) {
    Device* dev;
    signal(SIGINT, signalHandler);
    quit.store(false);
    try {
        dev = new Device("-", &quit);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        return 1;
    }
    Demodder dem(&dev->sampleQueue, &quit);

    std::thread bufReader(&Demodder::bufferToComplex, &dem);
    std::thread demod(&Demodder::demodulate, &dem);
    dev->init(3);

    bufReader.join();
    demod.join();


    delete dev;
    return 0;
}
