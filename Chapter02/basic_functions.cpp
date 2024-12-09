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
    Mat gray, gauss, canny, dil, ero;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gauss, Size(3, 3), 5, 0);
    Canny(gauss, canny, 30, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    dilate(canny, dil, kernel);
    erode(dil, ero, kernel);

    imshow("gauss", gauss);
    imshow("canny", canny);
    imshow("dilate", dil);
    imshow("erode", ero);

    waitKey(0);
    return 0;
}