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
    IQueue<unsigned char*> sampleQueue;
    Device(std::string serial);
    ~Device();
    void init();
};
