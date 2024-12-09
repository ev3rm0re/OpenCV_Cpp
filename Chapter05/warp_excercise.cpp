#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
float w = 1600, h = 800;
Mat matrix, imgWarp;
int main()
{
    string path = "../images/warp.jpg";
    Mat origin = imread(path);

    Point2f src[4] = {{370, 710}, {3632, 711}, {833, 1996}, {3178, 1989}};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(origin, imgWarp, matrix, Point(w, h));

    imshow("warped", imgWarp);
    waitKey(0);
    return 0;
}