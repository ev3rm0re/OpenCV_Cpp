#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

    circle(img, Point(256, 256), 100, Scalar(0, 0, 0), FILLED);

    // rectangle(img, Rect(256, 256, 200, 100), Scalar(0, 0, 255), FILLED);
    rectangle(img, Point(256, 256), Point(456, 356), Scalar(0, 0, 255), FILLED);
    line(img, Point(100, 100), Point(200, 200), Scalar(255, 0, 0), 5);
    putText(img, "ev3rm0re", Point(150, 200), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 1);

    imshow("img" , img);

    waitKey(0);
    return 0;
}