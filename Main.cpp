#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

Mat I, S, Y, Yh, F, Fh, T, Th, Is, Ismt, MT, MTN;
float W[3][3] = { { 0.5, 1, 0.5 },{ 1, 0, 1 },{ 0.5, 1, 0.5 } };
float f = 0.1, g = 0.9, h = 20, y = 0.2;
int Ep = 10;
int nump = 0;
int cont = 0;
int imax = 0;
int Imgstate = 0;

void normalizeImage(Mat& input, Mat& output) {
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            int px = input.at<unsigned char>(y, x);
            if (px > 0) {
                float pxn = static_cast<float>(px) / 255;
                output.at<float>(y, x) = 1 - pxn;
            } else {
                output.at<float>(y, x) = 1;
            }
        }
    }
}

int main() {
    I = imread("cm.jpg", 0);
    S = Mat::zeros(I.rows, I.cols, CV_32F);
    Y = Mat::zeros(I.rows, I.cols, CV_32F);
    Yh = Mat::zeros(I.rows, I.cols, CV_32F);
    F = Mat::zeros(I.rows, I.cols, CV_32F);
    Fh = Mat::zeros(I.rows, I.cols, CV_32F);
    T = Mat::zeros(I.rows, I.cols, CV_32F);
    Th = Mat::ones(I.rows, I.cols, CV_32F);
    Is = Mat::zeros(I.rows, I.cols, CV_8UC1);
    Ismt = Mat::zeros(I.rows, I.cols, CV_8UC1);
    MT = Mat::zeros(I.rows - 2, I.cols - 2, CV_8UC1);
    MTN = Mat::zeros(I.rows - 2, I.cols - 2, CV_32F);
    
    normalizeImage(I, S);

    nump = MT.rows * MT.cols;
    cont = 0;

    for (int i = 0; i < Ep; i++) {
        // Convolution
        for (int m = 1; m < S.rows - 1; m++){
		for (int n = 1; n < S.cols - 1; n++)
		{
						//Producto punto
			float sum = 0.0;
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					float p = Yh.at<float>(m - 1 + y, n - 1 + x);
					sum = sum + p * W[y][x];
				}
			}
						//calcular F
			F.at<float>(m, n) = (f * Fh.at<float>(m, n)) + sum + S.at<float>(m, n);
				//calcular salida Y
			if (F.at<float>(m, n) > Th.at<float>(m, n))
			{
				Y.at<float>(m, n) = 1;
				int vmt = MT.at<unsigned char>(m - 1, n - 1);
					//llenar matriz de timepo
				if (vmt < 1) { MT.at<unsigned char>(m - 1, n - 1) = i + 1; cont = cont + 1; }
			}
			else
			{
				Y.at<float>(m, n) = 0;
			}
						//calcular T
			T.at<float>(m, n) = (g * Th.at<float>(m, n)) + (h * Yh.at<float>(m, n));
		}
	}
		//Actualizamos valores de Yh, Th, Fh & desnormalizamos la salida
	for (int m = 1; m < S.rows - 1; m++)
	{
		for (int n = 1; n < S.cols - 1; n++)
		{
			Fh.at<float>(m, n) = F.at<float>(m, n);
			Yh.at<float>(m, n) = Y.at<float>(m, n);
			Th.at<float>(m, n) = T.at<float>(m, n);
		}
	}
	imax = i;
	if (cont == nump) { break; }
    }

    // Normalize MT
    for (int m = 1; m < S.rows - 1; m++){
	for (int n = 1; n < S.cols - 1; n++){
       		int vmt = MT.at<unsigned char>(m - 1, n - 1);
		MTN.at<float>(m - 1, n - 1) = (float)vmt / imax;
	}		
     }

    // Image output
    float w = 0.1;
    bool cp = true;
    int pxmax = 0;
    int pxmin = 255;
    int nvpx = 0;

    while (cp) {
        for (int m = 1; m < S.rows - 1; m++)
	{
		for (int n = 1; n < S.cols - 1; n++)
		{
			float px = S.at<float>(m, n);
			float vmt = MTN.at<float>(m - 1, n - 1);
			if (Imgstate == 1){//Luminosas
				nvpx = (px - (vmt*w)) * 255;
				if (nvpx < 1) { nvpx = 0; }
				Is.at<unsigned char>(m, n) = nvpx;
				if (pxmin > nvpx) { pxmin = nvpx; }
			}
			if (Imgstate == 0){ // oscuras
				nvpx = (1 - (px - (vmt*w))) * 255;
				if (nvpx > 254) { nvpx = 255; }
				Is.at<unsigned char>(m, n) = nvpx;
				if (pxmax < nvpx) { pxmax = nvpx; }
                        }
		}
	}
	if (pxmax > 254) { break; }
	else { w = w + 0.05; }
    }
    imwrite("output.jpg", Is);

    return 0;
}