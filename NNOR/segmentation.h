#pragma once

#include <vector>
#include <opencv2/core.hpp>

namespace nnor
{
#define LINESTHRESHOLD			3
#define MINLINESEPARATORHEIGHT	4
#define MINLINEHEIGHT			12

#define WORDSTHRESHOLD			3
#define MINWORDSSEPARATORWIDTH	10
#define MINWORDLENGTH			5	//it is unnecessary 'cause it would be checked at chars segmentation

#define CHARSTHRESHOLD			WORDSTHRESHOLD
#define MINCHARSSEPARATORWIDTH	3
#define MINCHARLENGTH			5

	std::vector<cv::Mat> segmentation(cv::Mat src, int separationType, int threshold, int minSeparatorSize, int minObjectSize);

	cv::Mat autoCrop(cv::Mat src);





//#define dotsInARowToBeALine	3
//#define minHeight			12
//#define spaceWidth			10
//#define charSegmentationThresh	1
//#define charSpacing			2

//	std::vector<cv::Mat> linesSegmentation(cv::Mat src, int lineSegmentationThreshold = dotsInARowToBeALine, int minLineHeight = minHeight);

//	std::vector<std::vector<cv::Mat>> wordsSegmentation(cv::Mat src, int lineSegmentationThreshold = dotsInARowToBeALine, int minWordHeight = minHeight, int minSpaceWidth = spaceWidth, int charSegmentationThreshold = charSegmentationThresh);

//	std::vector<std::vector<std::vector<cv::Mat>>> charsSegmentation(cv::Mat src, int lineSegmentationThreshold = dotsInARowToBeALine, int minWordHeight = minHeight, int minSpaceWidth = spaceWidth, int charSegmentationThreshold = charSegmentationThresh);

}