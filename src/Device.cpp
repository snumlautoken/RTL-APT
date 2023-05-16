#include "Device.h"
#include <iostream>


static void callback(unsigned char *buf, uint32_t len, void *ctx) {
    IQueue<unsigned char*>* q = (IQueue<unsigned char*>*) ctx;

    q->push(buf);
}

Device::Device(std::string serial) {
    int dev_index = getDevIndex(serial);
    if (dev_index < 0) {
        throw "No device found.";
    }
    int r = rtlsdr_open(&mDev, (uint32_t)dev_index);
    if (r != 0) {
        throw "Device could not be openned.";
    }
}

Device::~Device() {
    rtlsdr_close(mDev);
}

int Device::getDevIndex(std::string serial) {
    if (rtlsdr_get_device_count() == 0) {
        return -1;
    }
    if (serial == "-") {
        return 0;
    }
    return rtlsdr_get_index_by_serial(serial.c_str());
}



void Device::init() {
    rtlsdr_set_center_freq(mDev, 101900000);
    rtlsdr_set_sample_rate(mDev, 2400000);
    rtlsdr_set_tuner_gain_mode(mDev, 0);
    rtlsdr_set_tuner_bandwidth(mDev, 175000);
    rtlsdr_reset_buffer(mDev);

    rtlsdr_read_async(mDev, callback, &sampleQueue, 0, 0);
}
