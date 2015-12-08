#include "imagePreprocess.h"

Mat nnor::selectRectangleROI(Mat src, Rect roi)
{
	Mat roiImage = src(roi);
	return roiImage;
}