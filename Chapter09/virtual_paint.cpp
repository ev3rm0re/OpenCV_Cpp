#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<vector<int>> myColor {{50, 80, 0, 75, 149, 255}, {138, 168, 0, 179, 234, 255}};
vector<Scalar> myColorValue {{0, 255, 0}, {0, 0, 255}};
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
int area;
float peri;
Mat frame, frameHSV, mask;
vector<vector<int>> newPoints;

Point getContours(Mat imgdil, Mat img){
    
    findContours(imgdil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++)
    {
        area = contourArea(contours[i]);
        // cout << area << endl;
        if (area > 2500)
        {
            peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            // cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);

            // drawContours(img, conPoly, i, Scalar(0, 0, 255), 2);
            // rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y + boundRect[i].height / 2;
        }
    }
    return myPoint;
}

void findColor()
{
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);
    for (int i = 0; i < myColor.size(); i++)
    {
        Scalar lower(myColor[i][0], myColor[i][1], myColor[i][2]);
        Scalar upper(myColor[i][3], myColor[i][4], myColor[i][5]);
        inRange(frameHSV, lower, upper, mask);
        // imshow(to_string(i), mask);
        Point myPoint = getContours(mask, frame);
        if (myPoint.x != 0 && myPoint.y != 0)
        {
            newPoints.push_back({myPoint.x, myPoint.y, i});
        }
    }
}

void drawOnCanvas()
{
    for (int i = 0; i < newPoints.size(); i++)
    {
        circle(frame, Point(newPoints[i][0], newPoints[i][1]), 3, myColorValue[newPoints[i][2]], FILLED);
    }
}

int main()
{
    VideoCapture cap(0);

    while (cap.isOpened())
    {
        cap.read(frame);

        findColor();
        drawOnCanvas();
        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }

    destroyAllWindows();
    cap.release();
    return 0;
}