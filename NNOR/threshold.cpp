#include "threshold.h"

#include "opencv2/imgproc.hpp"

cv::Mat nnor::threshold(cv::Mat src, cv::ThresholdTypes thresholdType, cv::AdaptiveThresholdTypes adaptiveThresholdType,	int blockSize, double c)
{
	cv::Mat binary;

	if (thresholdType & cv::THRESH_OTSU)
		threshold(src, binary, 0, 255, thresholdType);
	else
		adaptiveThreshold(src, binary, 255, adaptiveThresholdType, thresholdType, blockSize, c);

	return binary;
}

