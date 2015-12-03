#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

namespace nnor
{
	//Defines blurring method.
	enum BlurFilterType
	{
		BLUR_NORMALIZED_BOX,
		BLUR_GAUSSIAN,
		BLUR_MEDIAN
	};

#define HORIZONTAL	0
#define VERTICAL	1

	//Returns size of the image projection (horizontal or vertical).
	int getSize(Mat projection, int projectionType);
	//Returns dual size of the image projection (how many dots of the currentImage were used to create one dot of the projection).
	int getDimension(Mat projection, int projectionType);


	//Returns ROI object defined by a rectangle.
	Mat selectRectangleROI(Mat src, Rect roi);


	//http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	//Performs automatic image rotation.
	Mat deskew(Mat img);


	//Blurs an image with the selected filter.
	Mat blur(Mat src, BlurFilterType filterType = BLUR_GAUSSIAN, Size ksize = Size(5, 5));

	//Performs binarization with the selected method.
	Mat threshold(Mat src, ThresholdTypes thresholdType = THRESH_BINARY, AdaptiveThresholdTypes adaptiveThresholdType = ADAPTIVE_THRESH_GAUSSIAN_C,
		int blockSize = 5, double c = 2);

	//Returns a one-dimensional Mat representing image projection.
	Mat projection(Mat src, int projectionType);
	//Returns a histogram of the image projection.
	Mat projectionHistogram(Mat src, int projectionType);
	//Draws histogram just right on the image.
	void drawProjectionHistogram(Mat src, int projectionType);
	//Returns a one-dimensional Mat representing image projection with a thresholded applied.
	Mat thresholdedProjection(Mat src, int projectionType, int threshold);
	//Returns a histogram of the image projection with a threshold applied.
	Mat thresholdedProjectionHistogram(Mat src, int projectionType, int threshold);

	//Performs segmentation using projections and threshold.
	//Can perform both horizontal and vertical segmentations.
	vector<Mat> segmentation(Mat src, int separationType, int threshold, int minSeparatorSize, int minObjectSize);

	
	//Crops left, right, top, bottom sides of Mat by a threshold.
	Mat autoCrop(Mat src, int threshold = 0);
	
	
	//Performs max height and width padding of the hierarchic structured characters.
	void hierarchicCharactersPadding(vector<vector<vector<Mat>>> images);
	void charactersPadding(vector<Mat> images);
}
