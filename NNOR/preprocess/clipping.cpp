#include "imagePreprocess.h"


Mat nnor::autoCrop(Mat src, int threshold)
{
	Mat verticalProjection = projection(src, VERTICAL);
	Mat horizontalProjection = projection(src, HORIZONTAL);

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
		return Mat();

	Mat result = src(Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1));
	return result;
}


void nnor::hierarchicCharactersPadding(vector<vector<vector<Mat>>> chars)
{
	int nnRows = 0;
	int nnCols = 0;
	for (int i = 0; i < chars.size(); i++)
	{
		for (int j = 0; j < chars[i].size(); j++)
		{
			for (int k = 0; k < chars[i][j].size(); k++)
			{
				chars[i][j][k] = autoCrop(chars[i][j][k]);
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
				Mat character;
				chars[i][j][k].copyTo(character);
				int left = (nnCols - character.cols) / 2;
				int right = nnCols - left - character.cols;
				int top = (nnRows - character.rows) / 2;
				int bottom = nnRows - top - character.rows;
				copyMakeBorder(character, character, top, bottom, left, right, BORDER_CONSTANT, 255);
				chars[i][j][k] = character;
			}
		}
	}
}


void nnor::charactersPadding(vector<Mat> chars)
{
	int nnRows = 0;
	int nnCols = 0;
	for (int i = 0; i < chars.size(); i++)
	{
		chars[i] = autoCrop(chars[i]);
		if (chars[i].rows > nnRows)
			nnRows = chars[i].rows;
		if (chars[i].cols > nnCols)
			nnCols = chars[i].cols;
	}

}