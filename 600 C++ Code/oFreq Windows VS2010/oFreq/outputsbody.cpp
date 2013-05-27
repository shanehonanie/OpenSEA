#include "outputsbody.h"


OutputsBody::OutputsBody(Body bodyIn, vector<double> frequenciesIn) : theBody(bodyIn), frequencies(frequenciesIn)
{
}


OutputsBody::~OutputsBody()
{
}

void OutputsBody::calculateOutputs()
{
	GlobalMotion theGlobalMotion;
	GlobalVelocity theGlobalVelocity;
	GlobalAcceleration theGlobalAcceleration;

	for(int i = 0; i < frequencies.size(); i++)//iterate through loop and create vector for each frequency
	{
		cx_mat temp(theBody.solutionMatrix.n_rows, GLOBAL_SIZE); //create a marix that is size of solution matrix by 3 (6dof is 6x3)
		temp.submat(0,0, (theBody.solutionMatrix.n_rows-1), 0) = theGlobalMotion.calculateOutput(theBody.solutionMatrix, frequencies[i]); //calculate motion
		temp.submat(0,1, (theBody.solutionMatrix.n_rows-1), 1) = theGlobalVelocity.calculateOutput(theBody.solutionMatrix, frequencies[i]);  //calculate acceleration
		temp.submat(0,2, (theBody.solutionMatrix.n_rows-1), 2) = theGlobalAcceleration.calculateOutput(theBody.solutionMatrix, frequencies[i]); //calculate velocity
		outputType.push_back(temp); //put the 6x3 matrix into outputype vector
	}
}

OutputsBody OutputsBody::getOutputsBody()
{
	return *this;
}
