/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once

#include "../data/Data.h"

/**
 * @brief Class to represent 2D images.
 */
class Image : public Data
{
public:
    // Constructors
    Image();
    Image(char* file_name);
    Image(unsigned char* data, int w, int h, int c, char* name);
    Image(Image &img);
    Image(Image &&img);

    // destructor
    virtual ~Image();

    int get_width();
    int get_height();
    int get_channels();

protected:

private:
    

};
