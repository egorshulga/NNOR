#include "opencv2/highgui.hpp"
#include <string>
#include <vector>

//#include "ImageProcessor/preprocess/imagePreprocess.h"
//#include "TextProcessor/preprocess/textPreprocess.h"

//#include "NN/NeuralNetwork/DataEntry.h"
//#include "NN/NeuralNetwork/DataReader.h"
//#include "NN/NeuralNetwork/NeuralNetwork.h"
//#include "NN/NeuralNetwork/NeuralNetworkTrainer.h"
//#include "ImageProcessor/ImageProcessor.h"

using namespace std;
using namespace cv;
//using namespace nnor;

string inputFile = "D:/for-work/coursework/test/lorem ipsum/simple.png";
//std::string inputFile = "D:/for-work/coursework/test/Scan_20151101 (4).png";
//std::string inputFile = "D:/for-work/coursework/test/numbers.png";

int main(int argc, char** argv)
{
//	Mat image = imread(inputFile, IMREAD_GRAYSCALE);

//	cv::Mat ROIimage = nnor::selectRectangleROI(image, cv::Rect(150, 100, 1200 - 150, 1500 - 100));
//	Mat ROIimage = image;

//	cv::Mat deskewedImage = nnor::deskew(ROIimage);
//	Mat deskewedImage = ROIimage;

//	Mat blurredImage = nnor::blur(deskewedImage, nnor::BLUR_GAUSSIAN, Size(1,1));

//	Mat binary = nnor::threshold(blurredImage, THRESH_BINARY, ADAPTIVE_THRESH_GAUSSIAN_C, 11,2);

//	Mat projectionHistogram = nnor::thresholdedProjectionHistogram(binary, VERTICAL, 3);

	
//	ImageProcessor *imageProcessor = new ImageProcessor(inputFile);

//	imageProcessor->blur();
//	auto blurred = imageProcessor->getImage();
//	imageProcessor->threshold();
//	auto thresholded = imageProcessor->getImage();









//	cv::Mat kernel = cv::Mat::ones(2, 1, CV_8UC1);			//CAN HELP IN CASE OF CHARS TORN
//	kernel = 255 * kernel;									//(maybe)
//	morphologyEx(binary, binary, cv::MORPH_OPEN, kernel);

//	vector<Mat> lines = segmentation(thresholded,VERTICAL,1,10,30);
//	vector<vector<Mat>> wordsByLines;
//	vector<vector<vector<Mat>>> charactersByWordsByLines;
//	vector<vector<Mat>> charactersByWords;
//	vector<Mat> characters;
//	for(auto line : lines)
//	{
//		auto word = segmentation(line, HORIZONTAL, 1, 15, 20);
//		wordsByLines.push_back(word);
//	}
//	for (auto wordsByLine : wordsByLines)
//	{
//		vector<vector<Mat>> charactersByLine;
//		for (auto word : wordsByLine)
//		{
//			vector<Mat> charactersByWordInLines = segmentation(word,HORIZONTAL,1,1,4);
//			charactersByLine.push_back(charactersByWordInLines);
//			charactersByWords.push_back(charactersByWordInLines);
//			characters.insert(characters.end(), charactersByWordInLines.begin(), charactersByWordInLines.end());
//			characters.push_back(Mat::ones(3, 3, CV_8U) * 255);
//		}
//		charactersByWordsByLines.push_back(charactersByLine);
//	}




//	string loremIpsum = "Lorem ipsum dolor sit amet, eu sanctus corrumpit constituto sed, cu vel sint invidunt. His ut lorem neglegentur, et congue veritus detracto mel. Ei labores facilis pro. Vero mnesarchum et sea, ius ridens scaevola no, modo tota deleniti per id. Facer numquam salutandi pro eu, appareat pertinacia ea quo. ";

//	vector<string> loremIpsumWords = nnor::split(loremIpsum, ' ');
//	vector<vector<char>> loremIpsumCharsByWords;
//	vector<char> loremIpsumChars;
//	for (auto word : loremIpsumWords)
//	{
//		loremIpsumCharsByWords.push_back(splitWord(word));
//	}
//	for (auto character : loremIpsum)
//	{
//		loremIpsumChars.push_back(character);
//	}

//	for (auto character : characters)
//	{
//		character = character;
//	}



	return 0;
//	imshow("projection", projectionHistogram);
//	cv::waitKey(0);
//	cv::destroyAllWindows();
}