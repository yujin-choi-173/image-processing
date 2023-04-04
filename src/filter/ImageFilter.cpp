#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "ImageFilter.h"

using namespace std;

void ImageFilter::adjust_brightness(Image& image, int brightness)
/**
 * @brief Adjust the brightness of an image
 *
 * @param[in] image
 * @param[in] brightness
*/
{
    int channels = image.get_channels();

    double increase = brightness;
    for (unsigned char* p = image.data; p != image.data + image.get_size(); p += channels) {
        if (channels >= 3) {
            // R
            *p = (unsigned char)std::fmax(0, std::fmin(255, ((*p) + increase)));
            // G
            *(p + 1) = (unsigned char)std::fmax(0, std::fmin(255, (*(p + 1) + increase)));
            // B
            *(p + 2) = (unsigned char)std::fmax(0, std::fmin(255, (*(p + 2) + increase)));
        }
        else {
            *p = (unsigned char)std::fmax(0, std::fmin(255, ((*p) + increase)));
        }
    }
}

unsigned char ImageFilter::get_increase(Image& image, int channels, float percent_change)
/**
 * @brief Get the increase value for each pixel based on the average brightness of the image
 *
 * @param[in] image
 * @param[in] channels
 * @param[in] percent_change
 * @return unsigned char
 *
 *
*/
{
    int total = 0;
    for (unsigned char* p = image.data; p != image.data + image.get_size(); p += channels) {
        if (channels >= 3) {
            total += (uint8_t)*p;
            total += (uint8_t) * (p + 1);
            total += (uint8_t) * (p + 2);
        }
        else {
            total += *p;
        }
    }

    std::cout << "total: " << total << std::endl;
    if (image.get_channels() == 4) {
        total = total / ((3 * image.get_size()) / 4);
    }
    else {
        total = total / image.get_size();
    }
    unsigned char increase = (unsigned char)(0.2 * (total / channels));
    std::cout << "total: " << total << std::endl;
    std::cout << "increase: " << (int)increase << std::endl;
    return increase;
}


void ImageFilter::to_grayscale(Image& image)
/**
 * @brief Convert an image to grayscale
 *
 * @param[in] image
*/
{

    // Check number of channels
    int channels = image.get_channels();
    int gray_channels = channels == 4 ? 2 : 1;
    int gray_size;

    // Already grayscale
    if (channels == 1 || channels == 2) {
        return;
    }

    // Need to copy alpha channel
    gray_size = image.get_width() * image.get_height() * gray_channels;

    unsigned char* gray_image = new unsigned char[gray_size];

    for (unsigned char* p = image.data, *pgray = gray_image; p != image.data + image.get_size(); p += channels, pgray += gray_channels) {
        if (channels >= 3) {
            *pgray = (unsigned char)((*p + *(p + 1) + *(p + 2)) / 3.0);
            if (channels == 4) {
                *(pgray + 1) = *(p + 3);
            }
        }
    }
    image.update(gray_image, gray_channels, gray_size);

    delete[] gray_image;
}

void ImageFilter::color_balance(Image& image)
/**
 * @brief Apply color balance to an image
 * 
 * @param[in] image
*/
{
    // Check ## of channels
    int width = image.get_width();
    int height = image.get_height();
    int channels = image.get_channels();
    int points = width * height;
    int size = image.get_size();

    if (channels == 1 || channels == 2) {return;}

    double avg_r=0.0, avg_b=0.0, avg_g=0.0;
    unsigned char* outputImageData = new unsigned char[size];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            avg_r += image.data[index];
            avg_g += image.data[index+1];
            avg_b += image.data[index+2];
        }
    }

    avg_r /= points;
    avg_g /= points;
    avg_b /= points;

    double avg_intensity = (avg_r + avg_g + avg_b) / 3.0;
    double scale_r = avg_intensity / avg_r;
    double scale_g = avg_intensity / avg_g;
    double scale_b = avg_intensity / avg_b;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            outputImageData[index] = (unsigned char)std::fmax(0, std::fmin(255, scale_r * image.data[index]));
            outputImageData[index+1] = (unsigned char)std::fmax(0, std::fmin(255, scale_r * image.data[index+1]));
            outputImageData[index+2] = (unsigned char)std::fmax(0, std::fmin(255, scale_r * image.data[index+2]));
            if (channels == 4) {
                outputImageData[index + 3] = static_cast<unsigned char>(image.data[index+3]);
            }
        }
    }

    image.update(outputImageData, channels, size);
    delete[] outputImageData;

}

void ImageFilter::edge_detection(Image &image, std::string filter, int threshold)
/**
 * @brief Apply the Sobel filter to an image
 *
 * @param[in] image
 * @param[in] filter Must be one of Sobel, Prewitt, and Scharr
 * @param[in] threshold
*/
{

    // Since the input image has already been grayscaled, the channel size is either 1 or 2
    int channels = image.get_channels();
    int width = image.get_width();
    int height = image.get_height();
    int size = image.get_size();

    unsigned char* outputImageData = new unsigned char[size];

    std::vector<int> y_mask;
    std::vector<int> x_mask;

    // Define the filters depending on the user input
    if (filter == "Sobel") {
        y_mask = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
        x_mask = { 1, 0, -1, 2, 0, -2, 1, 0 , -1 };
    }

    else if (filter == "Prewitt") {
        y_mask = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
        x_mask = { 1, 0, -1, 1, 0, -1, 1, 0 , -1 };
    }

    else if (filter == "Scharr") {
        y_mask = { 3, 10, 3, 0, 0, 0, -3, -10, -3 };
        x_mask = { 3, 0, -3, 10, 0, -10, 3, 0 , -3 };
    }

    // Convolute image with Sobel filter
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {

            float gx = 0, gy = 0;

            gx += x_mask[0] * image.data[(x - 1) * channels + width * (y - 1) * channels];
            gy += y_mask[0] * image.data[(x - 1) * channels + width * (y - 1) * channels];
            gy += y_mask[1] * image.data[(x - 1) * channels + width * y * channels];
            gx += x_mask[2] * image.data[(x - 1) * channels + width * (y + 1) * channels];
            gy += y_mask[2] * image.data[(x - 1) * channels + width * (y + 1) * channels];
            gx += x_mask[3] * image.data[x * channels + width * (y - 1) * channels];
            gx += x_mask[5] * image.data[x * channels + width * (y + 1) * channels];
            gx += x_mask[6] * image.data[(x + 1) * channels + width * (y - 1) * channels];
            gy += y_mask[6] * image.data[(x + 1) * channels + width * (y - 1) * channels];
            gy += y_mask[7] * image.data[(x + 1) * channels + width * y * channels];
            gx += x_mask[8] * image.data[(x + 1) * channels + width * (y + 1) * channels];
            gy += y_mask[8] * image.data[(x + 1) * channels + width * (y + 1) * channels];

            int index = (y * width + x) * channels;
            double edge = sqrt(gx * gx + gy * gy);

            if (edge > 255) {
                edge = 255;
            }
            else if (edge < threshold) {
                edge = 0;
            }

            outputImageData[index] = edge;
        }
    }

    //update image

    image.update(outputImageData, channels, size);
    delete[] outputImageData;
}

std::vector<float> ImageFilter::generateKernel(float kernelSize, double sigma,std::string type)
/**
 * @brief generate kernel for Gaussian filter and Box filter
 * @param[in] kernel_size
 * @param[in] standard deviation for Gaussian function
 * @param[in] choose to generate kernel for Gaussian blur or Box blur
 * @return kernel matrix
*/
{
    std::vector<float> kernel(kernelSize);
    float sum = 0.0;
    int halfSize = kernelSize / 2;
    
    if (type == "Gaussian"){
        for (int i = 0; i < kernelSize; ++i) {
            double x = i - halfSize;
            kernel[i] = exp(-x * x / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
            sum += kernel[i];
        }

        for (int i = 0; i < kernelSize; ++i) {
            kernel[i] /= sum;
        }
    }
    else if (type == "Box"){
        for (int i = 0; i < kernelSize; ++i) {
            kernel[i] = 1 / kernelSize;
        } 
    }
    return kernel;
}

void ImageFilter::convolution(Image& image, unsigned char* outputImageData, int halfSize, std::vector<float> kernel)
/**
 * @brief Convolution structure for Gaussian blur and Box blur
 * @param[in] image
 * @param[in] pointer to output image data
 * @param[in] half size of the kernel
 * @param[in] kernel
*/
{
    int width = image.get_width();
    int height = image.get_height();
    int channels = image.get_channels();
    int size = image.get_size();

    unsigned char *outputImageData_x = new unsigned char[size];
    
    //convolute horizontally
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0, g = 0, b = 0, a = 0;

            for (int k = -halfSize; k <= halfSize; ++k) {
                int n = x + k;
                if (n >= 0 && n < width) {
                    int index = (y * width + n) * channels;
                    // std::cout << index << std::endl;
                    if (channels == 1 || channels == 2) {
                        r += kernel[k + halfSize] * image.data[index];
                        if (channels == 2) {
                            a = image.data[index + 1]; //the alpha channel
                        }
                    }
                    if (channels >= 3) {
                        r += kernel[k + halfSize] * image.data[index];
                        g += kernel[k + halfSize] * image.data[index + 1];
                        b += kernel[k + halfSize] * image.data[index + 2];
                        if (channels == 4) {
                            a = image.data[index + 3]; //the alpha channel
                        }
                    }
                }
            }
            //change to char form
            int index = (y * width + x) * channels;
            if (channels == 1 || channels == 2) {
                outputImageData_x[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                if (channels == 2) {
                    outputImageData_x[index + 1] = static_cast<unsigned char>(a);
                }
            }
            if (channels >= 3) {
                outputImageData_x[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                outputImageData_x[index + 1] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, g)));
                outputImageData_x[index + 2] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, b)));
            }
            if (channels == 4) {
                outputImageData_x[index + 3] = static_cast<unsigned char>(a);
            }
        }
    }

    //convolute vertically
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0, g = 0, b = 0, a = 0;

            for (int k = -halfSize; k <= halfSize; ++k) {
                int n = y + k;
                if (n >= 0 && n < height) {
                    int index = (n * width + x) * channels;
                    if (channels == 1 || channels == 2) {
                        r += kernel[k + halfSize] * outputImageData_x[index];
                        if (channels == 2) {
                            a = outputImageData_x[index + 1]; //the alpha channel
                        }
                    }
                    if (channels >= 3) {
                        r += kernel[k + halfSize] * outputImageData_x[index];
                        g += kernel[k + halfSize] * outputImageData_x[index + 1];
                        b += kernel[k + halfSize] * outputImageData_x[index + 2];
                        if (channels == 4) {
                            a = outputImageData_x[index + 3]; //the alpha channel
                        }
                    }
                }
            }
            //change to char form
            int index = (y * width + x) * channels;
            if (channels == 1 || channels == 2) {
                outputImageData[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                if (channels == 2) {
                    outputImageData[index + 1] = static_cast<unsigned char>(a);
                }
            }
            if (channels >= 3) {
                outputImageData[index] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, r)));
                outputImageData[index + 1] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, g)));
                outputImageData[index + 2] = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, b)));
            }
            if (channels == 4) {
                outputImageData[index + 3] = static_cast<unsigned char>(a);
            }
        }
    }
    delete[] outputImageData_x;
}

void ImageFilter::GaussianFilter(Image& image, int kernelSize = 5, double sigma = 1.0)
/**
 * @brief Add Gaussian filter to the image and replace the original image
 *
 * @param[in] image
 * @param[in] size of the kernal
 * @param[in] standard deviation for Gaussian function
*/
{
    std::vector<float> kernel = generateKernel(kernelSize, sigma, "Gaussian");
    int halfSize = kernelSize / 2;
    int channels = image.get_channels();
    int size = image.get_size();


    unsigned char* outputImageData = new unsigned char[size];

    convolution(image, outputImageData, halfSize, kernel);

    //update image
    image.update(outputImageData, channels, size);
    delete[] outputImageData;
}

void ImageFilter::BoxFilter(Image& image, int kernelSize = 5)
/**
 * @brief Add Box blur filter to the image and replace the original image
 *
 * @param[in] image
 * @param[in] size of the kernal
*/
{
    double sigma = 1.;
    std::vector<float> kernel = generateKernel(kernelSize, sigma, "Box");
    int halfSize = kernelSize / 2;
    int channels = image.get_channels();
    int size = image.get_size();


    unsigned char* outputImageData = new unsigned char[size];

    convolution(image, outputImageData, halfSize, kernel);

    //update image
    image.update(outputImageData, channels, size);
    delete[] outputImageData;
}

/**
 * Use quick select to find the median
 *
 * @param nums The input window.
 * @param left The left index.
 * @param right The right index.
 */
unsigned char ImageFilter::partition(unsigned char* nums, int left, int right) {
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
unsigned char ImageFilter::quick_select(unsigned char* nums, int left, int right, int k) {
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
 * Replicate padding for an image.
 *
 * @param img The input image.
 * @param padded_img The output image with padding.
 * @param padding The padding size.
 */
void ImageFilter::replicate_padding(Image& img, unsigned char* padded_img, int padding) {
    int width = img.get_width();
    int height = img.get_height();
    int channel = img.get_channels();
    int new_width = width + 2 * padding;

    for (int row = -padding; row < height + padding; ++row) {
        for (int col = -padding; col < width + padding; ++col) {
            int src_row = min(max(row, 0), height - 1);
            int src_col = min(max(col, 0), width - 1);

            for (int ch = 0; ch < channel; ++ch) {
                padded_img[((row + padding) * new_width + col + padding) * channel + ch] =
                    img.data[(src_row * width + src_col) * channel + ch];
            }
        }
    }
}


/**
 * Applies a median filter to an image using the quick-select algorithm.
 *
 * @param img The input image.
 * @param kernel_size The size of the median filter kernel.
 */
void ImageFilter::median_filter(Image& img, int kernel_size) {
    int width = img.get_width();
    int height = img.get_height();
    int channel = img.get_channels();
    int padding = kernel_size / 2;
    int new_width = width + 2 * padding;
    int new_height = height + 2 * padding;
    unsigned char* padded_image = new unsigned char[new_width * new_height * channel];
    unsigned char* new_img = new unsigned char[width * height * channel];

    replicate_padding(img, padded_image, padding);

    int window_size = kernel_size * kernel_size;
    unsigned char* window = new unsigned char[window_size];
    int half_window_size = window_size / 2;

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            for (int ch = 0; ch < channel; ++ch) {
                int window_idx = 0;
                for (int k_row = -padding; k_row <= padding; ++k_row) {
                    for (int k_col = -padding; k_col <= padding; ++k_col) {
                        int cur_row = row + padding + k_row;
                        int cur_col = col + padding + k_col;

                        int padded_idx = (cur_row * new_width + cur_col) * channel + ch;
                        if (window_idx < window_size) {
                            window[window_idx++] = padded_image[padded_idx];
                        }
                    }
                }
                // Use quick select to find median
                unsigned char median = quick_select(window, 0, window_size - 1, half_window_size);
                int new_img_idx = (row * width + col) * channel + ch;
                new_img[new_img_idx] = median;
            }
        }
    }
    img.update(new_img, channel, width * height * channel);
    delete[] window;
    delete[] padded_image;
    delete[] new_img;
}


void ImageFilter::histogram_equalization(Image& img)
/**
 * @brief histogram equalising an image
 *
 * @param[in] img
*/
{
    std::vector<int> histogram(256, 0);
    int w = img.get_width();
    int l = img.get_height();
    int channels= img.get_channels();

    unsigned char* output_image = new unsigned char[w * l * channels];

    // Compute the histogram
    for (int i = 0; i < w * l * channels; i += channels) 
    {
        histogram[img.data[i]]++;
    }

    // Calculate the cumulative distribution function (CDF)
    std::vector<int> cdf(256, 0);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) 
    {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    // Find the minimum and maximum values of CDF
    int cdf_min = cdf[0];
    int cdf_max = cdf[255];
    for (int i = 1; i < 256; ++i) 
    {
        if (cdf[i] < cdf_min) cdf_min = cdf[i];
        if (cdf[i] > cdf_max) cdf_max = cdf[i];
    }

    // Normalize the CDF
    float cdf_range = static_cast<float>(cdf_max - cdf_min);
    for (int i = 0; i < 256; ++i) 
    {
        cdf[i] = static_cast<int>(((cdf[i] - cdf_min) / cdf_range) * 255);
    }
    // Perform histogram equalization using CDF
    for (int i = 0; i < w * l * channels; i += channels) 
    {
        output_image[i] = static_cast<unsigned char>(cdf[img.data[i]]);
    }

    img.update(output_image, channels, w * l * channels);
    delete[] output_image;
}
