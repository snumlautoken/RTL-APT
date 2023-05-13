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

    try {
        Device dev("-");
        dev.init(137100000);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        return 1;
    }

    return 0;
}
