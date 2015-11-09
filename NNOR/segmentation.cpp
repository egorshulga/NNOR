#include "preprocess.h"

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

//The idea is that one can separate lines, words and characters using one algorythm.
//It only should be defined is it either vertical or horyzontal segmentation
//and three parameters:
// - segmentation threshold (how many dots in a separator can be)
// - minimal separator size 
// - minimal object size (i.e. unsatisfactory groups of rows and columns will be ignored)
//AutoCrop should be applied manually
std::vector<cv::Mat> nnor::segmentation(cv::Mat src, int separationType , int threshold, int minSeparatorSize, int minObjectSize)
{
	std::vector<cv::Mat> objects;
	int size = getSize(src, separationType);
	int dimension = getDimension(src, separationType);


	cv::Mat projection = nnor::projection(src, separationType);
	cv::Mat projectionHist = nnor::projectionHistogram(src, separationType);		//uncomment to build histogram
	if (separationType == VERTICAL) line(projectionHist, cv::Point(threshold, 0), cv::Point(threshold, size), cv::Scalar(127));
	else line(projectionHist, cv::Point(0, threshold), cv::Point(size, threshold), cv::Scalar(127));

	for (int i = 0; i < size; i++)  
	{
		int objectStart = i;
		while (projection.at<int>(i) > threshold)
		{
			while ((i < size) && (projection.at<int>(i) > threshold))
				i++;
			int separatorStart = i;
			while ((i < size) && (projection.at<int>(i) <= threshold))
				i++;
			int nextObjectStart = i;

			if (nextObjectStart >= size || nextObjectStart - separatorStart >= minSeparatorSize) 
			{
				if (separatorStart - objectStart >= minObjectSize)
				{
					cv::Rect objectRect;
					if (separationType == VERTICAL) objectRect = cv::Rect(0, objectStart, dimension, separatorStart - objectStart);
					else objectRect = cv::Rect(objectStart, 0, separatorStart - objectStart, dimension);
					cv::Mat object = src(objectRect);
					objects.push_back(object);
				}
				i--;
				break;
			}
		}
	}
	return objects;
}

