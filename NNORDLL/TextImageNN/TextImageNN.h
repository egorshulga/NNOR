#pragma once

#include <opencv2/core.hpp>

#include "../NN/NN.h"
#include "../ImageProcessor/ImageSegmenter.h"
#include "../ImageProcessor/ImageProcessor.h"
#include "../TextProcessor/TextProcessor.h"

using namespace std;
using namespace cv;

namespace nnor
{
	class TextImageNN
	{
		ImageSegmenter *imageSegmenter = nullptr;
		ImageProcessor *imageProcessor = nullptr;
		TextProcessor *textProcessor = nullptr;
		NN *nn = nullptr;

	public:
		TextImageNN();

		void setImage(string imagePath);
		Mat getImage();
		void setROI(Rect roi);
		void setRotationAngle(double angle);
		void performAutomaticRotation();
		void setBlurFilterType(BlurFilterType filterType);
		void setBlurSize(Size size);
		void setThresholdType(ThresholdTypes type);
		void setAdaptiveThresholdType(AdaptiveThresholdTypes type);
		void setThresholdBlockSize(int size);
		void setThresholdSkew(double c);

		void setLinesThreshold(int threshold);
		void setLinesMinSeparatorSize(int size);
		void setLinesMinObjectSize(int size);
		void setWordsThreshold(int threshold);
		void setWordsMinSeparatorSize(int size);
		void setWordsMinObjectSize(int size);
		void setCharsThreshold(int threshold);
		void setCharsMinSeparatorSize(int size);
		void setCharsMinObjectSize(int size);

//		wstring getRecognizedText();
//		void setText(wstring text);

//		void train();
//		void recognize();

	private:
//		int* toIntArray(Mat image);
//		int* toIntArray(wstring text);
//		Mat toMat(int* array);
//		wstring toWstring(int* array);
	};
}