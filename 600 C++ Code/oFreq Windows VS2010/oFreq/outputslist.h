#ifndef OUTPUTSLIST_H
#define OUTPUTSLIST_H
#include <vector>
#include "body.h"
#include "outputsbody.h"
using namespace std;

class OutputsList
{
public:
	OutputsList(vector<Body>, vector<double>, vector<double>);
	~OutputsList();
	vector<OutputsBody> theOutputsBodyList; //List of each body with computed globlal matrices
	vector<Body> theBodyList;
	vector<double> theFrequencyList;
	vector<double> theDirectionList;
	void calculateOutputs();
};
#endif
