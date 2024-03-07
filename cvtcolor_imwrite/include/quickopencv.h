#ifndef _QUICKOPENCV_H_
#define _QUICKOPENCV_H_

#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

extern int value;
extern cv::Mat src_bar,addorsubjidan_src_bar,dst_bar;
class QuickDemo
{
    public:
        cv::Mat gray,hsv;
        void quickopen(cv::Mat image);
        void matcreation(cv::Mat image);
        void pixel_visit(cv::Mat& image);
        void tracking_bar(cv::Mat& image);
};
#endif