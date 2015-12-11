#include "ImageProcessor.h"

#include <opencv2/imgcodecs.hpp>


namespace nnor
{
	ImageProcessor::ImageProcessor(Mat image)
	{
//		image.copyTo(defaultImage);
		defaultImage = image;
	}
	
	ImageProcessor::ImageProcessor(string imagePath) : ImageProcessor(imread(imagePath, IMREAD_GRAYSCALE))
	{ }

	ImageProcessor::ImageProcessor()
	{ }

	void ImageProcessor::setImage(Mat image)
	{
		defaultImage = image;
		roi = Rect(0, 0, image.cols, image.rows);
		performRoiSelecting();
		performRotation();
		performBlurring();
		performThresholding();
	}

	void ImageProcessor::setImage(string imagePath)
	{
		setImage(imread(imagePath, IMREAD_GRAYSCALE));
	}

	void ImageProcessor::setRoi(Rect roi)
	{
		this->roi = roi;
		performRoiSelecting();
		performRotation();
		performBlurring();
		performThresholding();
	}

	void ImageProcessor::setRotationAngle(int angle)
	{
		this->rotationAngle = angle;
		performRotation();
		performBlurring();
		performThresholding();
	}

//	const int automatedRotationPerformed = -1;
	void ImageProcessor::performAutomaticRotation()
	{
//		setRotationAngle(automatedRotationPerformed);
		defaultImage = deskew(defaultImage);
		setImage(defaultImage);
	}

	void ImageProcessor::setBlurFilterType(BlurFilterType filterType)
	{
		this->filterType = filterType;
		performBlurring();
		performThresholding();
	}

	void ImageProcessor::setBlurKernelSize(Size ksize)
	{
		this->ksize = ksize;
		performBlurring();
		performThresholding();
	}

	void ImageProcessor::setThresholdType(ThresholdTypes thresholdType)
	{
		this->thresholdType = thresholdType;
		performThresholding();
	}

	void ImageProcessor::setAdaptiveThresholdType(AdaptiveThresholdTypes type)
	{
		this->adaptiveThresholdType = type;
		performThresholding();
	}

	void ImageProcessor::setThresholdBlockSize(int size)
	{
		this->thresholdBlockSize = size;
		performThresholding();
	}


	void ImageProcessor::setThresholdSkew(int skew)
	{
		this->thresholdSkew = skew;
		performThresholding();
	}

	Mat ImageProcessor::getImage()
	{
		return getThresholdedImage();
	}

	void ImageProcessor::performRoiSelecting()
	{
		roiImage = selectRectangleROI(defaultImage, roi);
	}

	void ImageProcessor::performRotation()
	{
		// get rotation matrix for rotating the image around its center
		Point2f center(roiImage.cols / 2.0, roiImage.rows / 2.0);
		Mat rot = getRotationMatrix2D(center, rotationAngle, 1.0);
		// determine bounding rectangle
		Rect bbox = RotatedRect(center, roiImage.size(), rotationAngle).boundingRect();
		// adjust transformation matrix
		rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
		warpAffine(roiImage, rotatedImage, rot, bbox.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
	}

	void ImageProcessor::performBlurring()
	{
		blurredImage = blur(rotatedImage, filterType, ksize);
	}

	void ImageProcessor::performThresholding()
	{
		thresholdedImage = threshold(blurredImage, thresholdType, adaptiveThresholdType, thresholdBlockSize, thresholdSkew);
	}

	Mat ImageProcessor::getRoiImage()
	{
		return roiImage;
	}

	Mat ImageProcessor::getRotatedImage()
	{
		return rotatedImage;
	}

	Mat ImageProcessor::getBlurredImage()
	{
		return blurredImage;
	}

	Mat ImageProcessor::getThresholdedImage()
	{
		return thresholdedImage;
	}

//	Mat ImageProcessor::getHistogram(ProjectionType histogramType) const
//	{
//		return projectionHistogram(currentImage, histogramType);
//	}


//	void ImageProcessor::drawHistogram(ProjectionType histogramType) const
//	{
//		drawProjectionHistogram(currentImage, histogramType);
//	}
}