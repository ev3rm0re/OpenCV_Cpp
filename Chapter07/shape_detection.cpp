#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void getContours(Mat imgdil, Mat img){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgdil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    string objectType;

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        // cout << area << endl;
        if (area > 2000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            // cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);

            int objCor = (int)conPoly[i].size();
            if (objCor == 3)
            {
                objectType = "Tri";
            }
            else if (objCor == 4)
            {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                cout << aspRatio << endl;
                objectType = (aspRatio >= 0.9 && aspRatio <= 1.1) ? "Square" : "Rect";
            }
            else if (objCor > 4)
            {
                objectType = "Circle";
            }
            drawContours(img, conPoly, i, Scalar(0, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            putText(img, objectType, {boundRect[i].x, boundRect[i].y}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(255, 0, 0));
        }
    }
}

int main()
{
    string path = "../images/shapes.png";
    Mat img = imread(path), gray, gauss, canny, dil;
    // pre-processing
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gauss, Size(3, 3), 3, 0);
    Canny(gauss, canny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(canny, dil, kernel);

    getContours(dil, img);

    imshow("img", img);
    waitKey(0);
    return 0;
}