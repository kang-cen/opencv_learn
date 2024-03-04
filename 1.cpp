//this is  my first project
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

void imageopen(String str)
{
    cv::Mat  image=cv::imread(str);
    cv::Mat binary;
    cv::cvtColor(image,binary,COLOR_BGR2GRAY);
    cv::imshow("test",binary);
    waitKey(0);

}

int main()
{
    String str="C:\\Users\\33088\\Pictures\\Screenshots\\a.png";
    imageopen(str);
    return 0;

}