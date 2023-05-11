#include <rtl-sdr.h>
#include <string>

class Device {
    private:
    rtlsdr_dev_t* mDev = nullptr;
    int getDevIndex(std::string serial);

    public:
    void findDev(std::string serial);
};
