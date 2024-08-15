#include "resize_nearest_neighbour.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace cimg_library;

cimg_library::CImg<unsigned char> resize_nearest_neighbour::resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height) const {
    cimg_library::CImg<unsigned char> result(new_width, new_height, 1, source.spectrum(), 0);
    float x_ratio = static_cast<float>(source.width()) / new_width;
    float y_ratio = static_cast<float>(source.height()) / new_height;

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            for (int c = 0; c < source.spectrum(); ++c) {
                float src_x = x * x_ratio;
                float src_y = y * y_ratio;
                result(x, y, 0, c) = estimate_color(source, src_x, src_y, c);
            }
        }
    }

    return result;
}

unsigned char resize_nearest_neighbour::estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel) const {
    int nearest_x = static_cast<int>(round(x));
    int nearest_y = static_cast<int>(round(y));
    nearest_x = std::max(0, std::min(nearest_x, source.width() - 1));
    nearest_y = std::max(0, std::min(nearest_y, source.height() - 1));
    std::cout << "Nearest neighbour estimate color at (" << nearest_x << ", " << nearest_y << ") in channel " << channel << std::endl;
    return source(nearest_x, nearest_y, 0, channel);
}
