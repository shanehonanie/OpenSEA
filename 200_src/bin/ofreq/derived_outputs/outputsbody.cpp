/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

//License
/*-------------------------------------------------------------------------------------------------------------------*\
 *Copyright Datawave Marine Solutions, 2013.
 *This file is part of OpenSEA.

 *OpenSEA is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *OpenSEA is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with OpenSEA.  If not, see <http://www.gnu.org/licenses/>.
\*-------------------------------------------------------------------------------------------------------------------*/

#include "outputsbody.h"


OutputsBody::OutputsBody(BodyWithSolution bodyIn, vector<double> frequenciesIn) : theBody(bodyIn), frequencies(frequenciesIn)
{}


OutputsBody::~OutputsBody()
{}

void OutputsBody::calculateOutputs()
{
	GlobalMotion theGlobalMotion;
	GlobalVelocity theGlobalVelocity;
	GlobalAcceleration theGlobalAcceleration;

	for(unsigned int i = 0; i < frequencies.size(); i++)//iterate through loop and create vector for each frequency
	{
		cx_mat temp(theBody.solutionMatrix[i].n_rows, GLOBAL_SIZE); //create a marix that is size of solution matrix by 3 (6dof is 6x3)
		temp.submat(0,0, (theBody.solutionMatrix[i].n_rows-1), 0) = theGlobalMotion.calculateOutput(theBody.solutionMatrix[i], frequencies[i]); //calculate motion
		temp.submat(0,1, (theBody.solutionMatrix[i].n_rows-1), 1) = theGlobalVelocity.calculateOutput(theBody.solutionMatrix[i], frequencies[i]);  //calculate acceleration
		temp.submat(0,2, (theBody.solutionMatrix[i].n_rows-1), 2) = theGlobalAcceleration.calculateOutput(theBody.solutionMatrix[i], frequencies[i]); //calculate velocity
		outputList.push_back(temp); //put the 6x3 matrix into outputList vector
	}
}

vector<cx_mat> OutputsBody::getOutputType(int classType)
{
	vector<cx_mat> newOutputsBody;

	for(unsigned int i = 0; i < outputList.size(); i++)
	{
		cx_mat singleClassInstance = outputList[i].submat(0, classType, (outputList[i].n_rows-1), classType);
		newOutputsBody.push_back(singleClassInstance);
	}

	return newOutputsBody;
}

vector<cx_mat> OutputsBody::getOutputList()
{
	return outputList;
}
