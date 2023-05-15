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
        dev = new Device("-");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        return 1;
    }
    Demodder dem(&dev->sampleQueue, &quit);

    std::thread demod(&Demodder::demodulate, &dem);
    std::thread reader(&Device::init, dev);

    while (!quit.load()) {
        usleep(100000000);
    }

    rtlsdr_cancel_async(dev->mDev);

    demod.join();
    reader.join();


    delete dev;
    return 0;
}
