#include "segmentation.h"

#include <vector>
#include <opencv2/core.hpp>
#include "projection.h"
#include <opencv2/imgproc.hpp>

//The idea is that one can separate lines, words and characters using one algorythm.
//It only should be defined is it either vertical or horyzontal segmentation
//and three parameters:
// - segmentation threshold (how many dots in a separator can be)
// - minimal separator size 
// - minimal object size (i.e. unsatisfactory groups of rows and columns will be ignored)
//AutoCrop should be applied manually
std::vector<cv::Mat> nnor::segmentation(cv::Mat src, int separationType , int threshold, int minSeparatorSize, int minObjectSize)
{
	std::vector<cv::Mat> objects;
	int size = nnor::getSize(src, separationType);
	int dimension = nnor::getDimension(src, separationType);


	cv::Mat projection = nnor::projection(src, separationType);
//	cv::Mat projectionHist = nnor::projectionHistogram(src, separationType);		//uncomment to build histogram
//	if (separationType == VERTICAL) line(projectionHist, cv::Point(threshold, 0), cv::Point(threshold, size), cv::Scalar(127));
//	else line(projectionHist, cv::Point(0, threshold), cv::Point(size, threshold), cv::Scalar(127));

	for (int i = 0; i < size; i++)  
	{
		int objectStart = i;
		while (projection.at<int>(i) > threshold)
		{
			while ((i < size) && (projection.at<int>(i) > threshold))
				i++;
			int separatorStart = i;
			while ((i < size) && (projection.at<int>(i) <= threshold))
				i++;
			int nextObjectStart = i;

			if (nextObjectStart >= size || nextObjectStart - separatorStart >= minSeparatorSize) 
			{
				if (separatorStart - objectStart >= minObjectSize)
				{
					cv::Rect objectRect;
					if (separationType == VERTICAL) objectRect = cv::Rect(0, objectStart, dimension, separatorStart - objectStart);
					else objectRect = cv::Rect(objectStart, 0, separatorStart - objectStart, dimension);
					cv::Mat object = src(objectRect);
					objects.push_back(object);
				}
				i--;
				break;
			}
		}
	}
	return objects;
}


cv::Mat nnor::autoCrop(cv::Mat src)
{
	cv::Mat verticalProjection = projection(src, VERTICAL);
	cv::Mat horizontalProjection = projection(src, HORIZONTAL);

	int x0, y0, x1, y1;
	for (x0 = 0; x0 < src.cols; x0++)
		if (horizontalProjection.at<int>(x0) > 0)
			break;
	for (y0 = 0; y0 < src.rows; y0++)
		if (verticalProjection.at<int>(y0) > 0)
			break;
	for (x1 = src.cols - 1; x1 >= 0; x1--)
		if (horizontalProjection.at<int>(x1) > 0)
			break;
	for (y1 = src.rows - 1; y1 >= 0; y1--)
		if (verticalProjection.at<int>(y1) > 0)
			break;

	if ((x1 - x0 <= 0) || (y1 - y0 <= 0))
		return cv::Mat();

	cv::Mat result = src(cv::Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1));
	return result;
}























//std::vector<cv::Mat> nnor::linesSegmentation(cv::Mat src, int lineSegmentationThreshold, int minLineHeight)
//{
//	cv::Mat verticalProjection = projection(src, VERTICAL);
//	cv::Mat verticalProjectionHist = projectionHistogram(src, VERTICAL);		//uncomment to build histogram

//	std::vector<cv::Mat> lines;
//	int histBinsCount = verticalProjection.rows;
//	for (int i = 0; i < histBinsCount; i++)
//	{
//		if (verticalProjection.at<int>(i) > lineSegmentationThreshold)
//		{
//			int lineStart = i;
//			while ((i < histBinsCount) && (verticalProjection.at<int>(i) > lineSegmentationThreshold))
//				i++;
//			int lineEnd = i;

//			if (lineEnd - lineStart > minLineHeight)
//			{
//				auto line = src(cv::Rect(0, lineStart, src.cols, lineEnd - lineStart));
//				lines.push_back(line);
//			}
//		}
//	}

//	return lines;
//}


//std::vector<std::vector<cv::Mat>> nnor::wordsSegmentation(cv::Mat src, int lineSegmentationThreshold, int minWordHeight, int minSpaceWidth, int charSegmentationThreshold)
//{
//	std::vector<std::vector<cv::Mat>> wordsByLines;

//	std::vector<cv::Mat> lines = linesSegmentation(src, lineSegmentationThreshold, minWordHeight);

//	for (int i = 0; i < lines.size(); i++)
//	{
//		cv::Mat horizontalProjection = projection(lines[i], HORIZONTAL);
//		cv::Mat horizontalProjectionHist = projectionHistogram(lines[i], HORIZONTAL);	//uncomment to build histogram
		
//		std::vector<cv::Mat> words;

//		int lineWidth = lines[i].cols;
//		int lineHeight = lines[i].rows;

//		for (int j = 0; j < lineWidth; j++)
//		{
//			int wordStart = j;
//			while (horizontalProjection.at<int>(j) > charSegmentationThreshold)
//			{
//				while ((j < lineWidth) && (horizontalProjection.at<int>(j) > charSegmentationThreshold))
//					j++;
//				int spaceStart = j;
//				while ((j < lineWidth) && (horizontalProjection.at<int>(j) <= charSegmentationThreshold))
//					j++;
//				int nextWordStart = j;

//				if (((nextWordStart - spaceStart >= minSpaceWidth) || (nextWordStart >= lineWidth)))
//				{
//					cv::Mat word = lines[i](cv::Rect(wordStart, 0, spaceStart - wordStart, lineHeight));
//					words.push_back(word);
//					j--;
//					break;
//				}
//			}
//		}

//		wordsByLines.push_back(words);
//	}

//	return wordsByLines;
//}

//std::vector<std::vector<std::vector<cv::Mat>>> nnor::charsSegmentation(cv::Mat src, int lineSegmentationThreshold, int minWordHeight, int minSpaceWidth, int charSegmentationThreshold)
//{
//	std::vector<std::vector<std::vector<cv::Mat>>> chars;
	
//	auto wordsByLines = wordsSegmentation(src, lineSegmentationThreshold, minWordHeight, minSpaceWidth, charSegmentationThreshold);

//	for (std::vector<cv::Mat> line : wordsByLines)
//	{
//		std::vector<std::vector<cv::Mat>> charsByLines;
//		for (cv::Mat word : line)
//		{
//			std::vector<cv::Mat> charsByWords;

//			auto wordHorizontalProjection = projection(word, HORIZONTAL);
//			auto wordHorizontalProjectionHistogram = projectionHistogram(word, HORIZONTAL);	//uncomment to build histogram

//			for (int i = 0; i < word.cols; i++)
//			{
//				if (wordHorizontalProjection.at<int>(i) > charSegmentationThreshold)
//				{
//					int charStart = i;
//					while ((i < word.cols) && (wordHorizontalProjection.at<int>(i) > charSegmentationThreshold))
//						i++;
//					int charEnd = i;

//					auto character = word(cv::Rect(charStart, 0, charEnd - charStart, word.rows));
//					character = autoCrop(character);
//					charsByWords.push_back(character);
//				}
//			}

//			charsByLines.push_back(charsByWords);
//		}
//		chars.push_back(charsByLines);
//	}

//	return chars;
//}

