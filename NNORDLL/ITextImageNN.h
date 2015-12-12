#pragma once

//This interfase is a part of dll creation.
//It is shared between a dll and programs using the dll.

#include <string>
#include <opencv2/core.hpp>
#include "ImageProcessor/preprocess/imagePreprocess.h"
using namespace std;
using namespace cv;

namespace nnor
{
	class ITextImageNN
	{
	public:
		virtual void setImage(string imagePath) = 0;
		virtual Mat getImage() = 0;
//		virtual HBITMAP getBitmap() = 0;
		virtual void setROI(Rect roi) = 0;
		virtual void setRotationAngle(double angle) = 0;
		virtual void performAutomaticRotation() = 0;
		virtual void setBlurFilterType(BlurFilterType filterType) = 0;
		virtual void setBlurSize(Size size) = 0;
		virtual void setThresholdType(ThresholdTypes type) = 0;
		virtual void setAdaptiveThresholdType(AdaptiveThresholdTypes type) = 0;
		virtual void setThresholdBlockSize(int size) = 0;
		virtual void setThresholdSkew(double c) = 0;

		virtual void setLinesThreshold(int threshold) = 0;
		virtual void setLinesMinSeparatorSize(int size) = 0;
		virtual void setLinesMinObjectSize(int size) = 0;
		virtual void setWordsThreshold(int threshold) = 0;
		virtual void setWordsMinSeparatorSize(int size) = 0;
		virtual void setWordsMinObjectSize(int size) = 0;
		virtual void setCharsThreshold(int threshold) = 0;
		virtual void setCharsMinSeparatorSize(int size) = 0;
		virtual void setCharsMinObjectSize(int size) = 0;

		virtual void setText(wstring text) = 0;
		virtual wstring getText() = 0;

		virtual void train() = 0;
		virtual void recognize() = 0;

		virtual void resetNN(wstring nnFilepath) = 0;
		virtual void saveNNState(wstring nnFilepath) = 0;
		virtual void resetNN() = 0;

		void destroy() const
		{
			delete this;
		}
	};


	typedef ITextImageNN* (__cdecl *ITextImageNNFactory)();

}