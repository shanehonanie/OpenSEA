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

#include "derivative.h"

//------------------------------------------Function Separator ----------------------------------------------------
Derivative::Derivative()
{
}

//------------------------------------------Function Separator ----------------------------------------------------
Derivative::~Derivative()
{

}

//------------------------------------------Function Separator ----------------------------------------------------
void Derivative::testPrint()
{
	
    for(unsigned int i = 0; i < pEquationList.size(); i++)
	{
		cout << "Equation #: " << i+1 << endl;
		equationList[i].testPrint();
	}
}

//------------------------------------------Function Separator ----------------------------------------------------
vector<Equation> &Derivative::EquationList()
{
    //Return equation list pointer.
    return pEquationList;
}

//------------------------------------------Function Separator ----------------------------------------------------
vector<Equation> &Derivative::Equations()
{
    return this->EquationList();
}

//------------------------------------------Function Separator ----------------------------------------------------
Equation &Derivative::getEquation(int number)
{
    //Return pointer to the specified equation.
    return pEquationList[number];
}

//------------------------------------------Function Separator ----------------------------------------------------
int Derivative::getEquationListSize()
{
    return pEquationList.size();
}
