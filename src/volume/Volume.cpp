/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include "Volume.h"
#include <string>


Volume::Volume()
{
}

Volume::Volume(char* dir_name) : Data(dir_name, true)
{   
}

// Destructor
Volume::~Volume()
{
}

int Volume::get_x() {
    return Data::w;
}

int Volume::get_y() {
    return Data::h;
}

int Volume::get_z() {
    return Data::num_files;
}

int Volume::get_channels() {
    return Data::c;
}

Volume::Volume(unsigned char* data, int w, int h, int c, int num_files, char* name) :
Data(data, w, h, c, num_files, name){}
