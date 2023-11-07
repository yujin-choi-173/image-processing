#include <iostream>
#include <string>
#include <array>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <filesystem>
#define OUTPUT_DIR "../Output/"

int main() {

    int w, h, c;
    unsigned char* data;
    char* name = "../Images/gracehopper.png";

    for (const auto & entry : std::filesystem::directory_iterator("../Scans/confuciusornis"))
        std::cout << entry.path() << std::endl;



    // std::filesystem::path in_file;
    // in_file = (name);
    // std::string filename = std::string(in_file.relative_path());
    // // std::string str(in_file.relative_path());
    // const char *f = filename.c_str();
    // // std::cout << in_file.relative_path().c_str() << std::endl;
    // std::cout << "f " << f << std::endl;
    // // std::cout << in_file.relative_path() << std::endl;
    // // std::cout << in_file.filename() << std::endl;
    // // std::cout << in_file.stem() << std::endl;
    // // std::cout << in_file.extension() << std::endl;
    // // std::cout << in_file.root_path() << std::endl;

    // std::filesystem::path output_dir (OUTPUT_DIR);
    // std::filesystem::path output_path = output_dir / in_file.stem();
    // try {
    //     std::filesystem::create_directories(output_path);
    // }
    // catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
    //     std::cout << e.what() << std::endl;
    // }

    // // // Read in image file
    // data = stbi_load(f, &w, &h, &c, 0);

    // // std::unique_ptr<unsigned char> ptr;
    // // Print image size to screen
    // std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 

    // // Save image to new filename
    // int success = stbi_write_png("output.png", w, h, c, data, 0);

    // // Deallocate memory
    // stbi_image_free(data);

    return 0;
}