#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <vector>

#include "deskew.h"
#include "threshold.h"
#include "projection.h"
#include "blur.h"
#include "roi.h"
#include "segmentation.h"

//std::string inputFile = "D:/for-work/coursework/test/lorem ipsum/m20.jpg";
std::string inputFile = "D:/for-work/coursework/test/Scan_20151101 (4).png";
//std::string inputFile = "D:/for-work/coursework/test/numbers.png";

int main(int argc, char** argv)
{
	cv::Mat image = imread(inputFile, cv::IMREAD_GRAYSCALE);

	cv::Mat ROIimage = nnor::selectRectangleROI(image, cv::Rect(150, 100, 1200 - 150, 1500 - 100));

//	cv::Mat deskewedImage = nnor::deskew(ROIimage);
	cv::Mat deskewedImage = ROIimage;

	cv::Mat blurredImage = nnor::blur(deskewedImage, nnor::BLUR_GAUSSIAN, cv::Size(11,11));

	cv::Mat binary = nnor::threshold(blurredImage, cv::THRESH_BINARY, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 7, 2);

	cv::Mat projectionHistogram = nnor::thresholdedProjectionHistogram(binary, VERTICAL, 3);

//	cv::Mat kernel = cv::Mat::ones(2, 1, CV_8UC1);			//CAN HELP IN CASE OF CHARS TORN
//	kernel = 255 * kernel;									//
//	morphologyEx(binary, binary, cv::MORPH_OPEN, kernel);

	std::vector<cv::Mat> lines = nnor::segmentation(binary, VERTICAL,17,8,20);
	std::vector<std::vector<cv::Mat>> words;
	std::vector<std::vector<std::vector<cv::Mat>>> chars;
	for(auto line : lines)
	{
		words.push_back(nnor::segmentation(line, HORIZONTAL, 5, 13, 15));
	}
	for (auto wordsByLine : words)
	{
		std::vector<std::vector<cv::Mat>> charactersByLine;
		for (auto word : wordsByLine)
		{
			auto charactersByWord = nnor::segmentation(word, HORIZONTAL,2,2,10);
			charactersByLine.push_back(charactersByWord);
		}
		chars.push_back(charactersByLine);
	}

	return 0;
//	imshow("projection", projectionHistogram);
//	cv::waitKey(0);
//	cv::destroyAllWindows();
}