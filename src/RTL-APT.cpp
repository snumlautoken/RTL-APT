#include <iostream>
#include <rtl-sdr.h>
#include "Device.h"

int main(int argc, char **argv) {
    char manufact[256], product[256], serial[256];
    int device_count = rtlsdr_get_device_count();

    for (int i = 0; i < device_count; i++) {
        rtlsdr_get_device_usb_strings(i, manufact, product, serial);
        std::cout << i << " " << manufact << " " << product << " " << serial << std::endl;
    }

    Device* dev;

    try {
        dev = new Device("-");
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        return 1;
    }

    dev->init(137100000);

    delete dev;
    return 0;
}
