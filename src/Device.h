#include <rtl-sdr.h>
#include <string>
#include <queue>
#include <atomic>
#include <array>
#include "IQueue.h"


class Device {
    private:
    int getDevIndex(std::string serial);
    public:
    std::atomic<bool>* quit;
    rtlsdr_dev_t* mDev = nullptr;
    IQueue<std::array<u_char, 16*32*512>> sampleQueue;
    Device(std::string serial);
    ~Device();
    void init();
};
