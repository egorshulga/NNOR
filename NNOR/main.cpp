#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <vector>

#include "preprocess.h"

std::string inputFile = "D:/for-work/coursework/test/lorem ipsum/simple.png";
//std::string inputFile = "D:/for-work/coursework/test/Scan_20151101 (4).png";
//std::string inputFile = "D:/for-work/coursework/test/numbers.png";

int main(int argc, char** argv)
{
	cv::Mat image = imread(inputFile, cv::IMREAD_GRAYSCALE);

//	cv::Mat ROIimage = nnor::selectRectangleROI(image, cv::Rect(150, 100, 1200 - 150, 1500 - 100));
	cv::Mat ROIimage = image;

//	cv::Mat deskewedImage = nnor::deskew(ROIimage);
	cv::Mat deskewedImage = ROIimage;

	cv::Mat blurredImage = nnor::blur(deskewedImage, nnor::BLUR_GAUSSIAN, cv::Size(1,1));

	cv::Mat binary = nnor::threshold(blurredImage, cv::THRESH_BINARY, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 11,2);

	cv::Mat projectionHistogram = nnor::thresholdedProjectionHistogram(binary, VERTICAL, 3);

//	cv::Mat kernel = cv::Mat::ones(2, 1, CV_8UC1);			//CAN HELP IN CASE OF CHARS TORN
//	kernel = 255 * kernel;									//
//	morphologyEx(binary, binary, cv::MORPH_OPEN, kernel);

	std::vector<cv::Mat> lines = nnor::segmentation(binary,VERTICAL,1,10,30);
	std::vector<std::vector<cv::Mat>> words;
	std::vector<std::vector<std::vector<cv::Mat>>> chars;
	for(auto line : lines)
	{
		words.push_back(nnor::segmentation(line,HORIZONTAL,1,10,20));
	}
	for (auto wordsByLine : words)
	{
		std::vector<std::vector<cv::Mat>> charactersByLine;
		for (auto word : wordsByLine)
		{
			auto charactersByWord = nnor::segmentation(word,HORIZONTAL,1,2,4);
			charactersByLine.push_back(charactersByWord);
		}
		chars.push_back(charactersByLine);
	}

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






	return 0;
//	imshow("projection", projectionHistogram);
//	cv::waitKey(0);
//	cv::destroyAllWindows();
}