#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace nnor
{
	cv::Mat threshold(cv::Mat src, cv::ThresholdTypes thresholdType = cv::THRESH_BINARY, cv::AdaptiveThresholdTypes adaptiveThresholdType = cv::ADAPTIVE_THRESH_GAUSSIAN_C,
		int blockSize = 5, double c = 2);


}