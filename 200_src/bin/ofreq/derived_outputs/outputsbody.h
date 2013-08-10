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
#ifndef OUTPUTSBODY_H
#define OUTPUTSBODY_H
#include <vector>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif
#include "globalacceleration.h"
#include "globalmotion.h"
#include "globalvelocity.h"

using namespace std;
using namespace arma;

const int GLOBAL_MOTION = 0; /**< Used for referencing Global Motion*/
const int GLOBAL_VELOCITY = 1; /**< Used for referencing Global Velocity*/
const int GLOBAL_ACCELERATION = 2; /**< Used for referencing Global Acceleraion*/
const int GLOBAL_SIZE = 3; /**< The number of Global Solution Types to be included in calculations*/

/**
 * This class holds the global solutions for all frequncies for a single body object.
 */

class OutputsBody
{
public:

	/**
	 * Constructor Creates a new OutputsBodyObject and sets the BodyWithSolution and waveFrequencies.
	 * @param bodyIn Sets BodyWithSolutionObject.
	 * @param Sets the List of wave frequencies.
	 */
    OutputsBody(Body, vector<double>);
	~OutputsBody(); /**< The default destructor, nothing happens here. */

    Body theBody; /**< Holds object that has body name and solutions. */
	vector<double> frequencies; /**< The list of wave frequencies to be used. */

	/**
	 * Retrieve a matrix of only one type of Global Solution.
	 * @param classype This specifies the index used to retrieve one of the Global Solutions.
	 * @return Matrix of one type Global Solutions, each index represents different frquency.
	 */
	vector<cx_mat> getOutputType(int);

	/**
	 * Retrieve a matrix of all types of Global Solution types.
	 * @return Matrix that has all Global solution types, each column is seperate class type, each index seperate frequency.
	 */
	vector<cx_mat> getOutputList();

	void calculateOutputs(); /**< Calculate SOlutions for eahc class type and frequency */

private:
	vector<cx_mat> outputList; /**< Each index is a cx_mat, each column matrix is a different global type, 0- Mot, 1 - acc, 2 - vel */
};
#endif
