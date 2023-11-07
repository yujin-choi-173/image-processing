/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "../volume/Volume.h"
#include "VolumeFilter.h"
using namespace std;

void VolumeFilter::GaussianFilter3d(Volume &volume,int kernelSize=5,double sigma=1.0)
/**
 * @brief Add Gaussian filter to the volume and replace the original volume
 * 
 * @param[in] volume
 * @param[in] size of the kernal
 * @param[in] standard deviation for Gaussian function
*/
{
    std::vector<double> kernel=generate_1d_gaussian_kernel(kernelSize, sigma);
    int halfSize = kernelSize / 2;
    int width=volume.get_x();
    int height=volume.get_y();
    int channels=volume.get_channels();
    int depth=volume.get_z();
    int size=(width*height*channels)*depth;

    unsigned char *outputVolumeData_x = new unsigned char[size];

    //convolute horizontally
    for (int z=0; z<depth; ++z){
        //cout << z << endl;
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                float r = 0, g = 0, b = 0, a = 0;

                for (int k = -halfSize; k <= halfSize; ++k ){
                    int n = x + k;
                    if (n >= 0 && n < width){
                        int index = (z * width * height + y * width + n) * channels;
                        if (channels==1 || channels ==2){
                            r += kernel[k + halfSize] * volume.data[index];
                            if (channels == 2) {
                            a = volume.data[index + 1]; //the alpha channel
                            }
                        }
                        if (channels>=3){
                            r += kernel[k + halfSize] * volume.data[index];
                            g += kernel[k + halfSize] * volume.data[index + 1];
                            b += kernel[k + halfSize] * volume.data[index + 2];
                            if (channels == 4) {
                                a = volume.data[index + 3]; //the alpha channel
                            }
                        }
                    }
                }
                //change to char form
                int index = (z * width * height + y * width +x) * channels;
                if (channels==1||channels==2){
                    outputVolumeData_x[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    if (channels == 2) {
                    outputVolumeData_x[index + 1] = static_cast<unsigned char>(a);
                }
                }
                if (channels>=3){
                    outputVolumeData_x[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    outputVolumeData_x[index + 1] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, g)));
                    outputVolumeData_x[index + 2] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, b)));
                    if (channels == 4) {
                        outputVolumeData_x[index + 3] = static_cast<unsigned char>(a);
                    }
                }
            }
        }
    }
    
    unsigned char *outputVolumeData_y = new unsigned char[size];
    //convolute vertically
    for (int z=0; z<depth; ++z){
        //cout << z << endl;
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                float r = 0, g = 0, b = 0, a = 0;
                //int index = (z * width * height + y * width +x) * channels;

                for (int k = -halfSize; k <= halfSize; ++k ){
                    int n = y + k;
                    if (n >= 0 && n < height){
                        int index = (z * width * height + n * width +x) * channels;
                        if (channels==1 || channels ==2){
                            r += kernel[k + halfSize] * outputVolumeData_x[index];
                            if (channels == 2) {
                            a = outputVolumeData_x[index + 1]; //the alpha channel
                            }
                        }
                        if (channels>=3){
                            r += kernel[k + halfSize] * outputVolumeData_x[index];
                            g += kernel[k + halfSize] * outputVolumeData_x[index + 1];
                            b += kernel[k + halfSize] * outputVolumeData_x[index + 2];
                            if (channels == 4) {
                                a = outputVolumeData_x[index + 3]; //the alpha channel
                            }
                        }
                    }
                }
                //change to char form
                int index = (z * width * height + y * width +x) * channels;
                if (channels==1||channels==2){
                    outputVolumeData_y[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    if (channels == 2) {
                    outputVolumeData_y[index + 1] = static_cast<unsigned char>(a);
                }
                }
                if (channels>=3){
                    outputVolumeData_y[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    outputVolumeData_y[index + 1] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, g)));
                    outputVolumeData_y[index + 2] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, b)));
                    if (channels == 4) {
                        outputVolumeData_y[index + 3] = static_cast<unsigned char>(a);
                    }
                }
            }
        }
    }
    delete[] outputVolumeData_x;

    unsigned char *outputVolumeData_z = new unsigned char[size];
    //convolute in depth
    for (int z=0; z<depth; ++z){
        //cout << z << endl;
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                float r = 0, g = 0, b = 0, a = 0;
                //int index = (z * width * height + y * width +x) * channels;

                for (int k = -halfSize; k <= halfSize; ++k ){
                    int n = z + k;
                    if (n >= 0 && n < depth){
                        int index = (n * width * height + y * width +x) * channels;
                        if (channels==1 || channels ==2){
                            r += kernel[k + halfSize] * outputVolumeData_y[index];
                            if (channels == 2) {
                            a = outputVolumeData_y[index + 1]; //the alpha channel
                            }
                        }
                        if (channels>=3){
                            r += kernel[k + halfSize] * outputVolumeData_y[index];
                            g += kernel[k + halfSize] * outputVolumeData_y[index + 1];
                            b += kernel[k + halfSize] * outputVolumeData_y[index + 2];
                            if (channels == 4) {
                                a = outputVolumeData_y[index + 3]; //the alpha channel
                            }
                        }
                    }
                }
                //change to char form
                int index = (z * width * height + y * width +x) * channels;
                if (channels==1||channels==2){
                    outputVolumeData_z[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    if (channels == 2) {
                    outputVolumeData_z[index + 1] = static_cast<unsigned char>(a);
                }
                }
                if (channels>=3){
                    outputVolumeData_z[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                    outputVolumeData_z[index + 1] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, g)));
                    outputVolumeData_z[index + 2] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, b)));
                    if (channels == 4) {
                        outputVolumeData_z[index + 3] = static_cast<unsigned char>(a);
                    }
                }
            }
        }
    }
    delete[] outputVolumeData_y;
    //update image 
    volume.update(outputVolumeData_z, channels, size);
    delete[] outputVolumeData_z;
}

std::vector<double> VolumeFilter::generate_1d_gaussian_kernel(int kernelSize, double sigma) {
    int halfSize = kernelSize / 2;
    std::vector<double> kernel(kernelSize);

    double sum = 0.0f;
    for (int i = 0; i < kernelSize; ++i) {
        double x = i - halfSize;
        kernel[i] = exp(-x * x / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
        sum += kernel[i];
    }

    for (int i = 0; i < kernelSize; ++i) {
        kernel[i] /= sum;
    }

    return kernel;
}


/**
 * Use quick select to find the median
 *
 * @param nums The input window.
 * @param left The left index.
 * @param right The right index.
 */
 // Optimize partition function by using median-of-three pivot selection
unsigned char VolumeFilter::partition(unsigned char* nums, int left, int right) {
    int mid = (left + right) / 2;
    if (nums[left] > nums[mid]) swap(nums[left], nums[mid]);
    if (nums[left] > nums[right]) swap(nums[left], nums[right]);
    if (nums[mid] > nums[right]) swap(nums[mid], nums[right]);

    int pivot = nums[mid];
    swap(nums[mid], nums[right]);
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[right]);
    return i + 1;
}

/**
 * Use quick select to find the median
 *
 * @param nums The input window.
 * @param left The left index.
 * @param right The right index.
 * @param k half window size.
 */
unsigned char VolumeFilter::quick_select(unsigned char* nums, int left, int right, int k) {
    while (left < right) {
        int pivot_index = partition(nums, left, right);
        if (k == pivot_index) {
            break;
        }
        else if (k < pivot_index) {
            right = pivot_index - 1;
        }
        else {
            left = pivot_index + 1;
        }
    }
    return nums[k];
}

/**
 * Apply replicate padding to a given 3D image.
 *
 * @param vol The source 3D image.
 * @param padded_img The destination padded 3D image.
 * @param padding The padding to be applied.
 */
void VolumeFilter::replicate3D_padding(Volume& vol, unsigned char* padded_img, int padding) {
    int width = vol.get_x();
    int height = vol.get_y();
    int depth = vol.get_z();
    int channel = vol.get_channels();
    int new_width = width + 2 * padding;
    int new_height = height + 2 * padding;

    for (int z = -padding; z < depth + padding; ++z) {
        for (int row = -padding; row < height + padding; ++row) {
            for (int col = -padding; col < width + padding; ++col) {
                int img_row = min(max(row, 0), height - 1);
                int img_col = min(max(col, 0), width - 1);
                int img_z = min(max(z, 0), depth - 1);

                for (int ch = 0; ch < channel; ++ch) {
                    int padded_idx = (((z + padding) * new_height + row + padding) * new_width + col + padding) * channel + ch;
                    int img_idx = ((img_z * height + img_row) * width + img_col) * channel + ch;
                    padded_img[padded_idx] = vol.data[img_idx];
                }
            }
        }
    }
}


/**
 * Apply 3D median filter to a given 3D image.
 *
 * @param vol The source 3D image.
 * @param kernel_size The size of the kernel to be applied.
 */
void VolumeFilter::median3D_filter(Volume& vol, int kernel_size) {
    int width = vol.get_x();
    int height = vol.get_y();
    int depth = vol.get_z();
    int channel = vol.get_channels();
    int padding = kernel_size / 2;
    int new_width = width + 2 * padding;
    int new_height = height + 2 * padding;
    int new_depth = depth + 2 * padding;
    unsigned char* padded_vol = new unsigned char[new_width * new_height * new_depth * channel];
    unsigned char* new_vol = new unsigned char[width * height * depth * channel];

    // Apply replicate padding to the source image.
    replicate3D_padding(vol, padded_vol, padding);

    // Iterate through each (z, row, col) position in the source image.
    int window_size = kernel_size * kernel_size * kernel_size;
    unsigned char* window = new unsigned char[window_size];

    // Precompute some values
    int half_window_size = window_size / 2;

    // Precompute half of the kernel size
    int half_kernel_size = kernel_size / 2;

    for (int z = 0; z < depth; ++z) {
        //cout << z << endl;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                for (int ch = 0; ch < channel; ++ch) {
                    int window_idx = 0;
                    for (int k_z = -half_kernel_size; k_z <= half_kernel_size; ++k_z) {
                        for (int k_row = -half_kernel_size; k_row <= half_kernel_size; ++k_row) {
                            for (int k_col = -half_kernel_size; k_col <= half_kernel_size; ++k_col) {
                                int cur_row = row + padding + k_row;
                                int cur_col = col + padding + k_col;
                                int cur_z = z + padding + k_z;

                                int padded_idx = (((cur_z * new_height) + cur_row) * new_width + cur_col) * channel + ch;
                                if (window_idx < window_size) {
                                    window[window_idx++] = padded_vol[padded_idx];
                                }
                            }
                        }
                    }

                    // Use quick select to find median
                    unsigned char median = quick_select(window, 0, window_size - 1, half_window_size);
                    int new_vol_idx = ((z * height + row) * width + col) * channel + ch;
                    new_vol[new_vol_idx] = median;
                }
            }
        }
    }
    
    vol.update(new_vol, channel, width * height * depth * channel);
    delete[] new_vol;
    delete[] window;
    delete[] padded_vol;
}




