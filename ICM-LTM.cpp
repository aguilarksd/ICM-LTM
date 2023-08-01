/******************************************************************************

                              ICM-LTM

*******************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat ICM-LTM(const Mat& I) {
    const int Ep = 100;
    const float W[3][3] = { { 0.5, 1, 0.5 },{ 1, 0, 1 },{ 0.5, 1, 0.5 } };
    const float f = 0.1f, g = 0.9f, h = 20.0f;

    Mat S, Yh, Fh, Th, Is, MTN;
    Mat Y, F, T, MT;

    normalize(I, S, 0.0, 1.0, NORM_MINMAX);

    Yh = Mat::zeros(I.rows, I.cols, CV_32F);
    Fh = Mat::zeros(I.rows, I.cols, CV_32F);
    Th = Mat::ones(I.rows, I.cols, CV_32F);
    Is = Mat::zeros(I.rows, I.cols, CV_8UC1);
    MT = Mat::zeros(I.rows - 2, I.cols - 2, CV_8UC1);
    MTN = Mat::zeros(I.rows - 2, I.cols - 2, CV_32F);

    int nump = MT.rows * MT.cols;
    int cont = 0;
    int imax = 0;

    for (int i = 0; i < Ep; i++) {
        F = (f * Fh) + S;
        filter2D(Yh, F, -1, Mat(3, 3, CV_32F, W), Point(-1, -1), 0, BORDER_REFLECT);

        threshold(F, Y, Th, 1, THRESH_BINARY);

        Mat MTmask = (MT < 1) & Y(Rect(1, 1, Y.cols - 2, Y.rows - 2));
        MT.setTo(i + 1, MTmask);
        cont = countNonZero(MTmask);

        T = (g * Th) + (h * Yh);

        F.copyTo(Fh);
        Y.copyTo(Yh);
        T.copyTo(Th);

        imax = i;
        if (cont == nump) {
            break;
        }
    }

    for (int m = 1; m < S.rows - 1; m++) {
        for (int n = 1; n < S.cols - 1; n++) {
            int vmt = MT.at<uchar>(m - 1, n - 1);
            MTN.at<float>(m - 1, n - 1) = (float)vmt / imax;
        }
    }

    float w = 0.1f;
    int pxmax = 0;
    int nvpx;
    while (true) {
        for (int m = 1; m < S.rows - 1; m++) {
            for (int n = 1; n < S.cols - 1; n++) {
                float px = S.at<float>(m, n);
                float vmt = MTN.at<float>(m - 1, n - 1);
                nvpx = static_cast<int>((1 - (px - (vmt * w))) * 255);
                nvpx = min(255, max(0, nvpx));
                Is.at<uchar>(m, n) = static_cast<uchar>(nvpx);
                pxmax = max(pxmax, nvpx);
            }
        }

        if (pxmax > 254) {
            break;
        }
        else {
            w += 0.05f;
        }
    }

    return Is;
}

int main()
{
    Mat I = imread("cameraman.jpg", IMREAD_GRAYSCALE); // Load your input image here
    if (I.empty()) {
        cout << "Failed to load the image!" << endl;
        return -1;
    }

    Mat lsImage = ICM-LTM(I);

    imwrite("output_image.jpg", lsImage);

    return 0;
}

