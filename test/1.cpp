#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


class QuickDemo
{
    public:
        void tracking_bar(cv::Mat& image);
};

// cv::Mat src,src1;

static void on_lightness(int pos, void* userdata) {
    Mat image = (*(Mat*)userdata);
    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    addWeighted(image, 1.0, m, 0, pos, dst);
    imshow("light_contrast", dst);
}

static void on_contrast(int pos, void* userdata) {
    Mat image = (*(Mat*)userdata);
    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    double contrast = pos / 100.0;
    addWeighted(image, contrast, m, 0.0, 0, dst);
    imshow("light_contrast", dst);
}

void QuickDemo::tracking_bar(cv::Mat& image)
{
     Mat src=image.clone();
     Mat src1=src.clone();
    namedWindow("light_contrast", WINDOW_FREERATIO);
    int lightness = 50;
    int max_value = 100;
    int contrast_value = 100;
    createTrackbar("Value Bar:", "light_contrast", &lightness, max_value, on_lightness,((void*)&src));
    createTrackbar("Contrast Bar:", "light_contrast", &contrast_value, 200, on_contrast,((void*)&src1));
    // on_lightness(50,(void*)&src);
}

int main() {
    Mat image = imread("C:\\Users\\33088\\Pictures\\Camera Roll\\car.jpg"); //  B, G, R
    if (image.empty()) {
        printf("could not load image....\n");
        return -1;
    }
    namedWindow("src", WINDOW_FREERATIO);
    imshow("src", image);
    QuickDemo QD;
    QD.tracking_bar(image);
    waitKey(0);
    cv::destroyAllWindows();
    return 0;
}