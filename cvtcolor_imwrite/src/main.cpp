
#include<string>

#include "quickopencv.h"

int main()
{
        
        String str="C:\\Users\\33088\\Pictures\\Camera Roll\\car.jpg";
        cv::Mat src=cv::imread(str);
        cv::namedWindow("src",cv::WINDOW_FREERATIO);
        cv::imshow("src",src);

        QuickDemo qd;
        // qd.quickopen(src);
        // qd.matcreation(src);
        // qd.pixel_visit(src);
        qd.tracking_bar(src);

        cv::waitKey(0);
        cv::destroyAllWindows();
        return 0;

}