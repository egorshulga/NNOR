#include "imagePreprocess.h"

#include <opencv2/imgproc.hpp>


int nnor::getSize(Mat projection, ProjectionType projectionType)
{
	if (projectionType == VERTICAL)
		return projection.rows;
	if (projectionType == HORIZONTAL)
		return projection.cols;
	return 0;
}

int nnor::getDimension(Mat projection, ProjectionType projectionType)
{
	if (projectionType == VERTICAL)
		return projection.cols;
	if (projectionType == HORIZONTAL)
		return projection.rows;
	return 0;
}


Mat nnor::projection(Mat src, ProjectionType projectionType)
{
	Mat projection;
	reduce(src, projection, projectionType, CV_REDUCE_SUM, CV_32SC1);
	projection = projection / 255;

//	int histBinsCount = getSize(projection, projectionType);
//	int histogramMaxValue = 0;
//	for (int i = 0; i < histBinsCount; i++)
//	{
//		if (projection.at<int>(i) > histogramMaxValue)
//			histogramMaxValue = projection.at<int>(i);
//	}
//	projection = histogramMaxValue - projection;

	projection = getDimension(src, projectionType) - projection;

	return projection;
}


Mat nnor::projectionHistogram(Mat src, ProjectionType projectionType)
{
	Mat projection = nnor::projection(src, projectionType);

	int histBinsCount = getSize(projection, projectionType);

	Mat projectionHistogram(src.size(), src.type());

	if (projectionType == VERTICAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, Point(0, i), Point(projection.at<int>(i), i), 0);
		}
	}
	if (projectionType == HORIZONTAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, Point(i, 0), Point(i, projection.at<int>(i)), 0);
		}
	}
	return projectionHistogram;
}

void nnor::drawProjectionHistogram(Mat src, ProjectionType projectionType)
{
	Mat projection = nnor::projection(src, projectionType);

	int histBinsCount = getSize(projection, projectionType);

	Mat projectionHistogram(src.size(), src.type());

	if (projectionType == VERTICAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(src, Point(0, i), Point(projection.at<int>(i), i), 0);
		}
	}
	if (projectionType == HORIZONTAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(src, Point(i, 0), Point(i, projection.at<int>(i)), 0);
		}
	}
}


Mat nnor::thresholdedProjection(Mat src, ProjectionType projectionType, int threshold)
{
	Mat projection = nnor::projection(src, projectionType);
	int histBinsCount = getSize(projection, projectionType);
	for (int i = 0; i < projection.rows; i++)
	{
		if (projection.at<int>(i) < threshold)
		{
			projection.at<int>(i) = 0;
		}
	}
	return projection;
}

Mat nnor::thresholdedProjectionHistogram(Mat src, ProjectionType projectionType, int threshold)
{
	Mat thresholdedProjection = nnor::thresholdedProjection(src, projectionType, threshold);
	Mat projectionHistogram(src.size(), src.type());

	int histBinsCount = getSize(thresholdedProjection, projectionType);

	if (projectionType == VERTICAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, Point(0, i), Point(thresholdedProjection.at<int>(i), i), 0);
		}
	}
	if (projectionType == HORIZONTAL)
	{
		for (int i = 0; i < histBinsCount; i++)
		{
			line(projectionHistogram, Point(i, 0), Point(i, thresholdedProjection.at<int>(i)), 0);
		}
	}

	return projectionHistogram;
}