#include "resize_bilinear.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace cimg_library;

/**
 * @brief Resizes the given source image to the specified new dimensions using bilinear interpolation.
 * 
 * @param source The original image to be resized.
 * @param new_width The desired width of the resized image.
 * @param new_height The desired height of the resized image.
 * @return cimg_library::CImg<unsigned char> The resized image.
 */
cimg_library::CImg<unsigned char> resize_bilinear::resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height, int matrix_size) const {
    cimg_library::CImg<unsigned char> result(new_width, new_height, 1, source.spectrum(), 0);
    float x_ratio = static_cast<float>(source.width()) / new_width;
    float y_ratio = static_cast<float>(source.height()) / new_height;

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            for (int c = 0; c < source.spectrum(); ++c) {
                float src_x = x * x_ratio;
                float src_y = y * y_ratio;
                result(x, y, 0, c) = estimate_color(source, src_x, src_y, c, matrix_size);
            }
        }
    }

    return result;
}
/**
 * @brief Estimates the color value at a specific position in the source image using bilinear interpolation.
 * 
 * @param source The original image.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @param channel The color channel to estimate.
 * @return unsigned char The estimated color value.
 */
unsigned char resize_bilinear::estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel, int matrix_size) const {
    int x1 = static_cast<int>(x);
    int y1 = static_cast<int>(y);
    int x2 = std::min(x1 + 1, source.width() - 1);
    int y2 = std::min(y1 + 1, source.height() - 1);

    float x_frac = x - x1;
    float y_frac = y - y1;

    float top = interpolate(source(x1, y1, 0, channel), source(x2, y1, 0, channel), x_frac);
    float bottom = interpolate(source(x1, y2, 0, channel), source(x2, y2, 0, channel), x_frac);

    return static_cast<unsigned char>(interpolate(top, bottom, y_frac));
}
/**
 * @brief Interpolates between two values.
 * 
 * @param start The starting value.
 * @param end The ending value.
 * @param factor The interpolation factor (0.0 to 1.0).
 * @return float The interpolated value.
 */
float resize_bilinear::interpolate(float start, float end, float factor) const {
    return start + factor * (end - start);
}
