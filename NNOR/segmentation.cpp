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


cv::Mat nnor::autoCrop(cv::Mat src, int threshold)
{
	cv::Mat verticalProjection = projection(src, VERTICAL);
	cv::Mat horizontalProjection = projection(src, HORIZONTAL);

	int x0, y0, x1, y1;
	for (x0 = 0; x0 < src.cols; x0++)
		if (horizontalProjection.at<int>(x0) > threshold)
			break;
	for (y0 = 0; y0 < src.rows; y0++)
		if (verticalProjection.at<int>(y0) > threshold)
			break;
	for (x1 = src.cols - 1; x1 >= 0; x1--)
		if (horizontalProjection.at<int>(x1) > threshold)
			break;
	for (y1 = src.rows - 1; y1 >= 0; y1--)
		if (verticalProjection.at<int>(y1) > threshold)
			break;

	if ((x1 - x0 <= 0) || (y1 - y0 <= 0))
		return cv::Mat();

	cv::Mat result = src(cv::Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1));
	return result;
}

