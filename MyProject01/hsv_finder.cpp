#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main()
{
    VideoCapture cap(0);
    Mat frame, frameHSV, mask; 

    namedWindow("TrackBar", (600, 200));
    createTrackbar("Hue min", "TrackBar", &hmin, 179);
    createTrackbar("Hue max", "TrackBar", &hmax, 179);
    createTrackbar("Sat min", "TrackBar", &smin, 255);
    createTrackbar("Sat max", "TrackBar", &smax, 255);
    createTrackbar("Val min", "TrackBar", &vmin, 255);
    createTrackbar("Val max", "TrackBar", &vmax, 255);

    while(cap.isOpened())
    {
        cap.read(frame);
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);
        inRange(frameHSV, lower, upper, mask);

        imshow("mask", mask);
        waitKey(1);
    }
    return 0;
}