///////////////////////////////////////////////////////////
//  NN.h
//  Implementation of the Class NN
//  Created on:      07-Dec-2015 09:52:44
//  Original author: egors
///////////////////////////////////////////////////////////

#if !defined(EA_C4EF62E5_F3F8_4c29_B029_D34552549A5E__INCLUDED_)
#define EA_C4EF62E5_F3F8_4c29_B029_D34552549A5E__INCLUDED_

#include <opencv2/core.hpp>

#include "NeuralNetwork/NeuralNetwork.h"
#include "NeuralNetwork/NeuralNetworkTrainer.h"

using namespace std;
using namespace cv;

class NN
{

public:
	NN();
	NeuralNetwork *neuralNetwork;
	NeuralNetworkTrainer *trainer;

	string recognize(vector<Mat> chars);
	void train(vector<Mat> chars, string text);

private:
	double* transformToDataEntry(Mat character);
	double* transformToDataEntry(char character);

};
#endif // !defined(EA_C4EF62E5_F3F8_4c29_B029_D34552549A5E__INCLUDED_)
