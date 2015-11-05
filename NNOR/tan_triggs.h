#pragma once

#include <opencv2/core/core.hpp>

namespace nnor
{
	//http://answers.opencv.org/question/9054/color-constancy-in-different-illumination-condition/
	cv::Mat tan_triggs_preprocessing(cv::InputArray src,
		float alpha = 0.1, float tau = 10.0, float gamma = 0.2, int sigma0 = 1,
		int sigma1 = 2);
}
