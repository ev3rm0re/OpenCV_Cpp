#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    int hmin = 96, smin = 156, vmin = 0;
    int hmax = 121, smax = 255, vmax = 255;

    VideoCapture cap = VideoCapture(0);
    Mat frame, frameHSV, mask, gauss, canny;
    vector<vector<Point>> contours;

    namedWindow("Trackbar", (600, 300));
    createTrackbar("Hue min", "Trackbar", &hmin, 179);
    createTrackbar("Hue max", "Trackbar", &hmax, 179);
    createTrackbar("Sat min", "Trackbar", &smin, 255);
    createTrackbar("Sat max", "Trackbar", &smax, 255);
    createTrackbar("Val min", "Trackbar", &vmin, 255);
    createTrackbar("Val max", "Trackbar", &vmax, 255);

    while (cap.isOpened())
    {
        cap.read(frame);
        Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);

        inRange(frameHSV, lower, upper, mask);
        GaussianBlur(mask, gauss, Size(3, 3), 5, 0);
        Canny(gauss, canny, 30, 150);
        findContours(canny, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            int area = contourArea(contours[i]);
            
            if (area > 100)
            {
                cout << area << endl;
                float peri = arcLength(contours[i], true);
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                boundRect[i] = boundingRect(conPoly[i]);
                rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            }
        }
        imshow("mask", mask);
        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }
    destroyAllWindows();
    cap.release();
    return 0;
}