#pragma once

#include "opencv2/core.hpp"

#define PROJECTION_HORIZONTAL	0
#define PROJECTION_VERTICAL		1

namespace nnor
{
	int getProjectionSize(cv::Mat projection, int projectionType);
	int getProjectionDimension(cv::Mat projection, int projectionType);

	cv::Mat projection(cv::Mat src, int projectionType);
	cv::Mat projectionHistogram(cv::Mat src, int projectionType);

	cv::Mat thresholdedProjection(cv::Mat src, int projectionType, int threshold);
	cv::Mat thresholdedProjectionHistogram(cv::Mat src, int projectionType, int threshold);
}