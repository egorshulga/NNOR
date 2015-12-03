#include "imagePreprocess.h"

#include <opencv2/imgproc.hpp>

Mat nnor::blur(Mat src, BlurFilterType filterType, Size ksize)
{
	Mat image;

	switch(filterType)
	{
	case BLUR_NORMALIZED_BOX:
		blur(src, image, ksize);
		break;
	case BLUR_MEDIAN:
	{
		int size = (ksize.height + ksize.width) / 2;
		medianBlur(src, image, size);
	}
	break;
	case BLUR_GAUSSIAN:
		GaussianBlur(src, image, ksize, 0);
		break;
	default:
		return src;
	}

	return image;
}