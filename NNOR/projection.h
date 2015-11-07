#pragma once

#include "opencv2/core.hpp"

namespace nnor
{
#define HORIZONTAL	0
#define VERTICAL	1

	int getSize(cv::Mat projection, int projectionType);
	int getDimension(cv::Mat projection, int projectionType);

	cv::Mat projection(cv::Mat src, int projectionType);
	cv::Mat projectionHistogram(cv::Mat src, int projectionType);

	cv::Mat thresholdedProjection(cv::Mat src, int projectionType, int threshold);
	cv::Mat thresholdedProjectionHistogram(cv::Mat src, int projectionType, int threshold);
}