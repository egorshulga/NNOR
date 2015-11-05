#include "tan_triggs.h"

#include <opencv2/imgproc.hpp>

namespace nnor
{
	/*
	* Copyright (c) 2012. Philipp Wagner <bytefish[at]gmx[dot]de>.
	* Released to public domain under terms of the BSD Simplified license.
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions are met:
	*   * Redistributions of source code must retain the above copyright
	*     notice, this list of conditions and the following disclaimer.
	*   * Redistributions in binary form must reproduce the above copyright
	*     notice, this list of conditions and the following disclaimer in the
	*     documentation and/or other materials provided with the distribution.
	*   * Neither the name of the organization nor the names of its contributors
	*     may be used to endorse or promote products derived from this software
	*     without specific prior written permission.
	*
	*   See <http://www.opensource.org/licenses/bsd-license>
	*/


	// Normalizes a given image into a value range between 0 and 255.
	cv::Mat norm_0_255(const cv::Mat& src) {
		// Create and return normalized image:
		cv::Mat dst;
		switch (src.channels()) {
		case 1:
			normalize(src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
			break;
		case 3:
			normalize(src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
			break;
		default:
			src.copyTo(dst);
			break;
		}
		return dst;
	}

	//
	// Calculates the TanTriggs Preprocessing as described in:
	//
	//      Tan, X., and Triggs, B. "Enhanced local texture feature sets for face
	//      recognition under difficult lighting conditions.". IEEE Transactions
	//      on Image Processing 19 (2010), 1635–650.
	//
	// Default parameters are taken from the paper.
	//
	cv::Mat tan_triggs_preprocessing(cv::InputArray src,
		float alpha, float tau, float gamma, int sigma0,
		int sigma1) {

		// Convert to floating point:
		cv::Mat X = src.getMat();
		X.convertTo(X, CV_32FC1);
		// Start preprocessing:
		cv::Mat I;
		pow(X, gamma, I);
		// Calculate the DOG Image:
		{
			cv::Mat gaussian0, gaussian1;
			// Kernel Size:
			int kernel_sz0 = (3 * sigma0);
			int kernel_sz1 = (3 * sigma1);
			// Make them odd for OpenCV:
			kernel_sz0 += ((kernel_sz0 % 2) == 0) ? 1 : 0;
			kernel_sz1 += ((kernel_sz1 % 2) == 0) ? 1 : 0;
			GaussianBlur(I, gaussian0, cv::Size(kernel_sz0, kernel_sz0), sigma0, sigma0, cv::BORDER_REPLICATE);
			GaussianBlur(I, gaussian1, cv::Size(kernel_sz1, kernel_sz1), sigma1, sigma1, cv::BORDER_REPLICATE);
			subtract(gaussian0, gaussian1, I);
		}

		{
			double meanI = 0.0;
			{
				cv::Mat tmp;
				pow(abs(I), alpha, tmp);
				meanI = mean(tmp).val[0];

			}
			I = I / pow(meanI, 1.0 / alpha);
		}

		{
			double meanI = 0.0;
			{
				cv::Mat tmp;
				pow(min(abs(I), tau), alpha, tmp);
				meanI = mean(tmp).val[0];
			}
			I = I / pow(meanI, 1.0 / alpha);
		}

		// Squash into the tanh:
		{
			cv::Mat exp_x, exp_negx;
			exp(I / tau, exp_x);
			exp(-I / tau, exp_negx);
			divide(exp_x - exp_negx, exp_x + exp_negx, I);
			I = tau * I;
		}
		return I;
	}

	cv::Mat tan_triggs(cv::Mat image)
	{
		// Calculate the TanTriggs Preprocessed image with default parameters:
		return tan_triggs_preprocessing(image);
	}
}