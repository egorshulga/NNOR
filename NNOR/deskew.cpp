#include "preprocess.h"

cv::Mat nnor::deskew(cv::Mat src)
{
	cv::Mat img;
	src.copyTo(img);
	bitwise_not(img, img);

	std::vector<cv::Point> points;
	cv::Mat_<uchar>::iterator it = img.begin<uchar>();
	cv::Mat_<uchar>::iterator end = img.end<uchar>();
	for (; it != end; ++it)
		if (*it)
			points.push_back(it.pos());

	cv::RotatedRect box = minAreaRect(cv::Mat(points));

	double angle = box.angle;
	if (angle < -45.)
		angle += 90.;

	cv::Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

	cv::Mat rotated;
	warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);

	cv::Size box_size = box.size;
	if (box.angle < -45.)
		std::swap(box_size.width, box_size.height);
	cv::Mat cropped;
	getRectSubPix(rotated, box_size, box.center, cropped);

	bitwise_not(cropped, cropped);
	return cropped;
}