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

cv::Mat src_bar,src1_bar;
void light_change(int b,void* userdata)
{   
    //pos 表示滑动条的当前位置，userdata 表示用户自定义数据
    // void onChange(int pos, void* userdata);
    Mat dst_bar=Mat::zeros(src_bar.size(),src_bar.type());
    Mat addorsub_src_bar=Mat::zeros(src_bar.size(),src_bar.type());
    if(b>50)
    {
        addWeighted(src_bar,1,addorsub_src_bar,0,b-50,dst_bar);
    }
    if(b<50)
    {
        addWeighted(src_bar,1,addorsub_src_bar,0,b-50,dst_bar);
    }
    if(b==50)
    {  
        dst_bar=src_bar.clone();
    }
    imshow("light_contrast modify",dst_bar);

}

void contrast_change(int b,void* userdata)
{   
    //亮度是给原图像像素都加减同一个值，而对比度 是给像素乘以或除以一个值  白的越白，黑的越黑
    //addWeighted(src1,alpha,src2,beta,gama,dst)   src1*alpha+src2*beta+gama=dst
    Mat dst_bar=Mat::zeros(src1_bar.size(),src1_bar.type());
    Mat mulordiv_src_bar=Mat::zeros(src1_bar.size(),src1_bar.type());
    double alpha=b/100.0;// 109/100=1 ; 109/100.0=1.09
    addWeighted(src1_bar,alpha,mulordiv_src_bar,0,0,dst_bar);
    imshow("light_contrast modify",dst_bar);

}

void QuickDemo::tracking_bar(cv::Mat& image)//通过滑动条，来调节图像的亮度
{
// - `trackbarname`：滑动条的名称
// - `winname`：包含滑动条的窗口名
// - `value`：初始化时滑动条的初始值指针    
// - `count`：滑动条的最大值
// - `onChange`：当滑动条的值改变时调用的回调函数
// - `userdata`：传递给回调函数的数据
    src_bar=image.clone();
    src1_bar=image.clone();
    cv::namedWindow("light_contrast modify",cv::WINDOW_FREERATIO);//如果没有这条语句 会没有滑动条
    int value=50;//亮度
    int max_value=100;
    int contrast=100;//对比度
    int max_contrast=200;
    //先用这个函数在窗口上创建一个滑动条，但是不会display图片 因为当滑动条的值未改变
    //不会运行light_change,所以需要在下面写一个light_change函数
    //当滑动条值改变时会调用light_change函数而且会 把value传给pos
    createTrackbar("light bar:", "light_contrast modify", &value, max_value,light_change);
    createTrackbar("contrast bar:", "light_contrast modify",&contrast, max_contrast,contrast_change);
    light_change(50,0);//先用这个函数初始化图片
}

void QuickDemo::key_control(cv::Mat& image)
{
    Mat dst;
    int index=0;
    while(true)
    {
        //当等待时间内无任何操作，返回-1  有字符输入时，返回字符ASCII码对应的十进制值
        //鼠标必须激活当前窗口, 即鼠标要点一下窗口，不然要是放在cmd窗口，无法键入字符
        char k=cv::waitKey(1000);//等待1s
        if(k==27)
            break;
        applyColorMap(image,dst,colormap[index%20]);
        index++;
        namedWindow("key control",WINDOW_FREERATIO);
        imshow("key control",dst);
    }
}

void QuickDemo::bitwise_operate(cv::Mat& image)
{
    cv::Mat m1,m2,dst;
    m1=Mat::zeros(Size(256,256),CV_8UC3);
    m2=Mat::zeros(Size(256,256),CV_8UC3);
//     void cv::rectangle	(	
// InputOutputArray 	img, 参数 img 输入图像。
// Rect 	rec,参数 rec 绘制矩形的规格 顶点(左上角)，宽，高
// const Scalar & 	color, 参数color 矩形颜色或亮度（灰度图像）。
// int 	thickness = 1,构成矩形的线条的厚度。负值意味着函数必须绘制一个填充矩形。
// int 	lineType = LINE_8, 参数lineType 线的类型
// int 	shift = 0 参数shift 点坐标中的小数位数
// )	
    rectangle(m1,Rect(100,100,80,80),Scalar(255,255,0),-1,0);//-1表示填充 
    rectangle(m2,Rect(150,150,80,80),Scalar(255,0,255),-1,0);
    imshow("m1",m1);
    imshow("m2",m2);
    bitwise_and(m1,m2,dst);//(255,0,0)交叉区域蓝色
    imshow("bitwise_and",dst);
    bitwise_or(m1,m2,dst);//(255,255,255)交叉区域白色 
    imshow("bitwise_or",dst);
    bitwise_not(image,dst);//取反
    namedWindow("bitwise_not",WINDOW_FREERATIO);
    imshow("bitwise_not",dst);
    bitwise_xor(m1,m2,dst);//异或（0，255，255）
    imshow("bitwise_xor",dst);

    
    

}
