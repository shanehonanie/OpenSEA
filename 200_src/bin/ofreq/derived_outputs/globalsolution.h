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
#ifndef GLOBALSOLUTION_H
#define GLOBALSOLUTION_H
#include "outputderived.h"
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif


using namespace std;
using namespace arma;

const int GLOBAL_MOTION_DERIVATIVE = 0; /**< Used for referencing Global Motion Derivative */
const int GLOBAL_VELOCITY_DERIVATIVE = 1; /**< Used for referencing Global Velocity Derivative */
const int GLOBAL_ACCELERATION_DERIVATIVE = 2; /**< Used for referencing Global Acceleration Derivative */

typedef complex<double> complexDouble; /**< Simple typedef for complexDouble represents complex<double> */

/**
 * This class represents the Global Solution.
 */

class GlobalSolution : public OutputDerived
{
public:
	GlobalSolution(); /**< This default constructor creates a Global Solution object. */
	~GlobalSolution(); /**< The default destructor, nothing happens here. */
	int orderDerivative; /**< Set by child classes */

	/**
	 * Calculates the outputs for Global Solution children classes
	 * @param matrixIn The original Matrix that is used for calculations.
	 * @param curWaveFreq The current wave frequency.
	 * @return The new matrix with calculations on each index.
	 */
	virtual cx_mat calculateOutput(cx_mat,double);
};
#endif
