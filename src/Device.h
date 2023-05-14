#include <rtl-sdr.h>
#include <string>
#include <queue>
#include <atomic>
#include "IQueue.h"


class Device {
    private:
    int getDevIndex(std::string serial);
    public:
    std::atomic<bool>* quit;
    rtlsdr_dev_t* mDev = nullptr;
    IQueue<u_char> sampleQueue;
    Device(std::string serial, std::atomic<bool> * q);
    ~Device();
    void init(uint32_t freq);
};
