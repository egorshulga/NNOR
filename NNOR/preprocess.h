#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


namespace nnor
{
	cv::Mat selectRectangleROI(cv::Mat src, cv::Rect roi);


	//http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	cv::Mat deskew(cv::Mat img);


	enum FilterType
	{
		BLUR_NORMALIZED_BOX,
		BLUR_GAUSSIAN,
		BLUR_MEDIAN
	};
	cv::Mat blur(cv::Mat src, FilterType filterType = BLUR_GAUSSIAN, cv::Size ksize = cv::Size(5, 5));


	cv::Mat threshold(cv::Mat src, cv::ThresholdTypes thresholdType = cv::THRESH_BINARY, cv::AdaptiveThresholdTypes adaptiveThresholdType = cv::ADAPTIVE_THRESH_GAUSSIAN_C,
		int blockSize = 5, double c = 2);


#define HORIZONTAL	0
#define VERTICAL	1
	int getSize(cv::Mat projection, int projectionType);
	int getDimension(cv::Mat projection, int projectionType);
	cv::Mat projection(cv::Mat src, int projectionType);
	cv::Mat projectionHistogram(cv::Mat src, int projectionType);
	cv::Mat thresholdedProjection(cv::Mat src, int projectionType, int threshold);
	cv::Mat thresholdedProjectionHistogram(cv::Mat src, int projectionType, int threshold);


	std::vector<cv::Mat> segmentation(cv::Mat src, int separationType, int threshold, int minSeparatorSize, int minObjectSize);
	cv::Mat autoCrop(cv::Mat src, int threshold = 0);

}
