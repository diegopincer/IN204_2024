#include "resize_nearest_neighbour.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace cimg_library;

/**
 * @brief Resizes the given source image to the specified new dimensions using nearest neighbour interpolation.
 * 
 * @param source The original image to be resized.
 * @param new_width The desired width of the resized image.
 * @param new_height The desired height of the resized image.
 * @return cimg_library::CImg<unsigned char> The resized image.
 */
cimg_library::CImg<unsigned char> resize_nearest_neighbour::resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height, int matrix_size) const {
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
 * @brief Estimates the color value at a specific position in the source image using nearest neighbour interpolation.
 * 
 * @param source The original image.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @param channel The color channel to estimate.
 * @return unsigned char The estimated color value.
 */
unsigned char resize_nearest_neighbour::estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel, int matrix_size) const {
    int half_size = matrix_size / 2;
    
    int nearest_x = static_cast<int>(round(x));
    int nearest_y = static_cast<int>(round(y));
    
    // Clamp to ensure we don't go out of bounds
    nearest_x = clamp(nearest_x, 0, source.width() - 1);
    nearest_y = clamp(nearest_y, 0, source.height() - 1);

    float min_distance = std::numeric_limits<float>::max();
    unsigned char best_color = source(nearest_x, nearest_y, 0, channel);

    // Iterate over the neighborhood defined by matrix_size
    for (int i = -half_size; i <= half_size; ++i) {
        for (int j = -half_size; j <= half_size; ++j) {
            int xi = clamp(nearest_x + i, 0, source.width() - 1);
            int yj = clamp(nearest_y + j, 0, source.height() - 1);

            float distance = std::sqrt((xi - x) * (xi - x) + (yj - y) * (yj - y));

            if (distance < min_distance) {
                min_distance = distance;
                best_color = source(xi, yj, 0, channel);
            }
        }
    }

    return best_color;
}