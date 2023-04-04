#include "data/Data.h"
#include "image/Image.h"
#include "volume/Volume.h"
#include "filter/ImageFilter.h"
#include "filter/VolumeFilter.h"
#include "projection/Projection.h"
#include "slice/Slice.h"
#include "unittest/Unittest.h"
#include <string>
#include <sstream>
#include <stdexcept>



bool is_int(const char* str) {
    char* p;
    int num = strtol(str, &p, 10);
    if (*p != 0) {
        return false;
    } else {
        return true;
    }
}

int main(int argc, const char *argv[]) {

    if (argc == 2) {
        if (std::string(argv[1]) == "--test") {
            Unittest::run_all();
            exit(0);
        }
    }

    if (argc < 4 || std::string(argv[1]) == "--help"){
        std::cout << ">> Usage: ./main [input type (either image or volume)] [input file path] --[filter name] [filter options]\n";
        std::cout << ">> Available 2D filters: \n   --gaussian_blur - [user defined kernel size] (either 5 or 7) \n --brightness - user defined brightness (integer) \n   --grayscale \n   --color \n   --histogram \n   --median \n   --box \n   --sobel \n   --scharr \n   --prewitt"<< std::endl;
        std::cout << ">> Available 3D filters: \n   --gaussian_blur - user defined kernel size \n   --median [user defined kernel size]"<< std::endl;
        std::cout << ">> Available Orthographic projections: \n   --mip - maximum intensity projection, optional user defined slab positions (both min & max required) \n   --minip - minimum intensity projection, optional user defined slab positions (both min & max required) \n   --aip - average intensity projection, optional user defined slab positions (both min & max required)" << std::endl;
        std::cout << ">> Available 3D slices: \n   --slice_xz - slicing in the xz plane, user defined y position \n   --slice_yz - slicing in the yz plane, user defined x position"<< std::endl;
        std::cout << "Tests: \n   --test, to run unit tests" << std::endl;
        exit(0);
    }

    // Check if the input file is 2D or 3D
    std::string dimension = argv[1];

    if (dimension == "--image" || dimension == "--Image"){
        // Input image
        Image img = Image((char*)argv[2]);

        // Output image
        std::string output_img = "";

        // Start the loop here for multiple filters
        int i=3;
        while (i<argc){
            std::string action = argv[i];
            if (action == "--gaussian_blur" || action == "--Gaussian_Blur"){
                
                if (i+1 == argc){
                    std::cout << "Gaussian kernel size not given" << std::endl;
                    throw std::invalid_argument( "Gaussian kernel size not given" );
                    // exit(0);
                }
                int kernel_size = atoi(argv[i+1]);
                std::cout << "Applying Gaussian blur ..." << std::endl;            
                ImageFilter::GaussianFilter(img, kernel_size, 1.0);
                output_img += "gaussian_";
                std::cout << output_img << std::endl;
                i+=2;
            }
            else if (action == "--brightness" || action == "--Brightness"){
                if (i+1 == argc){
                    std::cout << "Brightness not given" << std::endl;
                    exit(0);
                }
                int brightness = atoi(argv[i+1]);
                std::cout << "Adjusting brightness ..." << std::endl;
                ImageFilter::adjust_brightness(img, brightness);
                output_img += "brightness" + std::to_string(brightness) + "_";
                i += 2;
            }
            else if (action == "--grayscale" || action == "--Grayscale"){
                std::cout << "Applying grayscale filter ..." << std::endl;
                ImageFilter::to_grayscale(img);
                output_img += "grayscale_";
                i++;
            }
            else if (action == "--scharr" || action == "--Scharr"){
                std::cout << "Applying Scharr filter ..." << std::endl;
                ImageFilter::to_grayscale(img);
                ImageFilter::edge_detection(img, "Scharr", 100);
                output_img += "scharr_";
                i++;
            }
            else if (action == "--sobel" || action == "--Sobel"){
                std::cout << "Applying Sobel filter ..." << std::endl;
                ImageFilter::to_grayscale(img);
                ImageFilter::edge_detection(img, "Sobel", 100);
                output_img += "sobel_";
                i++;
            }
            else if (action == "--prewitt"|| action == "--Prewitt"){
                std::cout << "Applying Prewitt filter ..." << std::endl;
                ImageFilter::to_grayscale(img);
                ImageFilter::edge_detection(img, "Prewitt", 100);
                output_img += "prewitt_";
                i++;
            }
            else if (action == "--color" || action == "--Color"){
                ImageFilter::color_balance(img);
                std::cout << "Applying automatic color balance ..." << std::endl;
                output_img += "color_";
                i++;
            }
            else if (action == "--box" || action == "--Box"){
               if (i+1 == argc){
                    std::cout << "Box blur kernel size not given" << std::endl;
                    exit(0);
                }
                int kernel_size = atoi(argv[i+1]);
                ImageFilter::BoxFilter(img, kernel_size);
                std::cout << "Applying box blur ..." << std::endl;
                output_img += "box_";
                i+=2;
            }
            else if (action == "--median_blur" || action == "--Median_Blur"){
                if (i+1 == argc){
                    std::cout << "Median blur kernel size not given" << std::endl;
                    exit(0);
                }
                int kernel_size = atoi(argv[i+1]);
                ImageFilter::median_filter(img, kernel_size);
                std::cout << "Applying median blur ..." << std::endl;
                output_img += "median_";
                i+=2;
            }
            else if (action == "--histogram" || action == "--Histogram"){
                ImageFilter::histogram_equalization(img);
                std::cout << "Applying histogram equalisation ..." << std::endl;
                output_img += "histogram_";
                i++;
            }
            else{
                std::cout << "Invalid argument: " << action << std::endl;
                exit(0);
            }
            
        }
        // Write the final image with all the filters applied
        output_img.pop_back();
        img.write_file(output_img);
    }
    else if (dimension == "--volume" || dimension == "--Volume"){
        // Input volume
        Volume vol = Volume((char*)argv[2]);

        // Output volume
        std::string output_vol = "";
        
        // Start the loop here for multiple filters
        int i=3;
        while (i<argc){
            std::string action = argv[i];
            std::cout << action << std::endl;
            if (action == "--gaussian_blur" || action == "--Gaussian_Blur"){
                if (i+1 == argc){
                    std::cout << "Gaussian kernel size not given" << std::endl;
                    exit(0);
                }
                int kernel_size = atoi(argv[i+1]);
                std::cout << "Applying Gaussian blur ..." << std::endl;            
                VolumeFilter::GaussianFilter3d(vol, 5, 1.0);
                output_vol += "gaussian_blur_";
                i += 2;
            }
            else if (action == "--median_blur" || action == "--Median_Blur"){
                if (i+1 == argc){
                    std::cout << "Median blur kernel size not given" << std::endl;
                    exit(0);
                }
                int kernel_size = atoi(argv[i+1]);
                std::cout << "Applying median blur ..." << std::endl;
                VolumeFilter::median3D_filter(vol, kernel_size);
                output_vol += "median_blur_";
                i += 2;
            }
            else if (action == "--MIP" || action == "--mip"){

                // min_z and max_z will not have an effect if specify is false
                bool specify = false;
                int min_z = 0, max_z = 0;
                std::string range = "";
                // Check if they are specifying the max and min z values
                
                if (i+1 != argc && i+2 != argc){
                    
                    if (is_int(argv[i+1]) && is_int(argv[i+2])) {
                        specify = true;
                        min_z = atoi(argv[i+1]);
                        max_z = atoi(argv[i+2]);
                        range.append("_").append(argv[i+1]).append("-").append(argv[i+2]);
                        i += 2;
                    } 
                } else if (i+1 != argc) {
                    // If the next value is an int, but the one after is not
                    // the user has specified only the min z value.
                    if (is_int(argv[i+1])) {
                        std::cout << "Both min and max must be given if projecting a slab." << std::endl;
                        exit(0);
                    }
                }
                Image projection;
                std::cout << "Performing maximum intensity projection ..." << std::endl;
                Projection::max_intensity_projection(vol, projection, specify, min_z, max_z);
                projection.input_file = vol.input_file;
                projection.write_file(output_vol + "maximum_intensity_projection" + range);
                i++;
            }
            else if (action == "--MinIP" || action == "--minip"){
                // min_z and max_z will not have an effect if specify is false
                bool specify = false;
                int min_z = 0, max_z = 0;
                std::string range = "";
                // Check if they are specifying the max and min z values
                
                if (i+1 != argc && i+2 != argc){
                    
                    if (is_int(argv[i+1]) && is_int(argv[i+2])) {
                        specify = true;
                        min_z = atoi(argv[i+1]);
                        max_z = atoi(argv[i+2]);
                        range.append("_").append(argv[i+1]).append("-").append(argv[i+2]);
                        i += 2;
                    } 
                } else if (i+1 != argc) {
                    // If the next value is an int, but the one after is not
                    // the user has specified only the min z value.
                    if (is_int(argv[i+1])) {
                        std::cout << "Both min and max must be given if projecting a slab." << std::endl;
                        exit(0);
                    }
                }
                Image projection;
                std::cout << "Performing minimum intensity projection ..." << std::endl;
                Projection::min_intensity_projection(vol, projection, specify, min_z, max_z);
                projection.input_file = vol.input_file;
                projection.write_file(output_vol + "minimum_intensity_projection" + range);
                i++;
            }
            else if (action == "--AIP" || action == "--aip"){
                // min_z and max_z will not have an effect if specify is false
                bool specify = false;
                int min_z = 0, max_z = 0;
                std::string range = "";
                // Check if they are specifying the max and min z values
                
                if (i+1 != argc && i+2 != argc){
                    
                    if (is_int(argv[i+1]) && is_int(argv[i+2])) {
                        specify = true;
                        min_z = atoi(argv[i+1]);
                        max_z = atoi(argv[i+2]);
                        range.append("_").append(argv[i+1]).append("-").append(argv[i+2]);
                        i += 2;
                    } 
                } else if (i+1 != argc) {
                    // If the next value is an int, but the one after is not
                    // the user has specified only the min z value.
                    if (is_int(argv[i+1])) {
                        std::cout << "Both min and max must be given if projecting a slab." << std::endl;
                        exit(0);
                    }
                }
                Image projection;
                std::cout << "Performing median average intensity projection ..." << std::endl;
                Projection::median_avg_intensity_projection(vol, projection, specify, min_z, max_z);
                projection.input_file = vol.input_file;
                projection.write_file(output_vol + "average_intensity_projection" + range);
                i++;
            }
            else if (action == "--slice_xz" || action == "--Slice_xz"){
                if (i+1 == argc){
                    std::cout << "Point y not provided for slice on x-z plane." << std::endl;
                    exit(0);
                }
                int y = atoi(argv[i+1]);
                Image slice;
                Slice::slice_xz(vol, slice, y);
                slice.input_file = vol.input_file;
                slice.write_file(output_vol + "slice_xz_" + std::to_string(y));
                i += 2;
            }
            else if (action == "--slice_yz" || action == "--Slice_yz"){
                if (i+1 == argc){
                    std::cout << "Point y not provided for slice on y-z plane." << std::endl;
                    exit(0);
                }
                int x = atoi(argv[i+1]);
                Image slice;
                Slice::slice_yz(vol, slice, x);
                slice.input_file = vol.input_file;
                slice.write_file(output_vol + "slice_yz_" + std::to_string(x));
                i += 2;
            }
            else{
                std::cout << "Invalid argument: " << action << std::endl;
                exit(0);
            }
        }
    }
    return 0;
}


