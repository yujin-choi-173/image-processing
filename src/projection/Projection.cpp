/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Projection.h"
#include "../data/Data.h"


int Projection::locating(int i, int j, int k, int w, int l)
{
/*
    with this function, we are able to gain the index of any pixel in memory according to its coordinates(i, j, k,
    which represent its index on x, y and z)
    w and l are the size of a single 2D slice(image).
*/
    return i + j*w + k*w*l;
}


// please note that argument specify, min_z and max_z are default and defined in VolumeFilter.h
void Projection::max_intensity_projection(Volume& vol, Image& image, bool specify, int min_z, int max_z) 
/**
 * @brief making maximum intensity projection on a volume and return 2D image
 * 
 * @param[in] vol: object of volume
 * @param[in] image: object of output image 
 * @param[in] specify: buttom allowing user to specify projecting from slab
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * 
 * @return no return value
*/
{
 /*
    We pass parameter here by reference.
    User can specifically decide to make projection for the whole volme by only passing the reference of volume,
    or to make projection for any specific slab by setting boolean value of specify to true, and passing the 
    z value of its head and tail.

    we iterate through all pixels and for any pixel in the same position regarding x and y, 
    we extract the minimum and return it to a pixel of 2D image respectfully.
 */
    int w = vol.get_x(); // get the size of volume
    int l = vol.get_y();
    int h = vol.get_z();
    int c = vol.get_channels();
    image.h = l;       // define the size of output image
    image.w = w;
    int size = w * l * c;   // get the size of output image
    int index = 0;    // the index of output image data
    unsigned char *outputImageData = new unsigned char [size]; // ready to pass the maximum value back to volume's member--outputImageData.
    if(specify == false) // by default we do projection for the whole volume
    {
        
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int idx0 = locating(i, j, 0, w, l); 
                unsigned char max= vol.data[idx0];           // preset a maximum and replace it with any one greater
                for(int k = 0;k < h; ++k)
                {
                    int idx = locating(i, j, k, w, l) * c; // locate any pixel with the same index of z
                    if(vol.data[idx] > max) 
                    {
                        max=vol.data[idx]; // whoever is bigger stays
                    }
                }
                if(c == 1)  // if channel = 2, we insert one more value
                {
                    outputImageData[j * w + i] = max;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = max;
                    outputImageData[j * w + i + 1] = vol.data[idx0+1];
                }
            }
        }
    }
    else if(specify == true)
    {
      for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int idx0 = locating(i, j, 0, w, l); 
                unsigned char max= vol.data[idx0];            // preset a maximum and replace it with any one greater
                for(int k = min_z;k < max_z; ++k)
                {
                    int idx = locating(i, j, k, w, l) * c; // locate any pixel with the same index of z
                    if(vol.data[idx] > max) max=vol.data[idx];
                }
                if(c== 1)
                {
                    outputImageData[j * w + i] = max;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = max;
                    outputImageData[j * w + i + 1] = vol.data[idx0+1];
                }
                
            }
        }
    }
    image.update(outputImageData, c, size);
    delete[] outputImageData;
}

void Projection::min_intensity_projection(Volume& vol, Image& image, bool specify, int min_z, int max_z)
/**
 * @brief making maximum intensity projection on a volume and return 2D image
 * 
 * @param[in] vol: object of volume
 * @param[in] image: object of output image 
 * @param[in] specify: buttom allowing user to specify projecting from slab
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * 
 * @return no return value
*/
{
 /*
    We pass parameter here by reference.
    User can specifically decide to make projection for the whole volme by only passing the reference of volume,
    or to make projection for any specific slab by setting boolean value of specify to true, and passing the 
    z value of its head and tail.

    we iterate through all pixels and for any pixel in the same position regarding x and y, 
    we extract the maximum and return it to a pixel of 2D image respectfully.
 */
    int w = vol.get_x(); // get the size of volume
    int l = vol.get_y();
    int h = vol.get_z();
    int c =  vol.get_channels();
    image.h = l;
    image.w = w;
    int index = 0;    // the index of output image data
    int size = w*l*c;

    unsigned char *outputImageData = new unsigned char [size]; // ready to pass the maximum value back to volume's member--outputImageData.
    if(specify == false) // by default we do projection for the whole volume
    {
        
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int idx0 = locating(i, j, 0, w, l); 
                int min= vol.data[idx0];            // preset a minimum and replace it with any one smaller
                for(int k = 0;k > h; ++k)
                {
                    int idx= locating(i, j, k, w, l) * c;   // whoever is smaller stays
                    if(vol.data[idx] < min) min=vol.data[idx];
                }
                index = i+j*w;
                outputImageData[j * w + i] = min;
            }
        }
    }
    else if(specify == true)
    {
      for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int idx0 = locating(i, j, 0, w, l); 
                int min = vol.data[idx0];               // preset a maximum and replace it with any one greater
                for(int k = min_z;k < max_z; ++k)
                {
                    int idx= locating(i, j, k, w, l) * c;
                    if(vol.data[idx] < min) min=vol.data[idx];
                }
                if(c== 1)
                {
                    outputImageData[j * w + i] = min;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = min;
                    outputImageData[j * w + i + 1] = vol.data[idx0+1];
                }
            }
        }
    }
    image.update(outputImageData, c, size);
    delete[] outputImageData;

}

void Projection::mean_avg_intensity_projection(Volume& vol, Image& image, bool specify, int min_z, int max_z)
/**
 * @brief making maximum intensity projection on a volume and return 2D image
 * 
 * @param[in] vol: object of volume
 * @param[in] image: object of output image 
 * @param[in] specify: buttom allowing user to specify projecting from slab
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * 
 * @return no return value
*/
{
 /*
    We pass parameter here by reference.
    User can specifically decide to make projection for the whole volme by only passing the reference of volume,
    or to make projection for any specific slab by setting boolean value of specify to true, and passing the 
    z value of its head and tail.

    we iterate through all pixels and for any pixel in the same position regarding x and y, accumulate all the 
    value on z-direction, and calculate the mean of them, then return it to a pixel of 2D image respectfully.
 */
    int w = vol.get_x(); // get the size of volume
    int l = vol.get_y();
    int h = vol.get_z();
    int c = vol.get_channels();
    image.h = l;
    image.w = w;
    int size = w*l*c;   // get the size of output image
    int index = 0;    // the index of output image data

    unsigned char *outputImageData = new unsigned char [size]; // ready to pass the maximum value back to volume's member--outputImageData.
    if(specify == false) // by default we do projection for the whole volume
    {
        
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int sum = 0;                // initialize sum as 0
                for(int k = 0;k > h; ++k)
                {
                    int idx= locating(i, j, k, w, l) * c; 
                    sum = sum + vol.data[idx];   // add up all pixels with the same index of z
                }
                int buffer = (int)(sum/h);
                unsigned char mean = (unsigned char) buffer;
                if(c== 1)
                {
                    outputImageData[j * w + i] = mean;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = mean;
                    outputImageData[j * w + i + 1] = vol.data[locating(i,j,0,w,l)+1];
                }
            }
        }
    }
    else if(specify == true)
    {
      for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                int sum = 0;         
                for(int k = min_z;k < max_z; ++k)
                {
                    int idx= locating(i, j, k, w, l) * c; 
                    sum = sum + vol.data[idx];
                }
                int buffer = (int)(sum/(max_z - min_z));
                unsigned char mean = (unsigned char) buffer;
                if(c== 1)
                {
                    outputImageData[j * w + i] = mean;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = mean;
                    outputImageData[j * w + i + 1] = vol.data[locating(i,j,0,w,l)+1];
                }
            }
        }
    }
    image.update(outputImageData, c, size);
    delete[] outputImageData;

}



void Projection::median_avg_intensity_projection(Volume& vol, Image& image, bool specify, int min_z, int max_z)
/**
 * @brief making maximum intensity projection on a volume and return 2D image
 * 
 * @param[in] vol: object of volume
 * @param[in] image: object of output image 
 * @param[in] specify: buttom allowing user to specify projecting from slab
 * @param[in] head position of slab
 * @param[in] tail position of slab
 * 
 * @return no return value
*/
{
 /*
    We pass parameter here by reference.
    User can specifically decide to make projection for the whole volme by only passing the reference of volume,
    or to make projection for any specific slab by setting boolean value of specify to true, and passing the 
    z value of its head and tail.

    we iterate through all pixels and for any pixel in the same position regarding x and y, accumulate all the 
    value on z-direction, and calculate the mean of them, then return it to a pixel of 2D image respectfully.
 */
    int w = vol.get_x(); // get the size of volume
    int l = vol.get_y();
    int h = vol.get_z();
    int c = vol.get_channels();
    image.h = l;
    image.w = w;
    int size = w*l*c;   // get the size of output image

    unsigned char *outputImageData = new unsigned char [size]; // ready to pass the maximum value back to volume's member--outputImageData.
    
    if(specify == false) // by default we do projection for the whole volume
    {
        
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                unsigned char median;                // initialize median
                if(h%2 == 1)
                {
                    int idx1= locating(i, j, (int)(h/2), w, l) * c;
                    int idx2= (locating(i, j, (int)(h/2), w, l) + 1) * c;
                    int buffer = (vol.data[idx1] + vol.data[idx2]) / 2;
                    median = (unsigned char) buffer;
                }
                else if(h%2 == 0)
                {
                    int idx= locating(i, j, (int)(h/2), w, l) * c;
                    median = image.data[idx];
                }
                if(c== 1)
                {
                    outputImageData[j * w + i] = median;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = median;
                    outputImageData[j * w + i + 1] = vol.data[locating(i, j, (int)(h/2), w, l)+1];
                }
            }
        }
    }
    else if(specify == true)
    {
      for(int i = 0; i < w; ++i)
        {
            for(int j = 0;j < l; ++j)
            {
                unsigned char median;                // initialize median
                if((max_z - min_z)%2 == 1)
                {
                    int idx1= locating(i, j, (int)((max_z - min_z)/2), w, l) * c;
                    int idx2= (locating(i, j, (int)((max_z - min_z)/2), w, l) + 1) * c;
                    int buffer = (vol.data[idx1] + vol.data[idx2]) / 2;
                    median = (unsigned char) buffer;
                }
                else if((max_z - min_z)%2 == 0)
                {
                    int idx= locating(i, j, (int)((max_z - min_z)/2), w, l) * c;
                    median = vol.data[idx];
                }
                if(c== 1)
                {
                    outputImageData[j * w + i] = median;
                }
                else if(c== 2)
                {
                    outputImageData[j * w + i] = median;
                    outputImageData[j * w + i + 1] = vol.data[locating(i, j, (int)((max_z - min_z)/2), w, l)+1];
                }
            }
        }
    }
    image.update(outputImageData, c, size);
    delete[] outputImageData;

}
