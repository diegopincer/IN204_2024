#ifndef RESIZE_IMAGE_BASE_H
#define RESIZE_IMAGE_BASE_H

#include "CImg.h"

/**
 * @brief Abstract base class for image resizing.
 * 
 * This class provides an interface for resizing images. Derived classes must implement
 * the resize method to provide specific resizing algorithms.
 */
class resize_image_base {
public:
    /**
     * @brief Virtual destructor for the base class.
     */
    virtual ~resize_image_base() = default;

    /**
     * @brief Pure virtual method to resize an image.
     * 
     * Derived classes must implement this method to resize the given source image
     * to the specified new dimensions.
     * 
     * @param source The original image to be resized.
     * @param new_width The desired width of the resized image.
     * @param new_height The desired height of the resized image.
     * @return cimg_library::CImg<unsigned char> The resized image.
     */
    virtual cimg_library::CImg<unsigned char> resize(const cimg_library::CImg<unsigned char>& source, int new_width, int new_height) const = 0;

protected:
    /**
     * @brief Pure virtual method to estimate the color value at a specific position in the source image.
     * 
     * Derived classes must implement this method to provide specific color estimation techniques.
     * 
     * @param source The original image.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param channel The color channel to estimate.
     * @return unsigned char The estimated color value.
     */
    virtual unsigned char estimate_color(const cimg_library::CImg<unsigned char>& source, float x, float y, int channel) const = 0;
};

#endif // RESIZE_IMAGE_BASE_H
