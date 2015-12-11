#pragma once

#include <opencv2/core.hpp>


using namespace std;
using namespace cv;

namespace nnor
{
	class NN
	{
		//number of neurons
		int nInput, nHidden, nOutput;
		//input neurons resolution
		//multiplicity of these values is equal to nInput
		int nInputHeight;
		int nInputWidth;

		//neurons
		double* inputNeurons;
		double* hiddenNeurons;
		double* outputNeurons;

		//weights
		double** wInputHidden;
		double** wHiddenOutput;

		//change to weights
		double** deltaInputHidden;
		double** deltaHiddenOutput;

		//error gradients
		double* hiddenErrorGradients;
		double* outputErrorGradients;
		//batch learning flag
		bool useBatch = false;

		//learning parameters
		double learningRate;					// adjusts the step size of the weight update	
		double momentum;						// improves performance of stochastic learning (don't use for batch)


	public:
		NN(wstring inputFilename);
		NN(int numInputHeight, int numInputWidth, int numHidden, int numOutput);
		~NN();

		int getNumberOfInputNeurons();
		int getInputNeuronsHeight();
		int getInputNeuronsWidth();

		//weight operations
//		bool loadWeights(wstring inputFilename);
		bool saveWeights(wstring outputFilename);
		int* feedForwardPattern(int* pattern);
		void setTrainingParameters(double lR, double m, bool batch);
		void trainWithPattern(int* pattern, int* target);



	private:
		void createNeuronsAndWeightsLists();
		void initializeWeights();
		inline double activationFunction(double x);
		inline int clampOutput(double x);
		void feedForward(int* pattern);
		void backpropagate(int* target);
		double getOutputErrorGradient(double desiredValue, double outputValue);
		double getHiddenErrorGradient(int j);
		void updateWeights();
	};
}