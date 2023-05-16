#include "Decoder.h"
#include "../debug/bitmap_image.hpp"
#include <iostream>

int main() {
    AudioFile<float> a("rec.wav");
    std::vector<float> samples;
    std::cout << a.getSampleRate() << std::endl;
    double wl = a.getSampleRate()/2400.0;

    for (double i = 0; i < a.samples[0].size(); i+=wl) {
        float sample = 0;
        for (double j = i; j < i + wl; j++) {
            sample = std::max(sample, a.samples[0][(int)j]);
        }
        samples.push_back(sample);
    }

    std::cout << "sample" << std::endl;


    const int height = 1+(int)a.getLengthInSeconds()*2;
    const int width = 2080;
    
    bitmap_image img(width, height);
    
    float diff = 1200.0/float(width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 1) {
            float sample = samples[x*diff+1200*y];
            sample = (sample) * 255;
            sample = sample > 255 ? 255 : sample;
            unsigned char color = (unsigned char) sample;
            //std::cout << (int)color << std::endl;
            img.set_pixel(x, y, color, color, color);
        }
    }

    img.save_image("haha.bmp");

}
