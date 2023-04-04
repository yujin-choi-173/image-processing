/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include "Image.h"
#include <string>

enum filter { brightness, grayscale };

Image::Image()
{
}

// Constructor - using an initialisation list here
Image::Image(char* file_name): Data(file_name)
{   
}

// Copy constructor
Image::Image(Image &img): Data(img.file_name)
{   
}

// Destructor
Image::~Image()
{
}

int Image::get_width() {
    return this->w;
}

int Image::get_height() {
    return this->h;
}

int Image::get_channels() {
    return this->c;
}

// test constructor
Image::Image(unsigned char* data, int w, int h, int c, char* name) : Data(data, w, h, c, name){}
