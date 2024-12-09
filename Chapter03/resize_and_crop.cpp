#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    string path = "../images/ts.jpg";
    Mat img = imread(path);
    Mat resized, roi;

    resize(img, resized, Size(), 0.5, 0.5);
    Rect rec(200, 200, 250, 300);
    roi = img(rec);

    imshow("ts", img);
    imshow("resized", resized);
    imshow("roi", roi);

    waitKey(0);
    return 0;
}