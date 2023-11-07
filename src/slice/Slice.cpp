/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include "Slice.h"


void Slice::slice_xz(Volume &vol, Image &output_image, int y)
/** 
 * @brief  Slice a volume along the y-axis and writes the resulting image to the Output directory
 * 
 * @param  vol: the volume to be sliced
 * @param  output_image: this Image object will be set to represent the slice
 * @param  y: the y coordinate of the slice
 * 
*/
{
    std::cout << "Slicing volume in x-z plane." << std::endl;

    int w = vol.get_x();
    int h = vol.get_y();
    int l = vol.get_z();
    int c = vol.get_channels();

    // define the size of output image
    int slice_width = w;
    int slice_height = l;
    output_image.w = slice_width;
    output_image.h = slice_height;       
    

    // The size of a single 2D image in x-y
    int img_size = w * h;

    // get the size of outputted slice image
    int size = w*l;  

    // the index of output image data 
    int index = 0;    

    // Creating an array to hold the slice image data.
    unsigned char *sliceData = new unsigned char [size];

    // Iterating through the images which make up the volume.
    for (unsigned char* p = vol.data; p != vol.data + vol.get_size(); p += img_size) {
        // Since this x values in a row are stored together in memory
        // we can copy the entire row at once.
        std::copy(p + w*y, p + w*y + w, sliceData + index*w);
        index++;
    }

    output_image.update(sliceData, c, size);
    delete[] sliceData;
}


void Slice::slice_yz(Volume &vol, Image &output_image, int x)
/** 
 * @brief  Slice a volume along the x-axis and writes the resulting image to the Output directory
 * 
 * @param  vol: the volume to be sliced
 * @param  output_image: this Image object will be set to represent the slice
 * @param  x: the x coordinate of the slice
 * 
*/
{
    std::cout << "Slicing volume in y-z plane." << std::endl;

    int w = vol.get_x();
    int h = vol.get_y();
    int l = vol.get_z();
    int c = vol.get_channels();

    // define the size of output image
    int slice_width = h;
    int slice_height = l;
    output_image.w = slice_width;
    output_image.h = slice_height;  

    // The size of a single 2D image in x-y
    int img_size = w * h;

    // get the size of outputted slice image
    int size = h*l;  

    // the index of output image data 
    int index = 0;    

    // Creating an array to hold the slice image data.
    unsigned char *sliceData = new unsigned char [size];

    // Iterating through the images which make up the volume.
    for (unsigned char* p = vol.data; p != vol.data + vol.get_size(); p += img_size) {
        // Iterating through the y values in this image for the given x value.
        for (int row = 0; row < h; row++) {
            // Adding the pixels for the final slice output.
            sliceData[index*h + row] = p[row*w + x];
        }
        index++;
    }

    output_image.update(sliceData, c, size);
    delete[] sliceData;
}