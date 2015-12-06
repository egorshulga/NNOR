
#include "imagePreprocess.h"

#include "opencv2/imgproc.hpp"

Mat nnor::threshold(Mat src, ThresholdTypes thresholdType, AdaptiveThresholdTypes adaptiveThresholdType, int blockSize, double c)
{
	Mat binary;

	if (thresholdType & THRESH_OTSU)
		threshold(src, binary, 0, 255, thresholdType);
	else
		adaptiveThreshold(src, binary, 255, adaptiveThresholdType, thresholdType, blockSize, c);

	return binary;
}

