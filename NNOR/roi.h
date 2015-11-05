#pragma once
#include <opencv2/core.hpp>

namespace nnor
{
	cv::Mat selectRectangleROI(cv::Mat src, cv::Rect roi);
}