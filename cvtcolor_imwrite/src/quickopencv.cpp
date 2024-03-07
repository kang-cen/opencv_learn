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

void QuickDemo::pixel_visit(cv::Mat& image)//实现图像的逆变换操作
{
    int row=image.rows;
    int col=image.cols;
    int cha=image.channels();
    for(int r=0;r<row;r++)
    {
        uchar* current_row=image.ptr<uchar>(r);
        for(int c=0;c<col;c++)
        {
            if(cha==1)
            {
                int pixel=*current_row;
                *current_row++=255-pixel;
            }

            if(cha==3)
            {
                //因为ch=3时 每个像素有3个值
                *current_row++=255-*current_row;//b
                *current_row++=255-*current_row;//g
                *current_row++=255-*current_row;//r
            }
        }
    }

    cv::namedWindow("changed src image",cv::WINDOW_FREERATIO);
    imshow("changed src image",image);
}

int value=50;//变量的定义与初始化
cv::Mat src_bar,addorsub_src_bar,dst_bar;//用于亮度条滑动的矩阵
void value_change(int ,void*)
{   
    if(value>50)
    {
        addorsub_src_bar=cv::Scalar(value-50,value-50,value-50);
        add(src_bar,addorsub_src_bar,dst_bar);
    }
    if(value<50)
    {
        addorsub_src_bar=cv::Scalar(50-value,50-value,50-value);
        subtract(src_bar,addorsub_src_bar,dst_bar);
    }
    if(value==50)
    {  
        dst_bar=src_bar.clone();
    }
    imshow("value modify",dst_bar);

}

void QuickDemo::tracking_bar(cv::Mat& image)//通过滑动条，来调节图像的亮度
{
// - `trackbarname`：滑动条的名称
// - `winname`：包含滑动条的窗口名
// - `value`：初始化时滑动条的初始值指针    
// - `count`：滑动条的最大值
// - `onChange`：当滑动条的值改变时调用的回调函数
// - `userdata`：传递给回调函数的数据

    cv::namedWindow("value modify",cv::WINDOW_FREERATIO);
    dst_bar=Mat::zeros(image.size(),image.type());
    addorsub_src_bar=Mat::zeros(image.size(),image.type());
    src_bar=image;//赋值，其实改变的就是image原图
    int max_value=100;
    createTrackbar("value bar:", "value modify", &value, max_value,value_change);
    //必须得写，如果不写根本就不运行。因为只有滑动时才会回调，也就是先要创建窗口才行。不然根本就不运行回调函数
    value_change(50,0);
    
    
}