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

#include "equation.h"

//------------------------------------------Function Separator --------------------------------------------------------
Equation::Equation()
{
	initCoeff();

    //Initialize default value of the data index
    pDataIndex = -1;
}

//------------------------------------------Function Separator --------------------------------------------------------
Equation::Equation(int IndexIn)
{
    //Initialize with Data Index.
    Equation();
    pDataIndex = IndexIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
Equation::~Equation()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
void Equation::testPrint()
{
    cout << "Coefficients" << endl;
    for(unsigned int i = 0; i < pcoeffs.size(); i++)
        cout << "[" << i+1 << "]: " << pcoeffs[i] << endl;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<double> &Equation::Coefficients()
{
    //Return pointer to the list of coefficients.
    return pcoeffs;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Equation::getCoefficient(int number)
{
    //Return the coefficient at the specified number.
    return pcoeffs[number];
}

//------------------------------------------Function Separator --------------------------------------------------------
void Equation::setCoefficient(int number, double coeffIn)
{
    //Set the coefficient at the specified number
    pcoeffs[number] = coeffIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
int Equation::getCoefficientListSize()
{
    return pcoeffs.size();
}

//------------------------------------------Function Separator --------------------------------------------------------
void Equation::setDataIndex(int index)
{
    pDataIndex = index;
}

//------------------------------------------Function Separator --------------------------------------------------------
int Equation::getDataIndex()
{
    return pDataIndex;
}

//------------------------------------------Function Separator --------------------------------------------------------
int &Equation::DataIndex()
{
    return pDataIndex;
}

//==========================================Section Separator =========================================================
//Private Functions

//------------------------------------------Function Separator --------------------------------------------------------
void Equation::initCoeff()
{
    for(unsigned int i = 0 ; i < pcoeffs.size(); i++)
        pcoeffs[i] = 0;
}
