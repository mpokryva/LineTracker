// LineTracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat getLargestContour(Mat input) {
	Mat gray;
	cvtColor(input, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(3, 3), 0);
	threshold(gray, gray, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(gray, contours, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
	Mat drawing = Mat::zeros(gray.size(), CV_8UC3);
	vector<Vec4i> hierarchy;
	int maxIndex;
	double maxArea = 0;
	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i], false);
		if (area > maxArea) {
			maxIndex = i;
			maxArea = area;
		}
	}
	Scalar color = Scalar(255, 255, 255);
	drawContours(drawing, contours, maxIndex, color, 2, LINE_8, hierarchy, 0, Point());
	/*int morphSize = 3;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(4 * morphSize + 1, 2 * morphSize + 1),
	Point(morphSize, morphSize));
	morphologyEx(drawing, drawing, MORPH_CLOSE, element, Point(-1, -1), morphSize);*/
	return drawing;
}




int main()
{
	String winName = "Video Feed";
	namedWindow(winName, CV_WINDOW_NORMAL);
	Mat frame = imread("White_Strip.jpg");
	Mat drawing = getLargestContour(frame);
	const int MORPH_SIZE = 3;
	const int CLOSE_ITERATIONS = 3;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(4 * MORPH_SIZE + 1, 2 * MORPH_SIZE + 1),
		Point(MORPH_SIZE, MORPH_SIZE));
	morphologyEx(drawing, drawing, MORPH_CLOSE, element, Point(-1, -1), CLOSE_ITERATIONS);
	imshow(winName, drawing);
	waitKey(0);
	return 0;
}




