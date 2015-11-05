#include "opencv2/highgui/highgui.hpp"
#include <string>

#include "deskew.h"
#include "threshold.h"
#include "projection.h"
#include "blur.h"
#include "roi.h"
#include "segmentation.h"

//std::string inputFile = "D:/for-work/coursework/test/lorem ipsum/m20.jpg";
std::string inputFile = "D:/for-work/coursework/test/Scan_20151101 (3).png";
//std::string inputFile = "D:/for-work/coursework/test/numbers.png";

int main(int argc, char** argv)
{
	cv::Mat image = imread(inputFile, cv::IMREAD_GRAYSCALE);

	cv::Mat ROIimage = nnor::selectRectangleROI(image, cv::Rect(100,100,1020,1300));

	cv::Mat deskewedImage = nnor::deskew(ROIimage);
//	cv::Mat deskewedImage = ROIimage;

	cv::Mat blurredImage = nnor::blur(deskewedImage, nnor::BLUR_GAUSSIAN, cv::Size(11,11));

	cv::Mat binary = nnor::threshold(blurredImage, cv::THRESH_BINARY, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 7, 5);

	cv::Mat projectionHistogram = nnor::thresholdedProjectionHistogram(binary, PROJECTION_VERTICAL, 3);

	auto chars = nnor::charsSegmentation(binary, 4, 12, 10);

	return 0;
//	imshow("projection", projectionHistogram);
//	cv::waitKey(0);
//	cv::destroyAllWindows();
}