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

#include "matactiveforce.h"

//------------------------------------------Function Separator --------------------------------------------------------
matActiveForce::matActiveForce()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
matActiveForce::~matActiveForce()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
matActiveForce matActiveForce::operator+(const matActiveForce &forceOther)
{
    //Add two force objects together.
    matActiveForce output;

    //Find max size
    int maxsize;

    if (this->getMatSize() > forceOther.getMatSize())
        maxsize = this->getMatSize();
    else
        maxsize = forceOther.getMatSize();

    //Resize matrix and initialize with zeros.
    output.pCoeff.zeros(maxsize,1);

    //Iterate through matrix and add the two together.
    for (int i = 0; i < pCoeff.n_rows; i++)
    {
        output.pCoeff(i,1) = pCoeff(i,1) + forceOther.pCoeff(i,1);
    }

    //Write output
    return output;

    //cleanup
    delete output;
    delete maxsize;
}

//------------------------------------------Function Separator --------------------------------------------------------
matActiveForce matActiveForce::operator-(const matActiveForce &forceOther)
{
    //Add two force objects together.
    matActiveForce output;

    //Find max size
    int maxsize;

    if (this->getMatSize() > forceOther.getMatSize())
        maxsize = this->getMatSize();
    else
        maxsize = forceOther.getMatSize();

    //Resize matrix and initialize with zeros.
    output.pCoeff.zeros(maxsize,1);

    //Iterate through matrix and add the two together.
    for (int i = 0; i < pCoeff.n_rows; i++)
    {
        output.pCoeff(i,1) = pCoeff(i,1) - forceOther.pCoeff(i,1);
    }

    //Write output
    return output;

    //cleanup
    delete output;
    delete maxsize;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat &matActiveForce::Coefficients()
{
    return pCoeff;
}

//------------------------------------------Function Separator --------------------------------------------------------
void matActiveForce::setId(int num)
{
    pId = num;
}

//------------------------------------------Function Separator --------------------------------------------------------
int matActiveForce::getId()
{
    return pId;
}

//------------------------------------------Function Separator --------------------------------------------------------
int matActiveForce::getMatSize()
{
    return pCoeff.n_rows;
}
