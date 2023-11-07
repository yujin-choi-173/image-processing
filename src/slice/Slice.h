/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/

#pragma once

#include <string>

#include "../volume/Volume.h"
#include "../data/Data.h"
#include "../image/Image.h"

/**
 * @brief Slice class which encapsulates slice methods for 3D volumes.
 */
class Slice
{
public:

    static void slice_xz(Volume& vol, Image& output_image, int y);
    static void slice_yz(Volume& vol, Image& output_image, int x);

protected:

private:
    
};
