#include "preprocess.h"


cv::Mat nnor::autoCrop(cv::Mat src, int threshold)
{
	cv::Mat verticalProjection = projection(src, VERTICAL);
	cv::Mat horizontalProjection = projection(src, HORIZONTAL);

	int x0, y0, x1, y1;
	for (x0 = 0; x0 < src.cols; x0++)
		if (horizontalProjection.at<int>(x0) > threshold)
			break;
	for (y0 = 0; y0 < src.rows; y0++)
		if (verticalProjection.at<int>(y0) > threshold)
			break;
	for (x1 = src.cols - 1; x1 >= 0; x1--)
		if (horizontalProjection.at<int>(x1) > threshold)
			break;
	for (y1 = src.rows - 1; y1 >= 0; y1--)
		if (verticalProjection.at<int>(y1) > threshold)
			break;

	if ((x1 - x0 <= 0) || (y1 - y0 <= 0))
		return cv::Mat();

	cv::Mat result = src(cv::Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1));
	return result;
}


void nnor::hierarchicCharactersPadding(std::vector<std::vector<std::vector<cv::Mat>>> chars)
{
	int nnRows = 0;
	int nnCols = 0;
	for (int i = 0; i < chars.size(); i++)
	{
		for (int j = 0; j < chars[i].size(); j++)
		{
			for (int k = 0; k < chars[i][j].size(); k++)
			{
				chars[i][j][k] = nnor::autoCrop(chars[i][j][k]);
				if (chars[i][j][k].rows > nnRows)
					nnRows = chars[i][j][k].rows;
				if (chars[i][j][k].cols > nnCols)
					nnCols = chars[i][j][k].cols;
			}
		}
	}

	for (int i = 0; i < chars.size(); i++)
	{
		for (int j = 0; j < chars[i].size(); j++)
		{
			for (int k = 0; k < chars[i][j].size(); k++)
			{
				cv::Mat character;
				chars[i][j][k].copyTo(character);
				int left = (nnCols - character.cols) / 2;
				int right = nnCols - left - character.cols;
				int top = (nnRows - character.rows) / 2;
				int bottom = nnRows - top - character.rows;
				copyMakeBorder(character, character, top, bottom, left, right, cv::BORDER_CONSTANT, 255);
				chars[i][j][k] = character;
			}
		}
	}
}
