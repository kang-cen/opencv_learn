//this is  my first project
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

void imageopen(String str)
{

    cv::Mat  image=cv::imread(str);
    //当你不适用namewindow窗口语句时，默认格式为 WINDOW_AUTOSIZE ，即窗口与图片保持一致，如果
    //图片过大，导致窗口大于屏幕尺寸，则图片不会完全显示出来。所以你需要设置成  WINDOW_FREERATIO

    if(image.empty())
    {
        cout<<"I can't load pic"<<endl;
        
    }

    cv::namedWindow("test",WINDOW_FREERATIO);//第一个参数是窗口名称
    cv::imshow("test",image);//如果不写namewindow语句会默认生成一个窗口
    waitKey(0);//0 表示一直停在这个语句 如果是1 则表示停留1ms
    destroyAllWindows();//摧毁所有的窗口
}

int main()
{
    String str="C:\\Users\\33088\\Pictures\\Screenshots\\a.png";//图片不太大
    String str_big="C:\\Users\\33088\\Pictures\\Screenshots\\b.JPG";
    imageopen(str_big);
    return 0;

}