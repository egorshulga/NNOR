#include "watershed.h"

#include <opencv2/imgproc.hpp>

#include "threshold.h"

//it keeps throwing exceptions

cv::Mat nnor::watershed(cv::Mat src)
{
	cv::Mat binary = threshold(src);

	cv::Mat fg;
	erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 2);

	// Identify image pixels without objects
	cv::Mat bg;
	dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 3);
	threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);

	// Create markers image
	cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg;

	markers.convertTo(markers, CV_32S);
	watershed(src, markers);

	markers.convertTo(markers, CV_8U);

	return markers;
}


