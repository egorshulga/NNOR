#include "imagePreprocess.h"

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
vector<Mat> nnor::segmentation(Mat src, int separationType , int threshold, int minSeparatorSize, int minObjectSize)
{
	vector<Mat> objects;
	int size = getSize(src, separationType);
	int dimension = getDimension(src, separationType);


	Mat projection = nnor::projection(src, separationType);
	Mat projectionHist = projectionHistogram(src, separationType);		//uncomment to build histogram
	if (separationType == VERTICAL) line(projectionHist, Point(threshold, 0), Point(threshold, size), Scalar(127));
	else line(projectionHist, Point(0, threshold), Point(size, threshold), Scalar(127));

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
					Rect objectRect;
					if (separationType == VERTICAL) objectRect = Rect(0, objectStart, dimension, separatorStart - objectStart);
					else objectRect = Rect(objectStart, 0, separatorStart - objectStart, dimension);
					Mat object = src(objectRect);
					cv::rectangle(src, objectRect, Scalar(127));
					objects.push_back(object);
				}
				i--;
				break;
			}
		}
	}
	return objects;
}

