#ifndef _QUICKOPENCV_H_
#define _QUICKOPENCV_H_
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
class QuickDemo
{
    public:
        cv::Mat gray,hsv;
        void quickopen(cv::Mat image);
        void matcreation(cv::Mat image);
        
};
#endif