/*******************************************************************
* Basic Feed Forward Neural Network Class
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
********************************************************************/

#ifndef NNetwork
#define NNetwork

#include "dataReader.h"

class NeuralNetworkTrainer;

class NeuralNetwork
{
	//class members
	//--------------------------------------------------------------------------------------------
private:

	//number of neurons
	int nInput, nHidden, nOutput;
	
	//neurons
	double* inputNeurons;
	double* hiddenNeurons;
	double* outputNeurons;

	//weights
	double** wInputHidden;
	double** wHiddenOutput;
		
	//Friends
	//--------------------------------------------------------------------------------------------
	friend NeuralNetworkTrainer;
	
	//public methods
	//--------------------------------------------------------------------------------------------
public:

	//constructor & destructor
	NeuralNetwork(int numInput, int numHidden, int numOutput);
	~NeuralNetwork();

	//weight operations
	bool loadWeights(char* inputFilename);
	bool saveWeights(char* outputFilename);
	int* feedForwardPattern( double* pattern );
	double getSetAccuracy( vector<DataEntry*>& set );
	double getSetMSE( vector<DataEntry*>& set );

	//private methods
	//--------------------------------------------------------------------------------------------
private: 
	void initializeWeights();
	inline double activationFunction( double x );
	inline int clampOutput( double x );
	void feedForward( double* pattern );
	
};

#endif
