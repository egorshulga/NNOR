///////////////////////////////////////////////////////////
//  ImageSegmenter.h
//  Implementation of the Class ImageSegmenter
//  Created on:      07-Dec-2015 09:52:44
//  Original author: egors
///////////////////////////////////////////////////////////

#if !defined(EA_89BFA354_E964_403d_BA88_EDDA8CF53C35__INCLUDED_)
#define EA_89BFA354_E964_403d_BA88_EDDA8CF53C35__INCLUDED_

#include <opencv2/core.hpp>
#include <vector>
#include "preprocess/imagePreprocess.h"

using namespace cv;
using namespace std;

namespace nnor 
{
	class ImageSegmenter
	{
	public:
		ImageSegmenter();
		ImageSegmenter(Mat image);
		
	private:	//Input data for this processor
		Mat image;

		int linesThreshold = 1;
		int linesMinSeparatorSize = 10;
		int linesMinObjectSize = 30;

		int wordsThreshold = 1;
		int wordsMinSeparatorSize = 15;
		int wordsMinObjectSize = 20;

		int charsThreshold = 1;
		int charsMinSeparatorSize = 1;
		int charsMinObjectSize = 4;
	public:
		void setImage(Mat image);
		Mat getImage();
		void setLinesThreshold(int threshold);
		void setLinesMinSeparatorSize(int size);
		void setLinesMinObjectSize(int size);
		void setWordsThreshold(int threshold);
		void setWordsMinSeparatorSize(int size);
		void setWordsMinObjectSize(int size);
		void setCharsThreshold(int threshold);
		void setCharsMinSeparatorSize(int size);
		void setCharsMinObjectSize(int size);


	private:	//Output data for this processor
		vector<Mat> lines;
		vector<vector<Mat>> wordsByLines;
		vector<vector<vector<Mat>>> charsByWordsByLines;
		vector<vector<Mat>> charsByWords;
		vector<Mat> characters;

		void performLinesSegmentation();
		void performWordsSegmentation();
		void performCharsSegmentation();
	public:
		//Just lines
		vector<Mat> getLines() const;
		//Words hierarchically ordered by lines
		vector<vector<Mat>> getWordsByLines() const;
		//Characters hierarchically ordered by words that are ordered by lines
		vector<vector<vector<Mat>>> getCharsByWordsByLines() const;
		//Characters hierarchically ordered by words
		vector<vector<Mat>> getCharsByWords() const;
		//All characters without hierarchical ordering
		vector<Mat> getCharacters() const;


	public:		//Processing method itself
		void performSegmentation();

	};

}
#endif // !defined(EA_89BFA354_E964_403d_BA88_EDDA8CF53C35__INCLUDED_)
