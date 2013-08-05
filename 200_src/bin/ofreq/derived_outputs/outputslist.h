/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date              Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15 2013       Shane Honanie       Initially created
 *
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



//######################################### Class Separator ###########################################################
#ifndef OUTPUTSLIST_H
#define OUTPUTSLIST_H
#include <vector>
#include "outputsbody.h"
using namespace std;

/**
 * This class holds the global solutions for all frequncies for all body object(s).
 */

class OutputsList
{
public:
	OutputsList(); /**< This default constructor creates a OutputsList object. */

	/**
	 * Overloaded constructor
	 * @param theBodyListIn All bodies with calculated solutions.
	 * @param directionIn List of all wave directions.
	 * @param frequenciesIn List of all frequencies.
	 */
	OutputsList(vector<BodyWithSolution>, vector<double>, vector<double>);
	~OutputsList(); /**< The default destructor, nothing happens here. */

	vector<OutputsBody> theOutputsBodyList; /**< List of each body with computed globlal matrices */
	vector<BodyWithSolution> theBodyList; /**< List of all bodies with soluions computed by motion solver */
	vector<double> theFrequencyList; /**< List of frequencies used. */
	vector<double> theDirectionList; /**< List of directions used. */
	void calculateOutputs(); /**< Calculate the Global Solutions for each body */
};
#endif
