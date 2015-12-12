#include "TextImageNN.h"

namespace nnor
{
	TextImageNN::TextImageNN()
	{
		imageProcessor = new ImageProcessor();
		imageSegmenter = new ImageSegmenter();
		textProcessor = new TextProcessor();
	}

	void TextImageNN::setImage(string imagePath)
	{
		imageProcessor->setImage(imagePath);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	Mat TextImageNN::getImage()
	{
		return imageSegmenter->getImage();
	}

//	HBITMAP TextImageNN::getBitmap()
//	{
//		Mat image;
//		getImage().copyTo(image);
//		cvtColor(image, image, CV_BGRA2RGBA);
//		return CreateBitmap(image.cols, image.rows, 1, 32, image.data);
//	}

	void TextImageNN::setROI(Rect roi)
	{
		imageProcessor->setRoi(roi);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setRotationAngle(double angle)
	{
		imageProcessor->setRotationAngle(angle);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::performAutomaticRotation()
	{
		imageProcessor->performAutomaticRotation();
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setBlurFilterType(BlurFilterType filterType)
	{
		imageProcessor->setBlurFilterType(filterType);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setBlurSize(Size size)
	{
		imageProcessor->setBlurKernelSize(size);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setThresholdType(ThresholdTypes type)
	{
		imageProcessor->setThresholdType(type);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setAdaptiveThresholdType(AdaptiveThresholdTypes type)
	{
		imageProcessor->setAdaptiveThresholdType(type);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setThresholdBlockSize(int size)
	{
		imageProcessor->setThresholdBlockSize(size);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setThresholdSkew(double c)
	{
		imageProcessor->setThresholdSkew(c);
		imageSegmenter->setImage(imageProcessor->getImage());
	}

	void TextImageNN::setLinesThreshold(int threshold)
	{
		imageSegmenter->setLinesThreshold(threshold);
	}

	void TextImageNN::setLinesMinSeparatorSize(int size)
	{
		imageSegmenter->setLinesMinSeparatorSize(size);
	}

	void TextImageNN::setLinesMinObjectSize(int size)
	{
		imageSegmenter->setLinesMinObjectSize(size);
	}

	void TextImageNN::setWordsThreshold(int threshold)
	{
		imageSegmenter->setWordsThreshold(threshold);
	}

	void TextImageNN::setWordsMinSeparatorSize(int size)
	{
		imageSegmenter->setWordsMinSeparatorSize(size);
	}

	void TextImageNN::setWordsMinObjectSize(int size)
	{
		imageSegmenter->setWordsMinObjectSize(size);
	}

	void TextImageNN::setCharsThreshold(int threshold)
	{
		imageSegmenter->setCharsThreshold(threshold);
	}

	void TextImageNN::setCharsMinSeparatorSize(int size)
	{
		imageSegmenter->setCharsMinSeparatorSize(size);
	}


	void TextImageNN::setCharsMinObjectSize(int size)
	{
		imageSegmenter->setCharsMinObjectSize(size);
	}

	void TextImageNN::setText(wstring text)
	{
		textProcessor->setText(text);
	}

	wstring TextImageNN::getText()
	{
		return textProcessor->getText();
	}

	void TextImageNN::train()
	{
		vector<vector<Mat>> segmentedImage = imageSegmenter->getCharsByWords();
		vector<vector<wchar_t>> splittedChars = textProcessor->getCharsByWords();

		for (int i = 0; i < min(segmentedImage.size(), splittedChars.size()); i++)
		{
			for (int j = 0; j < min(segmentedImage[i].size(), splittedChars[i].size()); j++)
			{
				nn->trainWithPattern(toIntArray(segmentedImage[i][j]), toIntArray(splittedChars[i][j]));
			}
		}
	}

	

	void TextImageNN::recognize()
	{
		vector<vector<Mat>> segmentedImage = imageSegmenter->getCharsByWords();
		vector<wchar_t> splittedChars;

		for (int i = 0; i < segmentedImage.size(); i++)
		{
			for (int j = 0; j < segmentedImage[i].size(); j++)
			{
				auto recognitionResult = nn->feedForwardPattern(toIntArray(segmentedImage[i][j]));
				splittedChars.push_back(toWchar_t(recognitionResult));
			}
			splittedChars.push_back(L' ');
		}

		wstring result;
		for (wchar_t character : splittedChars)
		{
			result.push_back(character);
		}
		textProcessor->setText(result);
	}

	vector<int> TextImageNN::toIntArray(Mat image)
	{
		vector<int> result;
		for (int i = 0; i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				result.push_back(image.at<int>(i, j));
			}
		}
		return result;
	}

	vector<int> TextImageNN::toIntArray(wchar_t character)
	{
		vector<int> result;
		for (int i = 0; i < sizeof(wchar_t)*CHAR_BIT; i++)
		{
			result.push_back((character >> i) & 1);
		}
		return result;
	}

	wchar_t TextImageNN::toWchar_t(vector<int> array)
	{
		wchar_t result = 0;
		for (int i = 0; i < sizeof(wchar_t)*CHAR_BIT; i++)
		{
			result += array[i] << i;
		}
		return result;
	}


	void TextImageNN::resetNN(wstring nnFilepath)
	{
		delete nn;
		nn = new NN(nnFilepath);
	}

	void TextImageNN::saveNNState(wstring nnFilepath)
	{
		nn->saveWeights(nnFilepath);
	}

	void TextImageNN::resetNN()
	{
		delete nn;
		nn = new NN(imageProcessor->getImage().rows, imageProcessor->getImage().cols, HIDDENNEURONSNUMBER, OUTPUTNEURONSNUMBER);
	}
}
