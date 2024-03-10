#ifndef _QUICKOPENCV_H_
#define _QUICKOPENCV_H_

#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

class QuickDemo
{
    public:
        cv::Mat gray,hsv;
        int colormap[20]={
        COLORMAP_AUTUMN , //!< ![autumn](pics/colormaps/colorscale_autumn.jpg)
        COLORMAP_BONE , //!< ![bone](pics/colormaps/colorscale_bone.jpg)
        COLORMAP_JET , //!< ![jet](pics/colormaps/colorscale_jet.jpg)
        COLORMAP_WINTER , //!< ![winter](pics/colormaps/colorscale_winter.jpg)
        COLORMAP_RAINBOW, //!< ![rainbow](pics/colormaps/colorscale_rainbow.jpg)
        COLORMAP_OCEAN, //!< ![ocean](pics/colormaps/colorscale_ocean.jpg)
        COLORMAP_SUMMER, //!< ![summer](pics/colormaps/colorscale_summer.jpg)
        COLORMAP_SPRING , //!< ![spring](pics/colormaps/colorscale_spring.jpg)
        COLORMAP_COOL , //!< ![cool](pics/colormaps/colorscale_cool.jpg)
        COLORMAP_HSV, //!< ![HSV](pics/colormaps/colorscale_hsv.jpg)
        COLORMAP_PINK, //!< ![pink](pics/colormaps/colorscale_pink.jpg)
        COLORMAP_HOT , //!< ![hot](pics/colormaps/colorscale_hot.jpg)
        COLORMAP_PARULA , //!< ![parula](pics/colormaps/colorscale_parula.jpg)
        COLORMAP_MAGMA , //!< ![magma](pics/colormaps/colorscale_magma.jpg)
        COLORMAP_INFERNO , //!< ![inferno](pics/colormaps/colorscale_inferno.jpg)
        COLORMAP_PLASMA , //!< ![plasma](pics/colormaps/colorscale_plasma.jpg)
        COLORMAP_VIRIDIS , //!< ![viridis](pics/colormaps/colorscale_viridis.jpg)
        COLORMAP_CIVIDIS , //!< ![cividis](pics/colormaps/colorscale_cividis.jpg)
        COLORMAP_TWILIGHT , //!< ![twilight](pics/colormaps/colorscale_twilight.jpg)
        COLORMAP_TWILIGHT_SHIFTED  //!< ![twilight shifted](pics/colormaps/colorscale_twilight_shifted.jpg)
        };
        void quickopen(cv::Mat image);
        void matcreation(cv::Mat image);
        void pixel_visit(cv::Mat& image);
        void tracking_bar(cv::Mat& image);
        void key_control(cv::Mat& image);
        void bitwise_operate(cv::Mat& image);

};
#endif