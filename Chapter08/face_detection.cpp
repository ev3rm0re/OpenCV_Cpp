#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);
    Mat frame;
    CascadeClassifier faceCascade;
    faceCascade.load("../resources/haarcascade_frontalface_default.xml");

    vector<Rect> faces;

    if (!faceCascade.empty())
    {
        cout << "file loaded" << endl;
        while (cap.isOpened())
        {
            cap.read(frame);
            faceCascade.detectMultiScale(frame, faces, 1.1, 10);
            for (int i = 0; i < faces.size(); i++)
            {
                rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(0, 0, 255), 2);
            }
            imshow("frame", frame);
            if (waitKey(1) ==27)
                break;
        }
    }
    destroyAllWindows();
    cap.release();
    return 0;
}