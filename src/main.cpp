#include "CImg.h"
#include "resize_nearest_neighbour.h"
#include "resize_bilinear.h"
#include <sstream>
#include <iostream>

using namespace cimg_library;

/**
 * @brief Resizes an image using the specified resizer and saves the result.
 * 
 * @param resizer The resizer object that implements the resize method.
 * @param image The original image to be resized.
 * @param scale_factor The factor by which to scale the image.
 * @param method The name of the resizing method (used for output filename and logging).
 */
void resize_and_save(const resize_image_base& resizer, const CImg<unsigned char>& image, float scale_factor, const std::string& method) {
    // Calculate new dimensions based on the scale factor
    int new_width = static_cast<int>(image.width() * scale_factor);
    int new_height = static_cast<int>(image.height() * scale_factor);

    // Resize the image using the specified resizer
    CImg<unsigned char> resized_image = resizer.resize(image, new_width, new_height);

    // Create the output filename based on the method and scale factor
    std::ostringstream output_filename;
    output_filename << "lenna_resized_" << method << "_" << scale_factor << ".png";

    // Save the resized image to the output file
    resized_image.save(output_filename.str().c_str());

    // Log the resizing operation details
    std::cout << "Image resized using " << method << " to " << scale_factor * 100 << "% and saved to " << output_filename.str() << std::endl;
    std::cout << "New dimensions: " << resized_image.width() << "x" << resized_image.height() << std::endl;
}

int main() {
    // Load the original image from file
    CImg<unsigned char> image("src/lenna.png");

    // Create resizer objects for nearest neighbour and bilinear methods
    resize_nearest_neighbour nearest_neighbour_resizer;
    resize_bilinear bilinear_resizer;

    // Scale factors to apply
    float scale_factors[] = {0.5, 0.75, 1.5, 2.0};

    // Loop through each scale factor and resize the image using both methods
    for (float scale_factor : scale_factors) {
        // Resize and save using nearest neighbour method
        resize_and_save(nearest_neighbour_resizer, image, scale_factor, "nearest");
        // Resize and save using bilinear method
        resize_and_save(bilinear_resizer, image, scale_factor, "bilinear");
    }

    return 0;
}
