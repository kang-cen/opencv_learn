#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>

#include "quickopencv.h"

using namespace std;
using namespace cv;

int main()
{
        String str="C:\\Users\\33088\\Pictures\\Camera Roll\\smile.jpg";
        cv::Mat src=cv::imread(str);
        cv::imshow("src",src);

        QuickDemo qd;
        qd.quickopen(src);

        cv::waitKey(0);
        cv::destroyAllWindows();
        return 0;

}