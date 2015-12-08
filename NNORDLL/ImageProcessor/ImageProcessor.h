#pragma once

#include <opencv2/core.hpp>

#include "preprocess/imagePreprocess.h"

using namespace cv;
using namespace std;

namespace nnor
{
	class ImageProcessor
	{
	private:	//Input data
		Mat defaultImage;

		Rect roi;

		int rotationAngle = 0;

		BlurFilterType filterType = BLUR_GAUSSIAN;
		Size ksize = Size(5, 5);

		ThresholdTypes thresholdType = THRESH_BINARY;
		AdaptiveThresholdTypes adaptiveThresholdType = ADAPTIVE_THRESH_GAUSSIAN_C;
		int thresholdBlockSize = 5;
		int thresholdSkew = 2;

	public:
		void setImage(Mat image);
		void setRoi(Rect roi);
		void setRotationAngle(int angle);
		void performAutomaticRotation();
		void setBlurFilterType(BlurFilterType filterType);
		void setBlurKernelSize(Size ksize);
		void setThresholdType(ThresholdTypes thresholdType);
		void setAdaptiveThresholdType(AdaptiveThresholdTypes type);
		void setThresholdBlockSize(int size);
		void setThresholdSkew(int skew);

	private:	//Output data
		Mat roiImage;
		Mat rotatedImage;
		Mat blurredImage;
		Mat thresholdedImage;

		void performRoiSelecting();
		void performRotation();
		void performBlurring();
		void performThresholding();
	public:
		Mat getRoiImage();
		Mat getRotatedImage();
		Mat getBlurredImage();
		Mat getThresholdedImage();
		
	public:		//Data and methods needed for processing
		ImageProcessor(Mat image);
		ImageProcessor(string imagePath);

//		Mat getHistogram(ProjectionType histogramType) const;
//		void drawHistogram(ProjectionType histogramType) const;

	};

}