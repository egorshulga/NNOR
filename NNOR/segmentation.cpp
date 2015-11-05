#include "segmentation.h"

#include <vector>
#include <opencv2/core.hpp>
#include "projection.h"


std::vector<cv::Mat> nnor::linesSegmentation(cv::Mat src, int threshold, int minLineHeight)
{
	cv::Mat thresholdedVerticalProjection = thresholdedProjection(src, PROJECTION_VERTICAL, threshold);

	std::vector<cv::Mat> lines;
	int histBinsCount = thresholdedVerticalProjection.rows;
	for (int i = 0; i < histBinsCount; i++)
	{
		if (thresholdedVerticalProjection.at<int>(i) > 0)
		{
			int lineStart = i;
			while ((thresholdedVerticalProjection.at<int>(i) > 0) && (i < histBinsCount))
				i++;
			int lineEnd = i;

			if (lineEnd - lineStart > minLineHeight)
				lines.push_back(src(cv::Rect(0, lineStart, src.cols, lineEnd - lineStart)));
		}
	}

	return lines;
}


std::vector<std::vector<cv::Mat>> nnor::wordsSegmentation(cv::Mat src, int threshold, int minWordHeight, int minSpaceWidth)
{
	std::vector<std::vector<cv::Mat>> wordsByLines;

	std::vector<cv::Mat> lines = linesSegmentation(src, threshold, minWordHeight);

	for (int i = 0; i < lines.size(); i++)
	{
		cv::Mat horizontalProjection = thresholdedProjection(lines[i], PROJECTION_HORIZONTAL, threshold);
//		cv::Mat horizontalProjectionHist = thresholdedProjectionHistogram(lines[i], PROJECTION_HORIZONTAL, threshold);	//uncomment to build histogram
		
		std::vector<cv::Mat> words;

		int lineWidth = lines[i].cols;
		int lineHeight = lines[i].rows;

		for (int j = 0; j < lineWidth; j++)
		{
			int wordStart = j;
			while (horizontalProjection.at<int>(j) > 0)
			{
				while ((j < lineWidth) && (horizontalProjection.at<int>(j) > 0))
					j++;
				int spaceStart = j;
				while ((j < lineWidth) && (horizontalProjection.at<int>(j) == 0))
					j++;
				int nextWordStart = j;

				if ((nextWordStart - spaceStart >= minSpaceWidth) || (nextWordStart >= lineWidth))
				{
					words.push_back(lines[i](cv::Rect(wordStart, 0, spaceStart - wordStart, lineHeight)));
					j--;
					break;
				}
			}
		}

		wordsByLines.push_back(words);
	}

	return wordsByLines;
}

std::vector<std::vector<std::vector<cv::Mat>>> nnor::charsSegmentation(cv::Mat src, int threshold, int minWordHeight, int minSpaceWidth)
{
	std::vector<std::vector<std::vector<cv::Mat>>> chars;

	auto wordsByLines = wordsSegmentation(src, threshold, minWordHeight, minSpaceWidth);

	for (std::vector<cv::Mat> line : wordsByLines)
	{
		std::vector<std::vector<cv::Mat>> charsByLines;
		for (cv::Mat word : line)
		{
			std::vector<cv::Mat> charsByWords;

			auto wordHorizontalProjection = projection(word, PROJECTION_HORIZONTAL);
//			auto wordHorizontalProjectionHistogram = projectionHistogram(word, PROJECTION_HORIZONTAL);	//uncomment to build histogram

			for (int i = 0; i < word.cols; i++)
			{
				if (wordHorizontalProjection.at<int>(i) > 0)
				{
					int charStart = i;
					while ((i < word.cols) && (wordHorizontalProjection.at<int>(i) > 0))
						i++;
					int charEnd = i;

					auto character = word(cv::Rect(charStart, 0, charEnd - charStart, word.rows));
					autoCrop(character);
					charsByWords.push_back(character);
				}
			}

			charsByLines.push_back(charsByWords);
		}
		chars.push_back(charsByLines);
	}

	return chars;
}

cv::Mat nnor::autoCrop(cv::Mat src)
{
	cv::Mat verticalProjection = projection(src, PROJECTION_VERTICAL);
	cv::Mat horizontalProjection = projection(src, PROJECTION_HORIZONTAL);

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

	return src(cv::Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1));
}
