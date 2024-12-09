#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
float w = 300, h = 400;
Mat matrix, imgWarp;
int main()
{
    string path = "../images/cards.jpg";
    Mat img = imread(path);

    Point2f src[4] = {{275, 80}, {645, 180}, {105, 580}, {500, 700}};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++)
    {
        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
    }

    imshow("image", img);
    imshow("warped", imgWarp);
    waitKey(0);
    return 0;
}