#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // {红, 绿, 黄}
    vector<int> hmin = {0, 50, 26}, smin = {123, 116, 238}, vmin = {255, 255, 255};
    vector<int> hmax = {11, 90, 47}, smax = {255, 227, 255}, vmax = {255, 255, 255};
    vector<string> light = {"red", "green", "yellow"};
    vector<Scalar> light_color = {(0, 0, 255), (0, 255, 0), (0, 255, 255)};
    int flag;
    VideoCapture cap = VideoCapture(0);
    Mat frame, frameHSV, mask, gauss, canny, dil;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    float peri, area;

    while (cap.isOpened())
    {
        cap.read(frame);
        flag = 0;
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        for (int i = 0; i < 3; i++)
        {
            Scalar lower(hmin[i], smin[i], vmin[i]), upper(hmax[i], smax[i], vmax[i]);
            inRange(frameHSV, lower, upper, mask);
            GaussianBlur(mask, gauss, Size(3, 3), 3, 0);
            Canny(gauss, canny, 25, 125);
            Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
            dilate(canny, dil, kernel);
            findContours(dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            vector<vector<Point>> conPoly(contours.size());
            vector<Rect> boundRect(contours.size());

            for (int j = 0; j < contours.size(); j++)
            {
                area = contourArea(contours[j]);
                cout << area << endl;
                if (area > 500)
                {
                    peri = arcLength(contours[j], true);
                    approxPolyDP(contours[j], conPoly[j], 0.02 * peri, true);
                    boundRect[j] = boundingRect(conPoly[j]);
                    if ((int)conPoly[j].size() > 8)
                    {
                        rectangle(frame, boundRect[j].tl(), boundRect[j].br(), Scalar(0, 255, 0), 3);
                        putText(frame, light[i], {boundRect[j].x, boundRect[j].y}, FONT_HERSHEY_DUPLEX, 1, light_color[i]);
                        flag = 1;
                    }
                }
            }
            if (flag)
                break;
        }
        drawContours(frame, contours, -1, Scalar(0, 255, 0), 2);
        imshow("dil", dil);
        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }
    destroyAllWindows();
    cap.release();
    return 0;
}