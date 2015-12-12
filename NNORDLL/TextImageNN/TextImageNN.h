#pragma once

#include <opencv2/core.hpp>

#include "../NN/NN.h"
#include "../ImageProcessor/ImageSegmenter.h"
#include "../ImageProcessor/ImageProcessor.h"
#include "../TextProcessor/TextProcessor.h"

#include "../ITextImageNN.h"

using namespace std;
using namespace cv;

namespace nnor
{
#define OUTPUTNEURONSNUMBER sizeof(wchar_t)*CHAR_BIT
#define HIDDENNEURONSNUMBER 20

	class TextImageNN : public ITextImageNN
	{
		ImageSegmenter *imageSegmenter = nullptr;
		ImageProcessor *imageProcessor = nullptr;
		TextProcessor *textProcessor = nullptr;
		NN *nn = nullptr;

	public:
		TextImageNN();

		void setImage(string imagePath) override;
		Mat getImage() override;
//		HBITMAP getBitmap() override;
		void setROI(Rect roi) override;
		void setRotationAngle(double angle) override;
		void performAutomaticRotation() override;
		void setBlurFilterType(BlurFilterType filterType) override;
		void setBlurSize(Size size) override;
		void setThresholdType(ThresholdTypes type) override;
		void setAdaptiveThresholdType(AdaptiveThresholdTypes type) override;
		void setThresholdBlockSize(int size) override;
		void setThresholdSkew(double c) override;

		void setLinesThreshold(int threshold) override;
		void setLinesMinSeparatorSize(int size) override;
		void setLinesMinObjectSize(int size) override;
		void setWordsThreshold(int threshold) override;
		void setWordsMinSeparatorSize(int size) override;
		void setWordsMinObjectSize(int size) override;
		void setCharsThreshold(int threshold) override;
		void setCharsMinSeparatorSize(int size) override;
		void setCharsMinObjectSize(int size) override;

		void setText(wstring text) override;
		wstring getText() override;

		void train() override;
		void recognize() override;

		void resetNN(wstring nnFilepath) override;
		void saveNNState(wstring nnFilepath) override;
		void resetNN() override;

	private:
		vector<int> toIntArray(Mat image);
		vector<int> toIntArray(wchar_t character);
		wchar_t toWchar_t(vector<int> array);
	};


	extern "C" __declspec(dllexport) ITextImageNN* __cdecl createInstance()
	{
		return new TextImageNN();
	}
}
