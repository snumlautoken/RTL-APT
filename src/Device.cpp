#include "Device.h"
#include <iostream>


static void callback(unsigned char *buf, uint32_t len, void *ctx) {
    Device* d = (Device*) ctx;
    if (d->quit->load()) {
        rtlsdr_cancel_async(d->mDev);
        return;
    }

    std::array<u_char,16*32*512> a;

    for (int i = 0; i < 16*32*512; i++) {
        a[i] = buf[i];
    }

    d->sampleQueue.push(a);
}

Device::Device(std::string serial, std::atomic<bool> * q) : quit(q) {
    quit = q;
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
    rtlsdr_cancel_async(mDev);
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



void Device::init(uint32_t freq) {
    rtlsdr_set_center_freq(mDev, 103300000);
    rtlsdr_set_sample_rate(mDev, 2400000);
    rtlsdr_set_tuner_gain_mode(mDev, 0);
    rtlsdr_set_tuner_bandwidth(mDev, 175000);
    rtlsdr_reset_buffer(mDev);

    rtlsdr_read_async(mDev, callback, this, 0, 0);
}
