#include "outputslist.h"

OutputsList::OutputsList(vector<Body> bodyIn, vector<double> frequenciesIn) : theBodyList(bodyIn), theFrequencyList(frequenciesIn)
{}


OutputsList::~OutputsList()
{}

//Perform Calculations for all bodies
void OutputsList::calculateOutputs()
{
	for(int i = 0; i < theBodyList.size(); i++)
	{
		OutputsBody newOutputsBody(theBodyList[i], theFrequencyList);//create new OutputBody
		newOutputsBody.calculateOutputs();
		theOutputsBodyList.push_back(newOutputsBody); //add to the vector 
	}
}
