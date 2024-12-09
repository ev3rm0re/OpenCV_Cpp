#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

int main()
{
    string path = "../images/lambo.jpg";
    Mat img = imread(path), imgHSV, mask;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    namedWindow("TrackBar", (600, 200));
    createTrackbar("Hue min", "TrackBar", &hmin, 179);
    createTrackbar("Hue max", "TrackBar", &hmax, 179);
    createTrackbar("Sat min", "TrackBar", &smin, 255);
    createTrackbar("Sat max", "TrackBar", &smax, 255);
    createTrackbar("Val min", "TrackBar", &vmin, 255);
    createTrackbar("Val max", "TrackBar", &vmax, 255);

    while(true)
    {
        Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("img", img);
        imshow("imgHSV", imgHSV);
        imshow("mask", mask);
        waitKey(1);
    }
    return 0;
}