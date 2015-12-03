#include "ImageProcessor.h"

#include <opencv2/imgcodecs.hpp>


namespace nnor
{
	ImageProcessor::ImageProcessor(Mat image)
	{
		image.copyTo(defaultImage);

		reassignAllImages(image);
	}

	void ImageProcessor::reassignAllImages(Mat image)
	{
		roiImage = image;
		rotatedImage = image;
		blurredImage = image;
		thresholdedImage = image;

		currentImage = image;
	}


	ImageProcessor::ImageProcessor(string imagePath) : ImageProcessor(imread(imagePath, IMREAD_GRAYSCALE))
	{ }


	void ImageProcessor::reset()
	{
		defaultImage.copyTo(currentImage);
		reassignAllImages(currentImage);
	}


	Mat ImageProcessor::getImage() const
	{
		return currentImage;
	}


	void ImageProcessor::setROI(Rect roi)
	{
		previousImage = currentImage;
		currentImage = selectRectangleROI(previousImage, roi);
	}


	void ImageProcessor::blur(BlurFilterType filterType, Size ksize)
	{
		previousImage = currentImage;
		currentImage = nnor::blur(previousImage, filterType, ksize);
	}


	void ImageProcessor::rotate(double currentAngle)
	{
		previousImage = currentImage;

		double angle = currentAngle - previousAngle;
		previousAngle = currentAngle;
		
		// get rotation matrix for rotating the image around its center
		Point2f center(currentImage.cols / 2.0, currentImage.rows / 2.0);
		Mat rot = getRotationMatrix2D(center, angle, 1.0);
		// determine bounding rectangle
		Rect bbox = RotatedRect(center, currentImage.size(), angle).boundingRect();
		// adjust transformation matrix
		rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
		warpAffine(previousImage, currentImage, rot, bbox.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
	}


	void ImageProcessor::rotate()
	{
		previousImage = currentImage;
		currentImage = deskew(defaultImage);
	}


	void ImageProcessor::threshold(ThresholdTypes thresholdType, AdaptiveThresholdTypes adaptiveThresholdType, int blockSize, double c)
	{
		previousImage = currentImage;
		currentImage = nnor::threshold(previousImage, thresholdType, adaptiveThresholdType, blockSize, c);
	}


	Mat ImageProcessor::getHistogram(int histogramType) const
	{
		return projectionHistogram(currentImage, histogramType);
	}


	void ImageProcessor::drawHistogram(int histogramType)
	{
		previousImage = currentImage;
		drawProjectionHistogram(currentImage, histogramType);
	}
}
