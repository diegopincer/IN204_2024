#ifndef RESIZE_NEAREST_NEIGHBOUR_H
#define RESIZE_NEAREST_NEIGHBOUR_H

#include "resize_image_base.h"

class resize_nearest_neighbour : public resize_image_base {
public:
    /**
     * @brief Resizes the given source image to the specified new dimensions using nearest neighbour interpolation.
     * 
     * @param source The original image to be resized.
     * @param new_width The desired width of the resized image.
     * @param new_height The desired height of the resized image.
     * @param matrix_size The size of the matrix for interpolation.
     * @return cimg_library::CImg<unsigned char> The resized image.
     */
    cimg_library::CImg<unsigned char> resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height, int matrix_size) const override;

protected:
    /**
     * @brief Estimates the color value at a specific position in the source image using nearest neighbour interpolation.
     * 
     * @param source The original image.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param channel The color channel to estimate.
     * @param matrix_size The size of the matrix for interpolation.
     * @return unsigned char The estimated color value.
     */
    unsigned char estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel, int matrix_size) const override;
};

#endif // RESIZE_NEAREST_NEIGHBOUR_H
