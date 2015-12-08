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
		roiImage = selectRectangleROI(currentImage, roi);
		currentImage = roiImage;
	}


	void ImageProcessor::blur(BlurFilterType filterType, Size ksize)
	{
		blurredImage = nnor::blur(currentImage, filterType, ksize);
		currentImage = blurredImage;
	}


	void ImageProcessor::rotate(double currentAngle)
	{
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
		warpAffine(currentImage, rotatedImage, rot, bbox.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
		currentImage = rotatedImage;
	}


	void ImageProcessor::rotate()
	{
		rotatedImage = deskew(currentImage);
		currentImage = rotatedImage;
	}


	void ImageProcessor::threshold(ThresholdTypes thresholdType, AdaptiveThresholdTypes adaptiveThresholdType, int blockSize, double c)
	{
		thresholdedImage = nnor::threshold(currentImage, thresholdType, adaptiveThresholdType, blockSize, c);
		currentImage = thresholdedImage;
	}


	Mat ImageProcessor::getHistogram(ProjectionType histogramType) const
	{
		return projectionHistogram(currentImage, histogramType);
	}


	void ImageProcessor::drawHistogram(ProjectionType histogramType) const
	{
		drawProjectionHistogram(currentImage, histogramType);
	}
}
