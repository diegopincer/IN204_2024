#include "CImg.h"
 
using namespace cimg_library;

/**
 * @brief Displays an image and allows the user to interactively select a horizontal line to visualize the color intensity profile.
 * 
 * @param image The original image loaded from a file.
 * @param visu A blank image used for drawing the intensity profiles.
 * @param red An array representing the color red in RGB format.
 * @param green An array representing the color green in RGB format.
 * @param blue An array representing the color blue in RGB format.
 * 
 * @details The program loads an image, applies a blur effect, and displays it in a window. The user can click on any point in the image,
 *          and the program will extract and display the intensity profiles of the red, green, and blue channels along the selected horizontal line. 
 *          The profiles are displayed in a separate window.
 */

 
int main() {
  CImg<unsigned char> image("src/lenna.png"), visu(500,400,1,3,0);
  const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
  image.blur(2.5);
  CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
  while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    main_disp.wait();
    if (main_disp.button() && main_disp.mouse_y()>=0) {
      const int y = main_disp.mouse_y();
      visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
      visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
      visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
      }
    }
  return 0;
}