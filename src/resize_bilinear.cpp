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
    // Assuming matrix_size is always odd
    int half_size = matrix_size / 2;
    int x1 = std::max(0, static_cast<int>(x) - half_size);
    int y1 = std::max(0, static_cast<int>(y) - half_size);
    int x2 = std::min(x1 + matrix_size, source.width() - 1);
    int y2 = std::min(y1 + matrix_size, source.height() - 1);

    // Interpolation considering more pixels, depending on matrix_size
    float color_sum = 0.0f;
    float weight_sum = 0.0f;

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            int xi = std::min(x1 + i, source.width() - 1);
            int yj = std::min(y1 + j, source.height() - 1);

            // Calculates the weight based on the distance to x, y
            float x_dist = std::abs(x - xi);
            float y_dist = std::abs(y - yj);
            float weight = 1.0f / ((x_dist + 1) * (y_dist + 1)); 

            color_sum += source(xi, yj, 0, channel) * weight;
            weight_sum += weight;
        }
    }

    return static_cast<unsigned char>(color_sum / weight_sum);
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
