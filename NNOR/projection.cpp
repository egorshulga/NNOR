#include "projection.h"

#include <opencv2/imgproc.hpp>


int nnor::getProjectionSize(cv::Mat projection, int projectionType)
{
	if (projectionType == PROJECTION_VERTICAL)
		return projection.rows;
	if (projectionType == PROJECTION_HORIZONTAL)
		return projection.cols;
	return 0;
}

int nnor::getProjectionDimension(cv::Mat projection, int projectionType)
{
	if (projectionType == PROJECTION_VERTICAL)
		return projection.cols;
	if (projectionType == PROJECTION_HORIZONTAL)
		return projection.rows;
	return 0;
}


cv::Mat nnor::projection(cv::Mat src, int projectionType)
{
	cv::Mat projection;
	reduce(src, projection, projectionType, CV_REDUCE_SUM, CV_32SC1);
	projection = projection / 255;

//	int histBinsCount = getProjectionSize(projection, projectionType);
//	int histogramMaxValue = 0;
//	for (int i = 0; i < histBinsCount; i++)
//	{
//		if (projection.at<int>(i) > histogramMaxValue)
//			histogramMaxValue = projection.at<int>(i);
//	}
//	projection = histogramMaxValue - projection;

	projection = getProjectionDimension(src, projectionType) - projection;

	return projection;
}


cv::Mat nnor::projectionHistogram(cv::Mat src, int projectionType)
{
	cv::Mat projection = nnor::projection(src, projectionType);

	int histBinsCount = getProjectionSize(projection, projectionType);

	cv::Mat projectionHistogram(src.size(), src.type());

	if (projectionType == PROJECTION_VERTICAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, cv::Point(0, i), cv::Point(projection.at<int>(i), i), 0);
		}
	}
	if (projectionType == PROJECTION_HORIZONTAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, cv::Point(i, 0), cv::Point(i, projection.at<int>(i)), 0);
		}
	}
	return projectionHistogram;
}


cv::Mat nnor::thresholdedProjection(cv::Mat src, int projectionType, int threshold)
{
	cv::Mat projection = nnor::projection(src, projectionType);
	int histBinsCount = getProjectionSize(projection, projectionType);
	for (int i = 0; i < projection.rows; i++)
	{
		if (projection.at<int>(i) < threshold)
		{
			projection.at<int>(i) = 0;
		}
	}
	return projection;
}

cv::Mat nnor::thresholdedProjectionHistogram(cv::Mat src, int projectionType, int threshold)
{
	cv::Mat thresholdedProjection = nnor::thresholdedProjection(src, projectionType, threshold);
	cv::Mat projectionHistogram(src.size(), src.type());

	int histBinsCount = getProjectionSize(thresholdedProjection, projectionType);

	if (projectionType == PROJECTION_VERTICAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, cv::Point(0, i), cv::Point(thresholdedProjection.at<int>(i), i), 0);
		}
	}
	if (projectionType == PROJECTION_HORIZONTAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, cv::Point(i, 0), cv::Point(i, thresholdedProjection.at<int>(i)), 0);
		}
	}

	return projectionHistogram;
}