#include "outputslist.h"

OutputsList::OutputsList(vector<Body> bodyIn, vector<double> frequenciesIn, vector<double> directionsIn) 
	: theBodyList(bodyIn), theFrequencyList(frequenciesIn), theDirectionList(directionsIn)
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
