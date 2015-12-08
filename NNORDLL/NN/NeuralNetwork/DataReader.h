/*******************************************************************
* CSV Data File Reader and Training Set Creator
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
********************************************************************/

#ifndef _DATAREADER
#define _DATAREADER

//include standard header files
#include <vector>
#include <string>

using namespace std;

/*******************************************************************
* stores a data item
********************************************************************/
class DataEntry
{
public:	
	
	double* pattern;	//input patterns
	double* target;		//target result

public:	

	DataEntry(double* p, double* t): pattern(p), target(t) {}
		
	~DataEntry()
	{				
		delete[] pattern;
		delete[] target;
	}

};

/*******************************************************************
* Training Sets Storage - stores shortcuts to data items
********************************************************************/
class TrainingDataSet
{
public:

	vector<DataEntry*> trainingSet;
	vector<DataEntry*> generalizationSet;
	vector<DataEntry*> validationSet;

	TrainingDataSet(){}
	
	void clear()
	{
		trainingSet.clear();
		generalizationSet.clear();
		validationSet.clear();
	}
};

//dataset retrieval approach enum
enum { NONE, STATIC, GROWING, WINDOWING };

//data reader class
class DataReader
{
	
//private members
//----------------------------------------------------------------------------------------------------------------
private:

	//data storage
	vector<DataEntry*> data;
	int nInputs;
	int nTargets;

	//current data set
	TrainingDataSet tSet;

	//data set creation approach and total number of dataSets
	int creationApproach;
	int numTrainingSets;
	int trainingDataEndIndex;

	//creation approach variables
	double growingStepSize;			//step size - percentage of total set
	int growingLastDataIndex;		//last index added to current dataSet
	int windowingSetSize;			//initial size of set
	int windowingStepSize;			//how many entries to move window by
	int windowingStartIndex;		//window start index	
	
//public methods
//----------------------------------------------------------------------------------------------------------------
public:

	DataReader(): creationApproach(NONE), numTrainingSets(-1) {}
	~DataReader();
	
	bool loadDataFile( const char* filename, int nI, int nT );
	void setCreationApproach( int approach, double param1 = -1, double param2 = -1 );
	int getNumTrainingSets();	
	
	TrainingDataSet* getTrainingDataSet();
	vector<DataEntry*>& getAllDataEntries();

//private methods
//----------------------------------------------------------------------------------------------------------------
private:
	
	void createStaticDataSet();
	void createGrowingDataSet();
	void createWindowingDataSet();	
	void processLine( string &line );
};

#endif
