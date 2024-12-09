#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    Mat frame;
    while (cap.isOpened())
    {
        cap.read(frame);
        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }
    destroyAllWindows();
    cap.release();
    return 0;
}