/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once

#include "../filter/Filter.h"
#include "../volume/Volume.h"
#include "../data/Data.h"

/**
 * @brief Projection class which encapsulates projection methods for 3D volumes.
*/
class Projection : public Filter
{
public:

    // destructor
    ~Projection() override = default;

    static void max_intensity_projection(Volume& vol, Image& image, bool specify= false, int min_z= 0, int max_z= 0);
    static void min_intensity_projection(Volume& vol, Image& image, bool specify= false, int min_z= 0, int max_z= 0);
    static void mean_avg_intensity_projection(Volume& vol, Image& image, bool specify = false, int min_z= 0, int max_z= 0);
    static void median_avg_intensity_projection(Volume& vol, Image& image, bool specify= false, int min_z= 0, int max_z= 0);
    static int locating(int i, int j, int k, int w, int l);
protected:

private:
    
};
