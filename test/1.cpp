#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>


using namespace std;
using namespace cv;

class QuickDemo
{
    public:
        cv::Mat gray,hsv;
        void quickopen(cv::Mat image);
        
};

void QuickDemo::quickopen(cv::Mat image)
{
    cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
    cv::cvtColor(image,hsv,cv::COLOR_BGR2HSV);
    imshow("gray",gray);
    imshow("hsv",hsv);

    imwrite("C:\\Users\\33088\\Pictures\\Camera Roll\\smile_hsv.jpg",hsv);
    imwrite("C:\\Users\\33088\\Pictures\\Camera Roll\\smile_gray.jpg",gray);


}

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