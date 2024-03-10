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

void QuickDemo::channels_operate(cv::Mat& image)
{
    std::vector<Mat> single;//建立一个能够存放Mat类型的数组
    Mat dst;
    split(image,single);
    cv::namedWindow("blue",cv::WINDOW_FREERATIO);
    cv::namedWindow("green",cv::WINDOW_FREERATIO);
    cv::namedWindow("red",cv::WINDOW_FREERATIO);
    cv::namedWindow("blue after merge",cv::WINDOW_FREERATIO);
    cv::namedWindow("channels changed",cv::WINDOW_FREERATIO);

    imshow("blue",single[0]);
    imshow("green",single[1]);
    imshow("red",single[2]);
//以三通道形式显示单通道内容  蓝色
    single[1]=0;
    single[2]=0;
    cv::merge(single,dst);
    imshow("blue after merge",dst);
//通道改变
    int from_to[]={0,2,1,1,2,0};
    //void cv::mixChannels(const Mat* src, int nsrcs, Mat* dst, int ndsts, const int* fromTo, int npairs)
    cv::mixChannels(&image,1,&dst,1,from_to,3);
    cv::imwrite("C:\\Users\\33088\\Pictures\\Camera Roll\\flower_RGB.jpg",dst);
    imshow("channels changed",dst);

}

void QuickDemo::inRange_demo(cv::Mat& image)
{
    //实现背景抠图
    cvtColor(image,hsv,COLOR_BGR2HSV);
    cv::Mat masked=Mat::zeros(image.size(),image.type());
/*
void cv::inRange(cv::InputArray src, cv::InputArray lowerb, 
cv::InputArray upperb, cv::OutputArray dst)
用于根据指定的上限和下限阈值对输入图像的像素值进行范围筛选，生成一个二值化图像。
- `src` 是输入图像。
- `lowerb` 是包含低阈值的数组或标量。如果输入图像中的像素值大于等于 `lowerb`，则被认为是目标像素。
`upperb` 是包含高阈值的数组或标量。如果输入图像中的像素值小于 `upperb`，则被认为是目标像素。
- `dst` 是输出的二值化图像，与输入图像具有相同的尺寸与类型。
*/
    std::cout<<"reference table"<<std::endl;
    Mat rt=imread("C:\\Users\\33088\\Pictures\\Camera Roll\\reference.jpg");
    imshow("reference table",rt);
    inRange(hsv,Scalar(35,43,46),Scalar(77,255,255),masked);//从hsv中提取区域 白色为目标区域 黑色为背景
    imshow("masked",masked);
    bitwise_not(masked,masked);//提取物体/人物
    Mat bg=Mat::zeros(image.size(),image.type());
    bg=Scalar(40,40,250);
    image.copyTo(bg,masked);//ROI区域是人脸部分  将image图像拷贝到bg的masked区域，其余区域不变
    imshow("bg changed",bg);

}

void QuickDemo::pixel_static(cv::Mat& image)
{
    /*
    cv::minMaxLoc()`函数用于查找矩阵中的最小值和最大值，以及它们对应的位置（索引）
    void cv::minMaxLoc(const cv::Mat& src, double* minVal, double* maxVal=0, cv::Point* minLoc=0, 
    cv::Point* maxLoc=0, const cv::Mat& mask=cv::Mat())
        `src`：输入的  单通道矩阵 （例如灰度图像）
        - `minVal`：指向输出的最小值的指针（可选参数）
        - `maxVal`：指向输出的最大值的指针（可选参数）
        - `minLoc`：指向输出的最小值位置的指针（可选参数）
        - `maxLoc`：指向输出的最大值位置的指针（可选参数）
        - `mask`：可选参数，用于指定要考虑的非零掩码区域（默认为一个空矩阵） 


    void cv::meanStdDev(cv::InputArray src, cv::OutputArray mean, cv::OutputArray stddev,
     cv::InputArray mask = noArray()) 计算均值和标准差

    OutputArray 是 OpenCV 中定义的一个类，用于表示输出数据的容器。它可以用来表示用于接收函数输出数据
    的数组或矩阵。`OutputArray` 类型可以接受不同类型的数据结构，如 `cv::Mat`, `cv::UMat`, `cv::GpuMat` 等

    `OutputArray` 可以通过 `at` 方法来访问输出数据。
    */

   double min_value,max_value;
   cv::Mat mean_value,std_value;
   Point min_loc,max_loc;
   std::vector<Mat> mv;//用于接收单通道
   split(image,mv);
   for(int i=0;i<3;i++)
   {
    minMaxLoc(mv[i],&min_value,&max_value,&min_loc,&max_loc);
    // meanStdDev(mv[i],mean_value,std_value);  可以单个通道操作，也可以一起操作
    std::cout<<"mv["<<i<<"]"<<"min_value:"<<min_value<<std::endl;
    std::cout<<"mv["<<i<<"]"<<"max_value:"<<max_value<<std::endl;
    std::cout<<"mv["<<i<<"]"<<"min_loc:"<<min_loc<<std::endl;
    std::cout<<"mv["<<i<<"]"<<"max_loc:"<<min_loc<<std::endl;
    std::cout<<std::endl;
   }
    meanStdDev(image,mean_value,std_value);//标准差越小，图像的有效信息越少，如果方差很小的话，可能是什么噪声
    std::cout<<"channnel 1   "<<"mean_value:"<<mean_value.at<double>(0,0)<<"  sta_value:"<<std_value.at<double>(0,0)<<endl;
    std::cout<<"channnel 2   "<<"mean_value:"<<mean_value.at<double>(1,0)<<"  sta_value:"<<std_value.at<double>(1,0)<<endl;
    std::cout<<"channnel 3   "<<"mean_value:"<<mean_value.at<double>(2,0)<<"  sta_value:"<<std_value.at<double>(2,0)<<endl;
    std::cout<<"mean_value:"<<mean_value<<endl<<"sta_value"<<std_value<<endl; // 这样是输出一个矩阵

}