#pragma once

#include <opencv2/core.hpp>

#include "preprocess/imagePreprocess.h"

using namespace cv;
using namespace std;

namespace nnor
{
	class ImageProcessor
	{
		Mat defaultImage;

		Mat roiImage;
		Mat rotatedImage;
		Mat blurredImage;
		Mat thresholdedImage;

		Mat currentImage;

		int previousAngle = 0;

	public:
		ImageProcessor(Mat image);
		ImageProcessor(string imagePath);

		Mat getImage() const;
		void reset();

		void setROI(Rect roi);
		void rotate(double angle);
		void rotate();
		void blur(BlurFilterType filterType = BLUR_GAUSSIAN, Size ksize = Size(5, 5));
		void threshold(ThresholdTypes thresholdType = THRESH_BINARY,
			AdaptiveThresholdTypes adaptiveThresholdType = ADAPTIVE_THRESH_GAUSSIAN_C, int blockSize = 5, double c = 2);

		Mat getHistogram(ProjectionType histogramType) const;
		void drawHistogram(ProjectionType histogramType) const;

	private:
		void reassignAllImages(Mat image);
	};

}