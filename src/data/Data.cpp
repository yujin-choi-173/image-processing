/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include "Data.h"
#include <string>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#define OUTPUT_DIR "../Output/"

Data::Data()
{
    // // input_file = ("../Images/gracehopper.png");
    // this->data = new unsigned char[1];
    // delete this->data;
}

// Constructor
Data::Data(char* file_name): file_name(file_name), is_dir(false)
/**
 * @brief Constructor for Data used for single images. is_dir will default to False.
 * 
 * @param file_name The path to the image file.
 * 
*/
{   
    this->input_file = (file_name);
    this->read_file();
    this->size = this->w * this->h * this->c;
}

// Constructor - for directory (volume data)
Data::Data(char* file_name, bool is_dir): file_name(file_name), is_dir(is_dir)
/**
 * @brief Constructor for a new data object allowing the specification of is_dir.
 *        This is used for volume data, since an entire directory of images is read.
 * 
 * @param file_name If is_dir is true, this is the path to a directory. Otherwise it is the path to a file.
 * @param is_dir True if the data is a directory of images. False if the data is a single image.
 */
{   
    if (is_dir) {
        this->input_file = (file_name);
        this->read_dir();
    }
}

Data::Data(unsigned char* data, int w, int h, int c, char* name): num_files(1), is_dir(false)
/**
 * @brief Constructor for Data allowing the specification of a data array along with the dimensions of a single image.
 *        It is assumed to be a single image and is_dir will default to False.
 * 
 * @param data The data array containing the image data.
 * @param w The width of the image.
 * @param h The height of the image.
 * @param c The number of channels in the image.
 * @param name The name of the image.
 * 
*/
{
    this->w = w;
    this->h = h;
    this->c = c;
    this->update(data, c, w * h * c) ;   
    this->input_file = (name);
    this->input_file.replace_extension(".png");
}

Data::Data(unsigned char* data, int w, int h, int c, int num_files, char* name): num_files(num_files), is_dir(true)
/**
 * @brief Constructor for Data allowing the specification of a data array of many constituent images of a volume.
 *        It is assumed to be a volume and the maximum z dimension is num_files, the number of images.
 * 
 * @param data The data array containing the volume data.
 * @param w The width of a single image.
 * @param h The height of a single image.
 * @param c The number of channels in the image.
 * @param num_files The number of constituent images.
 * @param name The name of the volume.
 * 
*/
{
    this->w = w;
    this->h = h;
    this->c = c;
    this->update(data, c, w * h * num_files) ;   
    this->input_file = (name);
    // this->input_file.replace_extension(".png");
}

// Copy constructor
Data::Data(Data &data): file_name(data.file_name)
{   
    input_file = (file_name);
    this->read_file();
    this->size = this->w * this->h * this->c;
}

// Destructor
Data::~Data()
/**
 * @brief Destructor for Data. Ensures that allocated memory is freed.
*/
{
    if (file_read)
        stbi_image_free(data); 
}

int Data::get_size() const {
    return this->size;
}

void Data::read_file() 
/**
 * @brief Reads the image file and stores it in data variable
 * 
 * @return void
*/
{
    std::string input_path(input_file.relative_path());
    const char *f = input_path.c_str();
    this->data = stbi_load(f, &this->w, &this->h, &this->c, 0);
    file_read = true;
}

void Data::read_file(std::filesystem::path file, int channels) 
/**
 * @brief Reads the image file and stores it in data variable
 * 
 * @return void
*/
{
    std::string input_path(file.relative_path());
    const char *f = input_path.c_str();
    this->data = stbi_load(f, &this->w, &this->h, &this->c, channels);
    file_read = true;
}

void Data::read_dir() 
/**
 * @brief Reads all images from a directory and stores it in the object's data variable
 *        representing a 3D volume.
 * 
*/

{

    std::vector<std::filesystem::path> input_files;
    for (const std::filesystem::path & input_file : std::filesystem::directory_iterator(input_file.relative_path())) {
        if (input_file.relative_path().string().find(".png") != std::string::npos) {
            input_files.push_back(input_file);
        }
        
    }
    // Sort the files into increasing order
    insertionSort(input_files);

    // Read the first file to get the x and y dimensions
    read_file(input_files[0], 1);
    int x = w;
    int y = h;
    this->num_files = input_files.size();
    
    //  x * y * c * z
    int volume_size = x * y * this->num_files;
    int image_size = x * y;

    this->size = volume_size;
    if (file_read)
        stbi_image_free(this->data); 

    this->data = (unsigned char*)stbi__malloc(volume_size);
    this->size = volume_size;

    int z = 0;
    for (const auto & input_file : input_files) {
        std::string input_path(input_file.relative_path());
        // Make sure to skip non-png files
        if (input_file.relative_path().string().find(".png") == std::string::npos) {
            continue;
        }
        const char *f = input_path.c_str();
        unsigned char *data_2d = stbi_load(f, &x, &y, &c, 1);
        std::memcpy(this->data + image_size*z, data_2d, image_size);
        stbi_image_free(data_2d); 
        // Increment z
        ++z;
    }
}

void Data::write_file(std::string file_name) {
    std::filesystem::path parent_dir (OUTPUT_DIR);
    std::filesystem::path output_dir = parent_dir / input_file.stem();
    try {
        std::filesystem::create_directories(output_dir);
    }
    catch (std::exception& err) { 
        std::cout << err.what() << std::endl;
    }
    std::string output_path(output_dir.relative_path());
    output_path += "/" + file_name + ".png";
    std::cout << "Writing image to: " << output_path << std::endl << std::endl;
    const char *f = output_path.c_str();
    stbi_write_png(f, this->w, this->h, this->c, this->data, 0);
}

void Data::write_file(unsigned char* write_data, int width, int height, int channels, std::string sub_dir, std::string file_name) {
    std::filesystem::path parent_dir (OUTPUT_DIR);
    std::filesystem::path output_dir = parent_dir.append(sub_dir);
    try {
        std::filesystem::create_directories(output_dir);
    }
    catch (std::exception& err) { 
        std::cout << err.what() << std::endl;
    }
    std::filesystem::path output_path = output_dir.append(file_name).replace_extension(".png");
    std::string output_str(output_path.relative_path());
    std::cout << "Writing image to: " << output_path.relative_path() << std::endl << std::endl;
    
    const char *f = output_str.c_str();
    stbi_write_png(f, width, height, channels, write_data, 0);
}

void Data::update(unsigned char* new_data, int new_channels, int new_size)
/**
 * @brief Updates the object 
 * 
 * @param new_data
 * @param new_channels
 * @param new_size
 * @return void
*/
{
    this->c = new_channels;

    this->size = new_size;
    if (file_read)
        stbi_image_free(this->data); 

    this->data = (unsigned char*)stbi__malloc(new_size);

    std::copy(new_data, new_data + new_size, this->data);
}

void Data::set_input_file(char* file_name)
/**
 * @brief Sets the input file of type filesystem::path to the file at file_name
 * 
 * @param file_name The path to the file we wish to set as the input_file class variable
 * @return void
*/
{
    this->input_file = (file_name);
}


void Data::insertionSort(std::vector<std::filesystem::path> &vec)
/**
 * @brief Sorts a vector of paths in increasing order using the insertion sort algorithm
 * 
 * @param vec
*/
{
    int n = vec.size();
    for (int i = 1; i < n; ++i) {
        std::string x = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > x) {
            vec[j+1] = vec[j];
            j = j - 1;
        }
        vec[j+1] = x;
    }
}