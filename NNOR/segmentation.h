#pragma once

#include <vector>
#include <opencv2/core.hpp>

namespace nnor
{
	std::vector<cv::Mat> linesSegmentation(cv::Mat src, int threshold = 6, int minLineHeight = 12);

	std::vector<std::vector<cv::Mat>> wordsSegmentation(cv::Mat src, int threshold = 6, int minWordHeight = 12, int minSpaceWidth = 10);

	std::vector<std::vector<std::vector<cv::Mat>>> charsSegmentation(cv::Mat src, int threshold = 6, int minWordHeight = 12, int minSpaceWidth = 10);

	cv::Mat autoCrop(cv::Mat src);
}