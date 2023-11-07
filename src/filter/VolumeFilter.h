/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once

#include "Filter.h"
#include "../volume/Volume.h"
#include "../data/Data.h"

/**
 * @brief VolumeFilter class which encapsulates filtering methods for 3D volumes.
*/
class VolumeFilter : public Filter
{
public:

    // destructor
    ~VolumeFilter() override = default;

    static void GaussianFilter3d(Volume &volume,int kernelSize,double sigma);
    static void median3D_filter(Volume& img, int kernel_size);

protected:

private:
    static std::vector<double> generate_1d_gaussian_kernel(int kernelSize, double sigma);
    static void replicate3D_padding(Volume& img, unsigned char* padded_img, int padding);
    static unsigned char partition(unsigned char* nums, int left, int right);
    static unsigned char quick_select(unsigned char* nums, int left, int right, int k);

};