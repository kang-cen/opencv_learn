#include "quickopencv.h"

void QuickDemo::quickopen(cv::Mat image)
{
    cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
    cv::cvtColor(image,hsv,cv::COLOR_BGR2HSV);
    imshow("gray",gray);
    imshow("hsv",hsv);

    imwrite("C:\\Users\\33088\\Pictures\\Camera Roll\\smile_hsv.jpg",hsv);
    imwrite("C:\\Users\\33088\\Pictures\\Camera Roll\\smile_gray.jpg",gray);


}

void QuickDemo::matcreation(cv::Mat image)
{
    //m1,m2是通过clone or copyTo出来的 是新的Mat对象
    cv::Mat m1,m2;
    m1=image.clone();
    image.copyTo(m2);

    //zeros and ones
    cv::Mat m3=cv::Mat::zeros(Size(4,4),CV_8UC1);//CV_8UC1 8u是unsign char 8位  C1 是channels=1
    std::cout<<"m3 width "<<m3.rows<<" m3 row "<<m3.cols<<" m3 channels "<<m3.channels()<<std::endl;
    std::cout<<m3<<std::endl;

    cv::Mat m4=cv::Mat::zeros(Size(4,4),CV_8UC3);//c3 是channels=3 因为channels=3 所以每一个像素有三个值
    std::cout<<"m4 width "<<m4.rows<<" m4 row "<<m4.cols<<" m4 channels "<<m4.channels()<<std::endl;
    std::cout<<m4<<std::endl;

    cv::Mat m5=cv::Mat::ones(Size(400,400),CV_8UC3);//channels=1 时每一个像素值为1 当c=3时，只有像素值第一个通道为1
    std::cout<<"m5 width "<<m5.rows<<" m5 row "<<m5.cols<<" m5 channels "<<m5.channels()<<std::endl;
    // std::cout<<m5<<std::endl;

    m5=255;  //这个赋值操作 只会改变像素的第一个通道的值。
    // std::cout<<"after changed m5=255"<<std::endl<<m5<<std::endl;

    m5=cv::Scalar(0,255,0);  //当Size(400,400)太大了之后output会很慢 所以注释了
    // std::cout<<"after changed m5=cv::Scalar(0,255,0)"<<std::endl<<m5<<std::endl;

    std::cout<<"Of course, custom Mat types can also be displayed"<<std::endl;  //cout<<中文会乱码 奇怪
    cv::imshow("output1",m5);

    cv::Mat m6=m5;
    m6=cv::Scalar(0,0,255);
    std::cout<<"after the assignment operation and m6=cv::Scalar(0,0,255); Let's see an image of the M6"<<std::endl;
    cv::imshow("output2",m6);

    cv::Mat kernel=(Mat_<char>(3,3)<<
                    0,-1,0,
                    -1,5,-1,
                    0,1,0);
    std::cout<<kernel<<std::endl;

}


