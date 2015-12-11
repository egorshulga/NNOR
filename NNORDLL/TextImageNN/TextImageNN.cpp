#include "TextImageNN.h"


nnor::TextImageNN::TextImageNN()
{
	imageProcessor = new ImageProcessor();

}

void nnor::TextImageNN::setImage(string imagePath)
{
	imageProcessor->setImage(imagePath);
}

Mat nnor::TextImageNN::getImage()
{
	return imageSegmenter->getImage();
}

void nnor::TextImageNN::setROI(Rect roi)
{
	imageProcessor->setRoi(roi);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setRotationAngle(double angle)
{
	imageProcessor->setRotationAngle(angle);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::performAutomaticRotation()
{
	imageProcessor->performAutomaticRotation();
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setBlurFilterType(BlurFilterType filterType)
{
	imageProcessor->setBlurFilterType(filterType);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setBlurSize(Size size)
{	
	imageProcessor->setBlurKernelSize(size);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setThresholdType(ThresholdTypes type)
{
	imageProcessor->setThresholdType(type);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setAdaptiveThresholdType(AdaptiveThresholdTypes type)
{
	imageProcessor->setAdaptiveThresholdType(type);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setThresholdBlockSize(int size)
{
	imageProcessor->setThresholdBlockSize(size);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setThresholdSkew(double c)
{
	imageProcessor->setThresholdSkew(c);
	imageSegmenter->setImage(imageProcessor->getImage());
}

void nnor::TextImageNN::setLinesThreshold(int threshold)
{
	imageSegmenter->setLinesThreshold(threshold);
}

void nnor::TextImageNN::setLinesMinSeparatorSize(int size)
{
	imageSegmenter->setLinesMinSeparatorSize(size);
}

void nnor::TextImageNN::setLinesMinObjectSize(int size)
{
	imageSegmenter->setLinesMinObjectSize(size);
}

void nnor::TextImageNN::setWordsThreshold(int threshold)
{
	imageSegmenter->setWordsThreshold(threshold);
}

void nnor::TextImageNN::setWordsMinSeparatorSize(int size)
{
	imageSegmenter->setWordsMinSeparatorSize(size);
}

void nnor::TextImageNN::setWordsMinObjectSize(int size)
{
	imageSegmenter->setWordsMinObjectSize(size);
}

void nnor::TextImageNN::setCharsThreshold(int threshold)
{
	imageSegmenter->setCharsThreshold(threshold);
}

void nnor::TextImageNN::setCharsMinSeparatorSize(int size)
{
	imageSegmenter->setCharsMinSeparatorSize(size);
}

void nnor::TextImageNN::setCharsMinObjectSize(int size)
{
	imageSegmenter->setCharsMinObjectSize(size);
}

