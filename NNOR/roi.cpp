#include "preprocess.h"

cv::Mat nnor::selectRectangleROI(cv::Mat src, cv::Rect roi)
{
	cv::Mat roiImage = src(roi);
	return roiImage;
}