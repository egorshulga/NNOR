#pragma once

#include <vector>
#include <opencv2/core.hpp>

namespace nnor
{
	std::vector<cv::Mat> segmentation(cv::Mat src, int separationType, int threshold, int minSeparatorSize, int minObjectSize);

	cv::Mat autoCrop(cv::Mat src, int threshold = 0);
}