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

#include "forcereact.h"

//------------------------------------------Function Separator --------------------------------------------------------
forceReact::forceReact() : Force()
{}

//------------------------------------------Function Separator --------------------------------------------------------
forceReact::~forceReact()
{}

//------------------------------------------Function Separator --------------------------------------------------------
void forceReact::setCurDerivative(int newOrder)
{
	currentDerivative = newOrder;
}

//------------------------------------------Function Separator --------------------------------------------------------
void forceReact::setCurEquationNum(int newEquationNum)
{
	currentEquation = newEquationNum -1;
}

//------------------------------------------Function Separator --------------------------------------------------------
void forceReact::setCoeff(vector<string> newList, bool isDirectList)
{
	if(isDirectList) //key value pair
	{
		for(unsigned int i = 0; i <= newList.size()/2; i+=2)
		{
			derivative[currentDerivative].equationList[currentEquation].
			coefficients[atoi(newList[i].c_str())-1] = atof(newList[i+1].c_str());
		}
	}
	else //is sequential
	{
		for(unsigned int i = 0; i < MAX_COEFFICIENTS; i++)
			derivative[currentDerivative].equationList[currentEquation].
			coefficients[i] = atof(newList[i].c_str());
	}
}

//------------------------------------------Function Separator --------------------------------------------------------
void forceReact::testPrint()
{
	
	cout << "##Reactive Forces##" << endl;
	cout << "Name: " << forceName << endl;
    for(unsigned int i = 0l; i < derivative.size(); i++)
	{
		cout << "Derivative Order#: " << i << endl;
		derivative[i].testPrint();
	}
	cout<< endl;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<Derivative> &forceReact::getDerivatives()
{
    return derivative;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<Derivative> &forceReact::Derivatives()
{
    return this->getDerivatives();
}

//------------------------------------------Function Separator --------------------------------------------------------
Derivative &forceReact::getDerivative(int num)
{
    //Return the derivative object specified.
    //Value is a pointer to the derivative.

    return derivative[num];
}
