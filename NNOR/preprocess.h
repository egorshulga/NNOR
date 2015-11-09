#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


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
	int getSize(cv::Mat projection, int projectionType);
	//Returns dual size of the image projection (how many dots of the image were used to create one dot of the projection).
	int getDimension(cv::Mat projection, int projectionType);


	//Returns ROI object defined by a rectangle.
	cv::Mat selectRectangleROI(cv::Mat src, cv::Rect roi);


	//http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	//Performs automatic image rotation.
	cv::Mat deskew(cv::Mat img);


	//Blurs an image with the selected filter.
	cv::Mat blur(cv::Mat src, BlurFilterType filterType = BLUR_GAUSSIAN, cv::Size ksize = cv::Size(5, 5));

	//Performs binarization with the selected method.
	cv::Mat threshold(cv::Mat src, cv::ThresholdTypes thresholdType = cv::THRESH_BINARY, cv::AdaptiveThresholdTypes adaptiveThresholdType = cv::ADAPTIVE_THRESH_GAUSSIAN_C,
		int blockSize = 5, double c = 2);

	//Returns a one-dimensional Mat representing image projection.
	cv::Mat projection(cv::Mat src, int projectionType);
	//Returns a histogram of the image projection.
	cv::Mat projectionHistogram(cv::Mat src, int projectionType);
	//Returns a one-dimensional Mat representing image projection with a thresholded applied.
	cv::Mat thresholdedProjection(cv::Mat src, int projectionType, int threshold);
	//Returns a histogram of the image projection with a threshold applied.
	cv::Mat thresholdedProjectionHistogram(cv::Mat src, int projectionType, int threshold);

	//Performs segmentation using projections and threshold.
	//Can perform both horizontal and vertical segmentations.
	std::vector<cv::Mat> segmentation(cv::Mat src, int separationType, int threshold, int minSeparatorSize, int minObjectSize);

	
	//Crops left, right, top, bottom sides of Mat by a threshold.
	cv::Mat autoCrop(cv::Mat src, int threshold = 0);
	
	
	//Performs max height and width padding of the hierarchic structured characters.
	void nnor::hierarchicCharactersPadding(std::vector<std::vector<std::vector<cv::Mat>>> images);
}
