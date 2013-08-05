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

#include "outputslist.h"

OutputsList::OutputsList(vector<BodyWithSolution> bodyIn, vector<double> directionsIn, vector<double> frequenciesIn) 
	: theBodyList(bodyIn), theFrequencyList(frequenciesIn), theDirectionList(directionsIn)
{}

OutputsList::OutputsList()
{}



OutputsList::~OutputsList()
{}

//Perform Calculations for all bodies
void OutputsList::calculateOutputs()
{
	for(unsigned int i = 0; i < theBodyList.size(); i++)
	{
		OutputsBody newOutputsBody(theBodyList[i], theFrequencyList);//create new OutputBody
		newOutputsBody.calculateOutputs();
		theOutputsBodyList.push_back(newOutputsBody); //add to the vector 
	}
}
