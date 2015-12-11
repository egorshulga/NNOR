///////////////////////////////////////////////////////////
//  ImageSegmenter.cpp
//  Implementation of the Class ImageSegmenter
//  Created on:      07-Dec-2015 09:52:44
//  Original author: egors
///////////////////////////////////////////////////////////

#include "ImageSegmenter.h"

namespace nnor
{

	ImageSegmenter::ImageSegmenter()
	{ }
	

	ImageSegmenter::ImageSegmenter(Mat image)
	{
		this->image = image;
	}


	void ImageSegmenter::setImage(Mat image)
	{
		this->image = image;
		performSegmentation();
	}

	void ImageSegmenter::setLinesThreshold(int threshold)
	{
		linesThreshold = threshold;
		performLinesSegmentation();
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setLinesMinSeparatorSize(int size)
	{
		linesMinSeparatorSize = size;
		performLinesSegmentation();
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setLinesMinObjectSize(int size)
	{
		linesMinObjectSize = size;
		performLinesSegmentation();
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setWordsThreshold(int threshold)
	{
		wordsThreshold = threshold;
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setWordsMinSeparatorSize(int size)
	{
		wordsMinSeparatorSize = size;
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setWordsMinObjectSize(int size)
	{
		wordsMinObjectSize = size;
		performWordsSegmentation();
		performCharsSegmentation();
	}

	void ImageSegmenter::setCharsThreshold(int threshold)
	{
		charsThreshold = threshold;
		performCharsSegmentation();
	}

	void ImageSegmenter::setCharsMinSeparatorSize(int size)
	{
		charsMinSeparatorSize = size;
		performCharsSegmentation();
	}

	

	void ImageSegmenter::setCharsMinObjectSize(int size)
	{
		charsMinObjectSize = size;
		performCharsSegmentation();
	}


	void ImageSegmenter::performLinesSegmentation()
	{
		lines = segmentation(image, VERTICAL, linesThreshold, linesMinSeparatorSize, linesMinObjectSize);
	}

	void ImageSegmenter::performWordsSegmentation()
	{
		for (auto line : lines)
		{
			auto word = segmentation(line, HORIZONTAL, wordsThreshold, wordsMinSeparatorSize, wordsMinObjectSize);
			wordsByLines.push_back(word);
		}
	}

	

	void ImageSegmenter::performCharsSegmentation()
	{
		for (auto wordsByLine : wordsByLines)
		{
			vector<vector<Mat>> charactersByLine;
			for (auto word : wordsByLine)
			{
				vector<Mat> charactersByWordInLines = segmentation(word, HORIZONTAL, charsThreshold, charsMinSeparatorSize, charsMinObjectSize);
				charactersByLine.push_back(charactersByWordInLines);
				charsByWords.push_back(charactersByWordInLines);
				characters.insert(characters.end(), charactersByWordInLines.begin(), charactersByWordInLines.end());
				characters.push_back(Mat::ones(3, 3, CV_8U) * 255);
			}
			charsByWordsByLines.push_back(charactersByLine);
		}
	}

	void ImageSegmenter::performSegmentation()
	{
		performLinesSegmentation();
		performWordsSegmentation();
		performCharsSegmentation();
	}

	vector<Mat> ImageSegmenter::getLines() const
	{
		return lines;
	}

	vector<vector<Mat>> ImageSegmenter::getWordsByLines() const
	{
		return wordsByLines;
	}

	vector<vector<vector<Mat>>> ImageSegmenter::getCharsByWordsByLines() const
	{
		return charsByWordsByLines;
	}

	vector<vector<Mat>> ImageSegmenter::getCharsByWords() const
	{
		return charsByWords;
	}

	vector<Mat> ImageSegmenter::getCharacters() const
	{
		return characters;
	}

	Mat ImageSegmenter::getImage()
	{
		return image;
	}

}

