///////////////////////////////////////////////////////////
//  TextImageNN.h
//  Implementation of the Class TextImageNN
//  Created on:      07-Dec-2015 09:52:45
//  Original author: egors
///////////////////////////////////////////////////////////

#if !defined(EA_C3AB34C6_3481_49ed_BB63_80E73507D3A9__INCLUDED_)
#define EA_C3AB34C6_3481_49ed_BB63_80E73507D3A9__INCLUDED_

#include <opencv2/core.hpp>

#include "../NN/NN.h"
#include "../ImageProcessor/ImageSegmenter.h"
#include "../ImageProcessor/ImageProcessor.h"
#include "../TextProcessor/TextProcessor.h"

using namespace std;
using namespace cv;
using namespace nnor;


class TextImageNN
{

public:
	TextImageNN();
	virtual ~TextImageNN();
	ImageSegmenter *m_ImageSegmenter;
	ImageProcessor *m_ImageProcessor;
	TextProcessor *m_TextProcessor;
	NN *m_NN;

	string getText();
	void setText(string text);
	Mat getImage();
	setImage(image);
	Mat setROI(Rect roi);
	Mat setRotationAngle(double angle);
	Mat performAutomaticRotation();
	Mat setBlurFilterType(BlurFilterType filterType);
	Mat setBlurSize(Size size);
	Mat setThresholdType(ThresholdTypes type);
	Mat setAdaptiveThresholdType(AdaptiveThresholdTypes type);
	Mat setThresholdBlockSize(int size);
	Mat setThresholdSkew(double c);
	void setImage(image);

private:
	string text;
	Mat image;
	NN nn;

};
#endif // !defined(EA_C3AB34C6_3481_49ed_BB63_80E73507D3A9__INCLUDED_)
