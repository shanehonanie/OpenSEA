#ifndef OUTPUTSLIST_H
#define OUTPUTSLIST_H
#include <vector>
#include "bodywithsolution.h"
#include "outputsbody.h"
using namespace std;

class OutputsList
{
public:
	OutputsList();
	OutputsList(vector<BodyWithSolution>, vector<double>, vector<double>);
	~OutputsList();
	vector<OutputsBody> theOutputsBodyList; //List of each body with computed globlal matrices
	vector<BodyWithSolution> theBodyList;
	vector<double> theFrequencyList;
	vector<double> theDirectionList;
	void calculateOutputs();
};
#endif
