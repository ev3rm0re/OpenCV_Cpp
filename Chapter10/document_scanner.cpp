#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int thresh1 = 168, thresh2 = 250;

Mat preProcessing(Mat origin)
{
    Mat gray, gauss, canny, dil;
    cvtColor(origin, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gauss, Size(3, 3), 3, 0);
    Canny(gauss, canny, thresh1, thresh2);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(canny, dil, kernel);
    return dil;
}

vector<Point> getContours(Mat dil, Mat origin)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> init_points;
    findContours(dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    int maxArea = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);

        if (area > 2500)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            if (area > maxArea && conPoly[i].size() == 4)
            {
                // drawContours(origin, conPoly, i, Scalar(255, 0, 255), 5);
                init_points = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }
        }
    }
    return init_points;
}

void drawPoints(Mat origin, vector<Point> init_points, vector<Point> newPoints)
{
    for (int i = 0; i < init_points.size(); i++)
    {
        circle(origin, init_points[i], 5, Scalar(0, 255, 0), FILLED);
        putText(origin, to_string(i), init_points[i], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 0.8);
        putText(origin, to_string(i), newPoints[i], FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 0.8);
    }
}

vector<Point> reorder(vector<Point> init_points)
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;
    
    if (init_points.size() == 0)
    {
        return init_points;
    }
    for (int i = 0; i < 4; i++)
    {
        sumPoints.push_back(init_points[i].x + init_points[i].y);
        subPoints.push_back(init_points[i].x - init_points[i].y);
    }

    newPoints.push_back(init_points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
    newPoints.push_back(init_points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1
    newPoints.push_back(init_points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2
    newPoints.push_back(init_points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3
    return newPoints;
}

Mat getWarp(Mat origin, vector<Point> points, float w, float h)
{
    Mat matrix, warp;
    if (points.size() == 0)
        return origin;
    Point2f src[4] = {points[0], points[1], points[2], points[3]};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(origin, warp, matrix, Point(w, h));
    return warp;
}

int main()
{
    float w = 420, h = 680;
    Mat origin, gray, gauss, canny, dil, warp;
    vector<Point> points, newpoints;


    namedWindow("Trackbar", (600, 300));
    createTrackbar("thresh1", "Trackbar", nullptr, 255);
    setTrackbarPos("thresh1", "Trackbar", thresh1);
    createTrackbar("thresh2", "Trackbar", nullptr, 255);
    setTrackbarPos("thresh2", "Trackbar", thresh2);
    // string path = "../images/doc.jpg";
    // origin = imread(path);
    VideoCapture cap(0);
    while (cap.isOpened())
    {
        cap.read(origin);
        // pre-processing
        dil = preProcessing(origin);
        // get contours
        points = getContours(dil, origin);
        // draw points
        newpoints = reorder(points);
        // drawPoints(origin, points, newpoints);
        // warp
        warp = getWarp(origin, newpoints, w, h);
        imshow("dil", dil);
        imshow("image", origin);
        imshow("warp", warp);
        if (waitKey(1) == 27)
            break;
    }
    return 0;
}