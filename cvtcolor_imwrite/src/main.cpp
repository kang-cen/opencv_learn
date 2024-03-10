
#include<string>

#include "quickopencv.h"

int main()
{
        
        String str="C:\\Users\\33088\\Pictures\\Camera Roll\\lvmu.jpg";
        cv::Mat src=cv::imread(str);
        // cv::namedWindow("src",cv::WINDOW_FREERATIO);
        cv::imshow("src",src);

        QuickDemo qd;
        // qd.quickopen(src);
        // qd.matcreation(src);
        // qd.pixel_visit(src);
        // qd.tracking_bar(src);
        // qd.key_control(src);
        // qd.bitwise_operate(src);
        // qd.channels_operate(src);
        qd.inRange_demo(src);
        cv::waitKey();
        // cv::destroyAllWindows();
        return 0;

}