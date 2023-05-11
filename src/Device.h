#include <rtl-sdr.h>
#include <string>

class Device {
    private:
    rtlsdr_dev_t* mDev = nullptr;
    int getDevIndex(std::string serial);

    public:
    Device(std::string serial);
    void init(uint32_t freq);
    std::string s = "hello";
};
