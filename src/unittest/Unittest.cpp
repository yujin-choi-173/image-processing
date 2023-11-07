/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <tuple>

#include "Unittest.h"

std::tuple<int,int>  Unittest::test_adjust_brightness()
/**
 * @brief test the adjust brightness member function
*/
{
    return test_2D(0);
}

std::tuple<int,int>  Unittest::test_to_grayscale()
/**
 * @brief test the to_gray member function
*/
{   
    return test_2D(1);
}

std::tuple<int,int>  Unittest::test_color_balance()
/**
 * @brief test the color balance member function
*/
{
    return test_2D(2);
}

std::tuple<int,int>  Unittest::test_edge_detection()
/**
 * @brief test the Sobel, Prewitt, Scharr edge detection member function
*/
{   
    int passed = 0;
    int failed = 0;
    std::tuple<int,int> sobel;
    std::cout<<"Sobel:"<<std::endl;
    sobel = test_2D(3);
    passed += std::get<0>(sobel);
    failed += std::get<1>(sobel);

    std::tuple<int,int>  prewitt;
    std::cout<<"Prewitt:"<<std::endl;
    prewitt = test_2D(4);
    passed += std::get<0>(prewitt);
    failed += std::get<1>(prewitt);

    std::tuple<int,int> scharr;
    std::cout<<"Scharr:"<<std::endl;
    scharr = test_2D(5);
    passed += std::get<0>(scharr);
    failed += std::get<1>(scharr);

    std::tuple<int,int> total = {passed, failed};
    return total;
}

std::tuple<int,int>  Unittest::test_GaussianFilter()
/**
 * @brief test the gaussianFilter member function
*/
{
    return test_2D(6);
}

std::tuple<int,int>  Unittest::test_median_filter()
/**
 * @brief test the median_filter member function
*/
{
    return test_2D(7);
}

std::tuple<int,int>  Unittest::test_histogram_equalization()
/**
 * @brief test the histogram equalization member function
*/
{
    return test_2D(8);
}

std::tuple<int,int>  Unittest::test_2D(int sign=0)
/**
 * @brief combine all the 2D test progresses
 * 
 * @param[in] sign from 0 to 8  0: adjust_brightness; 1: to_grayscale; 2: color_balance;
 * 3: edge_detection(Sobel); 4: edge_detection(Prewitt); 5: edge_detection(Scharr);
 * 6: GaussianFilter; 7: median_filter; 8: histogram_equalization
*/
{
    int passed = 0;
    int failed = 0;
    int width = 3;
    int height = 3;
    int channel = 4;

    unsigned char* data = new unsigned char[37];
    // Initialize the input 2D image with some values.
    unsigned char value = 1;
    //cout << value << endl;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            for (int ch = 0; ch < channel; ++ch) {
                data[(row * width + col) * channel + ch] = value;
                value++;
            }
        }
    }
    
    Image img(data, width, height, channel, "test");

    if (sign == 0)
    {
        ImageFilter::adjust_brightness(img, 50);
        if (img.data[0] == 51)
        {
            std::cout<<"The adjust_brightness filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The adjust_brightness filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 1)
    {
        ImageFilter::to_grayscale(img);
        channel = 1;
        if (img.data[0] == 2)
        {
            std::cout<<"The to_gray filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The to_gray filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 2)
    {
        ImageFilter::color_balance(img);
        if (img.data[0] == 1)
        {
            std::cout<<"The color_balance filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The color_balance filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 3)
    {
        ImageFilter::edge_detection(img, "Sobel", 100);
        if (img.data[0] == 0)
        {
            std::cout<<"The Sobel edge detection filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The Sobel edge detection filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 4)
    {
        ImageFilter::edge_detection(img, "Prewitt", 100);
        if (img.data[0] == 0)
        {
            std::cout<<"The Prewitt edge detection filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The Prewitt edge detection filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 5)
    {
        ImageFilter::edge_detection(img, "Scharr", 100);
        if (img.data[0] == 0)
        {
            std::cout<<"The Scharr edge detection filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The Scharr edge detection filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 6)
    {
        ImageFilter::GaussianFilter(img, 3, 1.0);
        if (img.data[0] == 3)
        {
            std::cout<<"The Gaussian filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The Gaussian filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 7)
    {
        ImageFilter::median_filter(img, 3);
        if (img.data[0] == 5)
        {
            std::cout<<"The Median filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The Median filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 8)
    {
        ImageFilter::to_grayscale(img);
        channel = 1;
        ImageFilter::histogram_equalization(img);
        if (img.data[0] == 28)
        {
            std::cout<<"The histogram_equalization filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The histogram_equalization filter is False."<<std::endl;
            failed += 1;
        }
    }
    //output
    std::cout << "Filtered result:" << std::endl;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::cout << "(";
            for (int ch = 0; ch < channel; ++ch) {
                std::cout << static_cast<double>(img.data[(row * width + col) * channel + ch]);
                if (ch != channel - 1) std::cout << ", ";
            }
            std::cout << ") ";
        }
        std::cout << std::endl;
    }
    return {passed, failed};
}

std::tuple<int,int>  Unittest::test_3D_median()
/**
 * @brief test the 3D_median_filter member function
 * 
 * @param[in] kernelSize
*/
{
    return test_3D(1);
}

std::tuple<int,int>  Unittest::test_3D_GaussianFilter()
/**
 * @brief test the 3D_GaussianFilter member function
*/
{
    return test_3D(0);
}

std::tuple<int,int> Unittest::test_3D(int sign)
/**
 * @brief combine all the 3D test progresses
 * 
 * @param[in] kernelSize for GaussianFilter3D and medianFilter
 * @param[in] sigma for GaussianFilter3D
 * @param[in] sign from 0 to 1; 0: GaussianFilter; 1: median3D_filter
*/
{
    int passed = 0;
    int failed = 0;
    int width = 3;
    int height = 3;
    int channel = 1;
    int volume = 2;

    unsigned char* data = new unsigned char[101];
    // Initialize the input 3D image with some values.
    unsigned char value = 1;
    //cout << value << endl;
    for (int z = 0; z < volume; ++z) {
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                for (int ch = 0; ch < channel; ++ch) {
                    data[((z * height + row) * width + col) * channel + ch] = value;
                    value++;
                }
            }
        }
    }

    Volume vol(data, width, height, channel, volume, "test");

    if (sign == 0 )
    {
        VolumeFilter::GaussianFilter3d(vol, 3, 1.0);
        if (vol.data[0] == 1)
        {
            std::cout<<"The GaussianFilter3D filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The GaussianFilter3D filter is False."<<std::endl;
            failed += 1;
        }
    }
    else if (sign == 1)
    {
        VolumeFilter::median3D_filter(vol, 3);
        if (vol.data[0] == 4)
        {
            std::cout<<"The medianFilter3D filter is Right."<<std::endl;
            passed += 1;
        }
        else
        {
            std::cout<<"The medianFilter3D filter is False."<<std::endl;
            failed += 1;
        }
    }
        

    std::cout << "Filtered result:" << std::endl;
    for (int depth = 0; depth < volume; ++ depth)
    {
        std::cout<< "[";
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                std::cout << "(";
                for (int ch = 0; ch < channel; ++ch) {
                    std::cout << static_cast<double>(vol.data[(depth * width * height +row * width + col) * channel + ch]);
                    if (ch != channel - 1) std::cout << ", ";
                }
                std::cout << ") ";
            }
            std::cout << std::endl;
        }
        std::cout<< "]"<<std::endl;
    }

    return {passed, failed};
}
void Unittest::test_MIP(bool specify, int min_z, int max_z)
/**
 * @brief testing maximum intensity projection
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * @return no return value
*/
{
 /*
    this member of unit test allows user to decide if they want to test maximum intensity projection module with or without
    specifying a certain slab, and the position of both the head and tail of the slab.
    we create a 1D array containing hyperthetical information of a 3D volume, whose size is 2*2*2 with 1 channel.
    then we call the function from projection and do some implements on our 1D array, and output the value of our array.
    the result should be easy to judge.
 */
    int width = 2;     // initializing the size of volume
    int height = 2;
    int channel = 1;
    int volume = 2;    // containing 2 2D image

    unsigned char* data = new unsigned char[8];  //define our 1D array

    data[0] = 0, data[1] = 50, data[2] = 100, data[3] = 150;     // initialize our 1D array with simple value
    data[4] = 200, data[5] = 250, data[6] = 250, data[7] = 250;

    Volume test_vol(data, width, height, channel, volume, "projection_test");  // define our object of volme 
    Image test_img;                                                  // define our object of output image

    std::cout<< "Initial value of our volume:" << std::endl;    //print out initial volume
    for(int i = 0; i < 8; ++i)
    {
        std::cout<< (int)data[i] <<", ";
    }
    std::cout<<std::endl;

    if(specify == false)   // user deciding whether to cut some slabs in projection
    {
        Projection::max_intensity_projection(test_vol, test_img, false, 0, 0);
    }
    if(specify == true)
    {
        Projection::max_intensity_projection(test_vol, test_img, true, min_z, max_z);
    }

    std::cout<< "after maximum intensity projection, the output of projection :"<<std::endl;
    int h = test_img.get_height();             // get the size of output image
    int w = test_img.get_width();
    int c = test_img.get_channels();
    int size = (h * w) * c;

    for(int i = 0; i < size; ++i)
    {
        std::cout<< (int)test_img.data[i] << ", ";
    }
    std::cout<<std::endl;
}

void Unittest::test_MinIP(bool specify, int min_z, int max_z)
/**
 * @brief testing minimum intensity projection
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * @return no return value
*/
{
 /*
    this member of unit test allows user to decide if they want to test minimum intensity projection module with or without
    specifying a certain slab, and the position of both the head and tail of the slab.
    we create a 1D array containing hyperthetical information of a 3D volume, whose size is 2*2*2 with 1 channel.
    then we call the function from projection and do some implements on our 1D array, and output the value of our array.
    the result should be easy to judge.
 */
    int width = 2;     // initializing the size of volume
    int height = 2;
    int channel = 1;
    int volume = 2;    // containing 2 2D image

    unsigned char* data = new unsigned char[8];  //define our 1D array

    data[0] = 0, data[1] = 50, data[2] = 100, data[3] = 150;     // initialize our 1D array with simple value
    data[4] = 200, data[5] = 250, data[6] = 250, data[7] = 250;

    Volume test_vol(data, width, height, channel, volume, "projection_test");  // define our object of volme 
    Image test_img;                                                  // define our object of output image

    std::cout<< "Initial value of our volume:" << std::endl;    //print out initial volume
    for(int i = 0; i < 8; ++i)
    {
        std::cout<< (int)data[i] <<", ";
    }
    std::cout<<std::endl;

    if(specify == false)   // user deciding whether to cut some slabs in projection
    {
        Projection::min_intensity_projection(test_vol, test_img, false, 0, 0);
    }
    if(specify == true)
    {
        Projection::min_intensity_projection(test_vol, test_img, true, min_z, max_z);
    }

    std::cout<< "after minimum intensity projection, the output of projection :"<<std::endl;
    int h = test_img.get_height();             // get the size of output image
    int w = test_img.get_width();
    int c = test_img.get_channels();
    int size = (h * w) * c;

    for(int i = 0; i < size; ++i)
    {
        std::cout<< (int)test_img.data[i] << ", ";
    }
    std::cout<<std::endl;
}

void Unittest::test_mean_AIP(bool specify, int min_z, int max_z)
/**
 * @brief testing mean average intensity projection
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * @return no return value
*/
{
 /*
    this member of unit test allows user to decide if they want to test mean average intensity projection module with or without
    specifying a certain slab, and the position of both the head and tail of the slab.
    we create a 1D array containing hyperthetical information of a 3D volume, whose size is 2*2*2 with 1 channel.
    then we call the function from projection and do some implements on our 1D array, and output the value of our array.
    the result should be easy to judge.
 */
    int width = 2;     // initializing the size of volume
    int height = 2;
    int channel = 1;
    int volume = 2;    // containing 2 2D image

    unsigned char* data = new unsigned char[8];  //define our 1D array

    data[0] = 0, data[1] = 50, data[2] = 100, data[3] = 150;     // initialize our 1D array with simple value
    data[4] = 200, data[5] = 250, data[6] = 250, data[7] = 250;

    Volume test_vol(data, width, height, channel, volume, "projection_test");  // define our object of volme 
    Image test_img;                                                  // define our object of output image

    std::cout<< "Initial value of our volume:" << std::endl;    //print out initial volume
    for(int i = 0; i < 8; ++i)
    {
        std::cout<< (int)data[i] <<", ";
    }
    std::cout<<std::endl;

    if(specify == false)   // user deciding whether to cut some slabs in projection
    {
        Projection::mean_avg_intensity_projection(test_vol, test_img, false, 0, 0);
    }
    if(specify == true)
    {
        Projection::mean_avg_intensity_projection(test_vol, test_img, true, min_z, max_z);
    }

    std::cout<< "after mean average intensity projection, the output of projection :"<<std::endl;
    int h = test_img.get_height();             // get the size of output image
    int w = test_img.get_width();
    int c = test_img.get_channels();
    int size = (h * w) * c;

    for(int i = 0; i < size; ++i)
    {
        std::cout<< (int)test_img.data[i] << ", ";
    }
    std::cout<<std::endl;
}

void Unittest::test_median_AIP(bool specify, int min_z, int max_z)
/**
 * @brief testing median average intensity projection
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * @return no return value
*/
{
 /*
    this member of unit test allows user to decide if they want to test medina average intensity projection module with or without
    specifying a certain slab, and the position of both the head and tail of the slab.
    we create a 1D array containing hyperthetical information of a 3D volume, whose size is 2*2*2 with 1 channel.
    then we call the function from projection and do some implements on our 1D array, and output the value of our array.
    the result should be easy to judge.
 */
    int width = 2;     // initializing the size of volume
    int height = 2;
    int channel = 1;
    int volume = 2;    // containing 2 2D image

    unsigned char* data = new unsigned char[8];  //define our 1D array

    data[0] = 0, data[1] = 50, data[2] = 100, data[3] = 150;     // initialize our 1D array with simple value
    data[4] = 200, data[5] = 250, data[6] = 250, data[7] = 250;

    Volume test_vol(data, width, height, channel, volume, "projection_test");  // define our object of volme 
    Image test_img;                                                  // define our object of output image

    std::cout<< "Initial value of our volume:" << std::endl;    //print out initial volume
    for(int i = 0; i < 8; ++i)
    {
        std::cout<< (int)data[i] <<", ";
    }
    std::cout<<std::endl;

    if(specify == false)   // user deciding whether to cut some slabs in projection
    {
        Projection::median_avg_intensity_projection(test_vol, test_img, false, 0, 0);
    }
    if(specify == true)
    {
        Projection::median_avg_intensity_projection(test_vol, test_img, true, min_z, max_z);
    }

    std::cout<< "after median average intensity projection, the output of projection :"<<std::endl;
    int h = test_img.get_height();             // get the size of output image
    int w = test_img.get_width();
    int c = test_img.get_channels();
    int size = (h * w) * c;

    for(int i = 0; i < size; ++i)
    {
        std::cout<< (int)test_img.data[i] << ", ";
    }
    std::cout<<std::endl;
}

void Unittest::run_all()
/**
 * @brief runs all unit tests and prints out the total passed and failed.
*/
{
    int total_passed = 0;
    int total_failed = 0;
    std::tuple<int,int> test;

    test = Unittest::test_adjust_brightness();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_to_grayscale();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_color_balance();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_edge_detection();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_GaussianFilter();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_median_filter();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);
    
    test = Unittest::test_histogram_equalization();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);

    test = Unittest::test_3D_median();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);

    test = Unittest::test_3D_GaussianFilter();
    total_passed += std::get<0>(test);
    total_failed += std::get<1>(test);

    Unittest::test_MIP(false);
    Unittest::test_MinIP(false);
    Unittest::test_mean_AIP(false);
    Unittest::test_median_AIP(false);

    std::cout << std::endl << std::endl << std::endl << "==================== RESULTS ===================" << std::endl << std::endl;
    std::cout << "Tests passed: " << total_passed << std::endl;
    std::cout << "Tests failed: " << total_failed << std::endl << std::endl;
    
}