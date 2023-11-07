/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/

#pragma once

#include "../data/Data.h"
#include "../image/Image.h"
#include "../data/Data.h"
#include <vector>

/**
 * @brief Class to represent 3D volumes.
 */
class Volume : public Data
{
public:
    
    // Constructors
    Volume(char* dir_name);
    Volume();
    Volume(unsigned char* data, int w, int h, int c, int num_files, char* name);

    // destructor
    virtual ~Volume();
    
    int get_x();
    int get_y();
    int get_z();
    int get_channels();

    char* dir_name;


protected:

private:
    

};
