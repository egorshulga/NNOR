#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

namespace nnor
{
	//http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	cv::Mat deskew(cv::Mat img);
}