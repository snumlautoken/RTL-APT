#include "Device.h"
#include <iostream>

static void callback(unsigned char *buf, uint32_t len, void *ctx) {
    Device* dev = (Device *) ctx;
    std::cout << dev->s << std::endl;
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


void Device::init(uint32_t freq) {
    rtlsdr_set_center_freq(mDev, freq);
    rtlsdr_set_sample_rate(mDev, 2400000);
    rtlsdr_set_tuner_gain_mode(mDev, 0);
    rtlsdr_set_tuner_bandwidth(mDev, 40000);
    rtlsdr_reset_buffer(mDev);

    rtlsdr_read_async(mDev, callback, this, 12, (16 * 16384));
}
