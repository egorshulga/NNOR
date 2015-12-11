#include "NN.h"

#include <iostream>
#include <vector>
#include <fstream>
//#include <math.h>


namespace nnor
{
	NN::NN(wstring filename)
	{
		fstream inputFile;
		inputFile.open(filename, ios::in);

		if (inputFile.is_open())
		{
			vector<double> weights;
			string line = "";
			//read data
			while (!inputFile.eof())
			{
				getline(inputFile, line);
				//process line
				if (line.length() > 2)
				{	//store inputs		
					char* cstr = new char[line.size() + 1];
					char* t;
					strcpy_s(cstr, line.size(), line.c_str());
					//tokenise
					int i = 0;
					t = strtok_s(cstr, ",", nullptr);
					while (t != nullptr)
					{
						weights.push_back(atof(t));
						//move token onwards
						t = strtok_s(cstr, ",", nullptr);
						i++;
					}
					//free memory
					delete[] cstr;
				}
			}

			if (weights.size() < 4)
			{
				wcout << L"Incorrect values in input file: " << filename << L" - unable to initialize NN" << endl;
				inputFile.close();
				return;
			}

			int pos = 0;
			nInputHeight = weights[pos++];
			nInputWidth = weights[pos++];
			nHidden = weights[pos++];
			nOutput = weights[pos++];
			nInput = nInputHeight * nInputWidth;
			//check if sufficient weights were loaded
			if (weights.size() != ((nInput + 1) * nHidden + (nHidden + 1) * nOutput + 4)) //first 4 values - numbers of neurons in each layer
			{
				wcout << endl << L"Error - Incorrect number of weights in input file: " << filename << endl;
				inputFile.close();
				return;
			}

			createNeuronsAndWeightsLists();

			//initialize weights
			for (int i = 0; i <= nInput; i++)
			{
				for (int j = 0; j < nHidden; j++)
				{
					wInputHidden[i][j] = weights[pos++];
				}
			}
			for (int i = 0; i <= nHidden; i++)
			{
				for (int j = 0; j < nOutput; j++)
				{
					wHiddenOutput[i][j] = weights[pos++];
				}
			}
			wcout << endl << L"Neuron weights loaded successfuly from '" << filename << L"'" << endl;
			inputFile.close();
		}
		else
		{
			wcout << endl << L"Error - Weight input file '" << filename << L"' could not be opened: " << endl;
		}
	}

	NN::NN(int numInputHeight, int numInputWidth, int nH, int nO) : nInput(numInputHeight*numInputWidth),
		nHidden(nH), nOutput(nO), nInputHeight(numInputHeight), nInputWidth(numInputWidth)
	{
		createNeuronsAndWeightsLists();
		initializeWeights();
	}


	int NN::getNumberOfInputNeurons()
	{
		return nInput;
	}

	int NN::getInputNeuronsHeight()
	{
		return nInputHeight;
	}

	int NN::getInputNeuronsWidth()
	{
		return nInputWidth;
	}

	NN::~NN()
	{
		//delete neurons
		delete[] inputNeurons;
		delete[] hiddenNeurons;
		delete[] outputNeurons;

		//delete weight storage
		for (int i = 0; i <= nInput; i++) delete[] wInputHidden[i];
		delete[] wInputHidden;

		for (int j = 0; j <= nHidden; j++) delete[] wHiddenOutput[j];
		delete[] wHiddenOutput;
	}



	//	bool NN::loadWeights(wstring filename)
	//	{
	//		//open file for reading
	//		fstream inputFile;
	//		inputFile.open(filename, ios::in);
	//
	//		if (inputFile.is_open())
	//		{
	//			vector<double> weights;
	//			string line = "";
	//
	//			//read data
	//			while (!inputFile.eof())
	//			{
	//				getline(inputFile, line);
	//
	//				//process line
	//				if (line.length() > 2)
	//				{
	//					//store inputs		
	//					char* cstr = new char[line.size() + 1];
	//					char* t;
	//					strcpy_s(cstr, line.size(), line.c_str());
	//
	//					//tokenise
	//					int i = 0;
	//					t = strtok_s(cstr, ",", NULL);
	//
	//					while (t != NULL)
	//					{
	//						weights.push_back(atof(t));
	//
	//						//move token onwards
	//						t = strtok_s(cstr, ",", NULL);
	//						i++;
	//					}
	//
	//					//free memory
	//					delete[] cstr;
	//				}
	//			}
	//
	//			//check if sufficient weights were loaded
	//			if (weights.size() != ((nInput + 1) * nHidden + (nHidden + 1) * nOutput))
	//			{
	//				wcout << endl << L"Error - Incorrect number of weights in input file: " << filename << endl;
	//
	//				//close file
	//				inputFile.close();
	//
	//				return false;
	//			}
	//
	//			//set weights
	//			int pos = 0;
	//			nInputHeight = weights[pos++];
	//			nInputWidth = weights[pos++];
	//			nHidden = weights[pos++];
	//			nOutput = weights[pos++];
	//			nInput = nInputHeight * nInputWidth;
	//			for (int i = 0; i <= nInput; i++)
	//			{
	//				for (int j = 0; j < nHidden; j++)
	//				{
	//					wInputHidden[i][j] = weights[pos++];
	//				}
	//			}
	//
	//			for (int i = 0; i <= nHidden; i++)
	//			{
	//				for (int j = 0; j < nOutput; j++)
	//				{
	//					wHiddenOutput[i][j] = weights[pos++];
	//				}
	//			}
	//
	//			//print success
	//			wcout << endl << L"Neuron weights loaded successfuly from '" << filename << L"'" << endl;
	//
	//			//close file
	//			inputFile.close();
	//
	//			return true;
	//		}
	//		else
	//		{
	//			wcout << endl << L"Error - Weight input file '" << filename << L"' could not be opened: " << endl;
	//			return false;
	//		}
	//	}



	bool NN::saveWeights(wstring filename)
	{
		//open file for reading
		fstream outputFile;
		outputFile.open(filename, ios::out);

		if (outputFile.is_open())
		{
			outputFile.precision(50);

			outputFile << nInputHeight << "," << nInputWidth << "," << nHidden << "," << nOutput << ",";

			//output weights
			for (int i = 0; i <= nInput; i++)
			{
				for (int j = 0; j < nHidden; j++)
				{
					outputFile << wInputHidden[i][j] << ",";
				}
			}

			for (int i = 0; i <= nHidden; i++)
			{
				for (int j = 0; j < nOutput; j++)
				{
					outputFile << wHiddenOutput[i][j];
					if (i * nOutput + j + 1 != (nHidden + 1) * nOutput) outputFile << ",";
				}
			}

			//print success
			wcout << endl << L"Neuron weights saved to '" << filename << L"'" << endl;

			//close file
			outputFile.close();

			return true;
		}
		else
		{
			wcout << endl << L"Error - Weight output file '" << filename << L"' could not be created: " << endl;
			return false;
		}
	}



	int* NN::feedForwardPattern(int* pattern)
	{
		feedForward(pattern);

		//create copy of output results
		int* results = new int[nOutput];
		//	for (int i = 0; i < nOutput; i++) results[i] = outputNeurons[i];
		for (int i = 0; i < nOutput; i++) results[i] = clampOutput(outputNeurons[i]);

		return results;
	}


	void NN::createNeuronsAndWeightsLists()
	{
		//create neuron lists
		//--------------------------------------------------------------------------------------------------------
		inputNeurons = new(double[nInput + 1]);
		for (int i = 0; i < nInput; i++) inputNeurons[i] = 0;

		//create input bias neuron
		inputNeurons[nInput] = -1;

		hiddenNeurons = new(double[nHidden + 1]);
		for (int i = 0; i < nHidden; i++) hiddenNeurons[i] = 0;

		//create hidden bias neuron
		hiddenNeurons[nHidden] = -1;

		outputNeurons = new(double[nOutput]);
		for (int i = 0; i < nOutput; i++) outputNeurons[i] = 0;

		//create weight lists (include bias neuron weights)
		//--------------------------------------------------------------------------------------------------------
		wInputHidden = new(double*[nInput + 1]);
		for (int i = 0; i <= nInput; i++)
		{
			wInputHidden[i] = new (double[nHidden]);
			for (int j = 0; j < nHidden; j++) wInputHidden[i][j] = 0;
		}

		wHiddenOutput = new(double*[nHidden + 1]);
		for (int i = 0; i <= nHidden; i++)
		{
			wHiddenOutput[i] = new (double[nOutput]);
			for (int j = 0; j < nOutput; j++) wHiddenOutput[i][j] = 0;
		}
	}

	void NN::initializeWeights()
	{
		//set range
		double rH = 1 / sqrt((double)nInput);
		double rO = 1 / sqrt((double)nHidden);

		//set weights between input and hidden 		
		//--------------------------------------------------------------------------------------------------------
		for (int i = 0; i <= nInput; i++)
		{
			for (int j = 0; j < nHidden; j++)
			{
				//set weights to random values
				wInputHidden[i][j] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
			}
		}

		//set weights between input and hidden
		//--------------------------------------------------------------------------------------------------------
		for (int i = 0; i <= nHidden; i++)
		{
			for (int j = 0; j < nOutput; j++)
			{
				//set weights to random values
				wHiddenOutput[i][j] = (((double)(rand() % 100) + 1) / 100 * 2 * rO) - rO;
			}
		}
	}



	inline double NN::activationFunction(double x)
	{
		//sigmoid function
		return 1 / (1 + exp(-x));
	}



	inline int NN::clampOutput(double x)
	{
		if (x < 0.1) return 0;
		if (x > 0.9) return 1;
		return -1;
	}


	void NN::feedForward(int* pattern)
	{
		//set input neurons to input values
		for (int i = 0; i < nInput; i++) inputNeurons[i] = pattern[i];

		//Calculate Hidden Layer values - include bias neuron
		//--------------------------------------------------------------------------------------------------------
		for (int j = 0; j < nHidden; j++)
		{
			//clear value
			hiddenNeurons[j] = 0;

			//get weighted sum of pattern and bias neuron
			for (int i = 0; i <= nInput; i++) hiddenNeurons[j] += inputNeurons[i] * wInputHidden[i][j];

			//set to result of sigmoid
			hiddenNeurons[j] = activationFunction(hiddenNeurons[j]);
		}

		//Calculating Output Layer values - include bias neuron
		//--------------------------------------------------------------------------------------------------------
		for (int k = 0; k < nOutput; k++)
		{
			//clear value
			outputNeurons[k] = 0;

			//get weighted sum of pattern and bias neuron
			for (int j = 0; j <= nHidden; j++) outputNeurons[k] += hiddenNeurons[j] * wHiddenOutput[j][k];

			//set to result of sigmoid
			outputNeurons[k] = activationFunction(outputNeurons[k]);
		}
	}

	void NN::trainWithPattern(int* pattern, int* target)
	{
		feedForward(pattern);
		backpropagate(target);
	}

	void NN::backpropagate(int* desiredOutputs)
	{
		//modify deltas between hidden and output layers
		//--------------------------------------------------------------------------------------------------------
		for (int k = 0; k < nOutput; k++)
		{
			//get error gradient for every output node
			outputErrorGradients[k] = getOutputErrorGradient(desiredOutputs[k], outputNeurons[k]);

			//for all nodes in hidden layer and bias neuron
			for (int j = 0; j <= nHidden; j++)
			{
				//calculate change in weight
				if (useBatch) deltaHiddenOutput[j][k] += learningRate * hiddenNeurons[j] * outputErrorGradients[k];
				else deltaHiddenOutput[j][k] = learningRate * hiddenNeurons[j] * outputErrorGradients[k] + momentum * deltaHiddenOutput[j][k];
			}
		}

		//modify deltas between input and hidden layers
		//--------------------------------------------------------------------------------------------------------
		for (int j = 0; j < nHidden; j++)
		{
			//get error gradient for every hidden node
			hiddenErrorGradients[j] = getHiddenErrorGradient(j);

			//for all nodes in input layer and bias neuron
			for (int i = 0; i <= nInput; i++)
			{
				//calculate change in weight 
				if (useBatch) deltaInputHidden[i][j] += learningRate * inputNeurons[i] * hiddenErrorGradients[j];
				else deltaInputHidden[i][j] = learningRate * inputNeurons[i] * hiddenErrorGradients[j] + momentum * deltaInputHidden[i][j];

			}
		}

		//if using stochastic learning update the weights immediately
		if (!useBatch) updateWeights();

	}

	inline double NN::getOutputErrorGradient(double desiredValue, double outputValue)
	{
		//return error gradient
		return outputValue * (1 - outputValue) * (desiredValue - outputValue);
	}

	double NN::getHiddenErrorGradient(int j)
	{
		//get sum of hidden->output weights * output error gradients
		double weightedSum = 0;
		for (int k = 0; k < nOutput; k++) weightedSum += wHiddenOutput[j][k] * outputErrorGradients[k];

		//return error gradient
		return hiddenNeurons[j] * (1 - hiddenNeurons[j]) * weightedSum;
	}

	void NN::updateWeights()
	{
		//input -> hidden weights
		//--------------------------------------------------------------------------------------------------------
		for (int i = 0; i <= nInput; i++)
		{
			for (int j = 0; j < nHidden; j++)
			{
				//update weight
				wInputHidden[i][j] += deltaInputHidden[i][j];

				//clear delta only if using batch (previous delta is needed for momentum
				if (useBatch) deltaInputHidden[i][j] = 0;
			}
		}

		//hidden -> output weights
		//--------------------------------------------------------------------------------------------------------
		for (int j = 0; j <= nHidden; j++)
		{
			for (int k = 0; k < nOutput; k++)
			{
				//update weight
				wHiddenOutput[j][k] += deltaHiddenOutput[j][k];

				//clear delta only if using batch (previous delta is needed for momentum)
				if (useBatch)deltaHiddenOutput[j][k] = 0;
			}
		}
	}

	void NN::setTrainingParameters(double lR, double m, bool batch)
	{
		learningRate = lR;
		momentum = m;
		useBatch = batch;
	}

}