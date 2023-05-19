#include "Decoder.h"
#include "../debug/bitmap_image.hpp"
#include <iostream>
#include <functional>

int main() {
    AudioFile<float> a("Test.wav");
    std::vector<float> samples;
    std::function<float(float)> sigmoid = [](float sample) {return 255*(1/(1+std::exp(6-15*sample))); };
    double wl = a.getSampleRate()/2400.0;

    for (double i = 20000; i < a.samples[0].size(); i+=wl) {
        float sample = 0;
        for (int j = i; j < i + wl; j++) {
            sample = std::max(sample, a.samples[0][j]);
        }
        samples.push_back(sample);
    }


    const int height = 1+(int)a.getLengthInSeconds()*2;
    const int width = 2080;
    
    bitmap_image img(width, height);
    
    float diff = 1200.0/float(width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 1) {
            float sample = samples[x*diff+1200*y];
            sample = sample * 255;
            sample = sample > 255 ? 255 : sample;
            unsigned char color = (unsigned char) sample;
            img.set_pixel(x, y, color, color, color);
        }
    }

    img.save_image("haha.bmp");

}
