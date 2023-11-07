/**
 * Group name: Tarjan
 * Authors: Eric Brine, Ligen Cai, Yujin Choi, Jinwei Hu, Yu Yan, Hao Zhou
 * Github usernames: edsml-tc2122, acse-yc2122, acse-ericbrine, edsml-yy2622, edsml-hz122, ACSE-jh4322
*/


#pragma once
#include "../filter/Filter.h"
#include "../filter/ImageFilter.h"
#include "../filter/VolumeFilter.h"
#include "../image/Image.h"
#include "../volume/Volume.h"
#include "../data/Data.h"
#include "../projection/Projection.h"

#include <iostream>

class Unittest
{
    public:
    static std::tuple<int,int>  test_adjust_brightness();
    static std::tuple<int,int>  test_to_grayscale();
    static std::tuple<int,int>  test_color_balance();
    static std::tuple<int,int>  test_edge_detection();
    static std::tuple<int,int>  test_GaussianFilter();
    static std::tuple<int,int>  test_median_filter();
    static std::tuple<int,int>  test_histogram_equalization();

    static std::tuple<int,int>  test_GaussianFilter3d(int kernelSize,double sigma);
    static std::tuple<int,int>  test_3D_median();
    static std::tuple<int,int>  test_3D_GaussianFilter();

    static void test_MIP(bool specify = false, int min_z = 0, int max_z = 0);
    static void test_MinIP(bool specify = false, int min_z = 0, int max_z = 0);
    static void test_mean_AIP(bool specify = false, int min_z = 0, int max_z = 0);
    static void test_median_AIP(bool specify = false, int min_z = 0, int max_z = 0);

    static void run_all();

    private:
    static std::tuple<int,int> test_3D(int sign=0);
    static std::tuple<int,int>  test_2D(int sign);

    int tests_passed = 0;
    int tests_failed = 0;
    int total_tests = 0;
};