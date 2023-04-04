/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once
#include "Filter.h"
#include "../image/Image.h"
#include "../data/Data.h"


/**
 * @brief ImageFilter class which encapsulates filtering methods for 2D images.
*/
class ImageFilter : public Filter
{
public:

    ~ImageFilter() override = default;

    static void adjust_brightness(Image& image, int brightness);
    static void to_grayscale(Image& image);
    static void color_balance(Image& image);
    static void edge_detection(Image& image, std::string filter, int threshold);
    static void GaussianFilter(Image& image, int kernelSize, double sigma);
    static void median_filter(Image& img, int kernel_size);
    static void histogram_equalization(Image& img);
    static void BoxFilter(Image& image, int kernelSize);

protected:

private:
    static unsigned char get_increase(Image& image, int channels, float percent_change);
    static std::vector<float> generateKernel(float kernelSize, double sigma, std::string type);
    static void replicate_padding(Image& src, unsigned char* padded_img, int padding);
    static void convolution(Image& image, unsigned char* outputImageData, int halfSize, std::vector<float> kernel);
    static unsigned char partition(unsigned char* nums, int left, int right);
    static unsigned char quick_select(unsigned char* nums, int left, int right, int k);
};
