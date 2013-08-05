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

#include "globalsolution.h"


GlobalSolution::GlobalSolution() : OutputDerived(), orderDerivative(-1)
{
}


GlobalSolution::~GlobalSolution()
{
}

cx_mat GlobalSolution::calculateOutput(cx_mat matrixIn, double curWaveFreq)
{
	cx_mat newMatrix(matrixIn.n_rows,1);
	complexDouble compI(0,1); //comlex number w/ 0 real, 1 imaginary used below for computations

	for(unsigned int i = 0; i < matrixIn.n_rows; i++)
	{
		newMatrix[i] = pow(curWaveFreq, orderDerivative) * pow(compI, orderDerivative) * matrixIn[i];
	}
	return newMatrix;
}
