#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    string path = "../images/rain.mov";
    VideoCapture cap = VideoCapture(path);
    Mat frame;
    while (cap.isOpened())
    {
        cap.read(frame);
        imshow("frame", frame);
        waitKey(2);
    }
    return 0;
}