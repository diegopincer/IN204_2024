#ifndef RESIZE_IMAGE_BASE_H
#define RESIZE_IMAGE_BASE_H

#include "CImg.h"
#include <vector>

/**
 * @brief Abstract base class for image resizing algorithms.
 */
class resize_image_base {
public:
    /**
     * @brief Virtual destructor for the base class.
     */
    virtual ~resize_image_base() = default;

    /**
     * @brief Resizes the given source image to the specified new dimensions.
     * 
     * @param source The original image to be resized.
     * @param new_width The desired width of the resized image.
     * @param new_height The desired height of the resized image.
     * @param matrix_size The size of the matrix used for interpolation.
     * @return cimg_library::CImg<unsigned char> The resized image.
     */
    virtual cimg_library::CImg<unsigned char> resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height, int matrix_size) const = 0;

protected:
    /**
     * @brief Estimates the color value at a specific position in the source image.
     * 
     * @param source The original image.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param channel The color channel to estimate.
     * @param matrix_size The size of the matrix used for interpolation.
     * @return unsigned char The estimated color value.
     */
    virtual unsigned char estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel, int matrix_size) const = 0;

    /**
     * @brief Clamps a value between a minimum and maximum value.
     * 
     * @param value The value to clamp.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return int The clamped value.
     */
    int clamp(int value, int min, int max) const {
        return std::max(min, std::min(value, max));
    }

    /**
     * @brief Gets the neighborhood of pixels around a specific position in the source image.
     * 
     * @param source The original image.
     * @param x The x-coordinate of the center position.
     * @param y The y-coordinate of the center position.
     * @param size The size of the neighborhood matrix.
     * @param channel The color channel to extract.
     * @return std::vector<unsigned char> The neighborhood pixels.
     */
    std::vector<unsigned char> get_neighborhood(const cimg_library::CImg<unsigned char>& source, int x, int y, int size, int channel) const {
        std::vector<unsigned char> neighborhood;
        int half_size = size / 2;
        for (int dy = -half_size; dy <= half_size; ++dy) {
            for (int dx = -half_size; dx <= half_size; ++dx) {
                int nx = clamp(x + dx, 0, source.width() - 1);
                int ny = clamp(y + dy, 0, source.height() - 1);
                neighborhood.push_back(source(nx, ny, 0, channel));
            }
        }
        return neighborhood;
    }
};

#endif // RESIZE_IMAGE_BASE_H
