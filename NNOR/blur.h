#pragma once

#include <opencv2/core.hpp>

namespace nnor
{

	enum FilterType
	{
		BLUR_NORMALIZED_BOX,
		BLUR_GAUSSIAN,
		BLUR_MEDIAN
	};

	cv::Mat blur(cv::Mat src, FilterType filterType = BLUR_GAUSSIAN, cv::Size ksize = cv::Size(5, 5));
}
