/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once

#include <iostream>
#include <filesystem>

// template <class T>
class Data
{
public:
    // default constructor - should we have it?
    Data();
    // constructor
    Data(char* file_name);
    Data(char* file_name, bool is_dir);
    Data(unsigned char* data, int w, int h, int c, char* name);
    Data(unsigned char* data, int w, int h, int c, int num_files, char* name);
    Data(Data &data);
    Data(Data &&data);

    // destructor
    virtual ~Data();

    // Make sure to handle error if stbi_load fails
    void read_dir();
    void read_file();
    void read_file(std::filesystem::path file, int channels);

    void write_file();
    void write_file(std::string sub_dir);
    static void write_file(unsigned char* write_data, int width, int height, int channels, std::string sub_dir, std::string file_name);
    
    int get_size() const;

    void set_input_file(char* file_name);

    void update(unsigned char* data, int channels, int size);

    char* file_name;
    std::filesystem::path input_file;
    unsigned char* data;
    int w, h, c;
    int size;
    int num_files;
    
    bool file_read = false;
    bool is_dir = false;


protected:

private:

    void insertionSort(std::vector<std::filesystem::path> &vec);

};