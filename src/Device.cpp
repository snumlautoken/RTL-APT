#include "Device.h"

int Device::getDevIndex(std::string serial) {
    if (rtlsdr_get_device_count() == 0) {
        return -1;
    }
    if (serial == "-") {
        return 0;
    }
    return rtlsdr_get_index_by_serial(serial.c_str());
}

void Device::findDev(std::string serial) {
    uint32_t dev_index = 0;

    int r = rtlsdr_open(&mDev, dev_index);
}
