
#include<string>

#include "quickopencv.h"

int main()
{
        
        String str="C:\\Users\\33088\\Pictures\\Camera Roll\\meimei.jpg";
        cv::Mat src=cv::imread(str);
        // cv::namedWindow("src",cv::WINDOW_FREERATIO);
        // cv::imshow("src",src);

        QuickDemo qd;
        // qd.quickopen(src);
        // qd.matcreation(src);
        // qd.pixel_visit(src);
        // qd.tracking_bar(src);
        // qd.key_control(src);
        // qd.bitwise_operate(src);
        // qd.channels_operate(src);
        // qd.inRange_demo(src);
        // qd.pixel_static(src);
        // qd.geometry_draw(src);
        // qd.random_draw();
        // qd.draw_polygon();
        qd.mouse_drawing(src);
        cv::waitKey();
        system("pause");
        // cv::destroyAllWindows();
        return 0;

}