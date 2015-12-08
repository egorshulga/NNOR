/*******************************************************************
* Neural Network Training Class
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
*********************************************************************/

#ifndef NNetworkTrainer
#define NNetworkTrainer

//standard includes
#include <fstream>
#include <vector>

//neural network header
#include "neuralNetwork.h"

//Constant Defaults!
#define LEARNING_RATE 0.001
#define MOMENTUM 0.9
#define MAX_EPOCHS 1500
#define DESIRED_ACCURACY 90  
#define DESIRED_MSE 0.001 

/*******************************************************************
* Basic Gradient Descent Trainer with Momentum and Batch Learning
********************************************************************/
class NeuralNetworkTrainer
{
	//class members
	//--------------------------------------------------------------------------------------------

private:

	//network to be trained
	NeuralNetwork* NN;

	//learning parameters
	double learningRate;					// adjusts the step size of the weight update	
	double momentum;						// improves performance of stochastic learning (don't use for batch)

	//epoch counter
	long epoch;
	long maxEpochs;
	
	//accuracy/MSE required
	double desiredAccuracy;
	
	//change to weights
	double** deltaInputHidden;
	double** deltaHiddenOutput;

	//error gradients
	double* hiddenErrorGradients;
	double* outputErrorGradients;

	//accuracy stats per epoch
	double trainingSetAccuracy;
	double validationSetAccuracy;
	double generalizationSetAccuracy;
	double trainingSetMSE;
	double validationSetMSE;
	double generalizationSetMSE;

	//batch learning flag
	bool useBatch;

	//log file handle
	bool loggingEnabled;
	fstream logFile;
	int logResolution;
	int lastEpochLogged;

	//public methods
	//--------------------------------------------------------------------------------------------
public:	
	
	NeuralNetworkTrainer( NeuralNetwork* untrainedNetwork );
	void setTrainingParameters( double lR, double m, bool batch );
	void setStoppingConditions( int mEpochs, double dAccuracy);
	void useBatchLearning( bool flag ){ useBatch = flag; }
	void enableLogging( const char* filename, int resolution );

	void trainNetwork( TrainingDataSet* tSet );

	void backpropagate(double* desiredOutputs);

	//private methods
	//--------------------------------------------------------------------------------------------
private:
	inline double getOutputErrorGradient( double desiredValue, double outputValue );
	double getHiddenErrorGradient( int j );
	void runTrainingEpoch( vector<DataEntry*> trainingSet );
	void updateWeights();
};


#endif