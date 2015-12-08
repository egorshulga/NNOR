#include "imagePreprocess.h"

Mat nnor::deskew(Mat src)
{
	Mat img;
	src.copyTo(img);
	bitwise_not(img, img);

	vector<Point> points;
	Mat_<uchar>::iterator it = img.begin<uchar>();
	Mat_<uchar>::iterator end = img.end<uchar>();
	for (; it != end; ++it)
		if (*it)
			points.push_back(it.pos());

	RotatedRect box = minAreaRect(Mat(points));

	double angle = box.angle;
	if (angle < -45.)
		angle += 90.;

	Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

	Mat rotated;
	warpAffine(img, rotated, rot_mat, img.size(), INTER_CUBIC);

	Size box_size = box.size;
	if (box.angle < -45.)
		std::swap(box_size.width, box_size.height);
	Mat cropped;
	getRectSubPix(rotated, box_size, box.center, cropped);

	bitwise_not(cropped, cropped);
	return cropped;
}