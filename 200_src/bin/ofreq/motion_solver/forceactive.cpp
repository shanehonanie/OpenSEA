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

#include "forceactive.h"

//------------------------------------------Function Separator --------------------------------------------------------
forceActive::forceActive(): Force()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
forceActive::~forceActive()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
void forceActive::setCoeff(vector<string> theListIn, bool isDirectList)
{
	complexDouble newComplexNumber;

	for(unsigned int i = 0 ; i < MAX_COEFFICIENTS; i++)
	{
		if(theListIn[i].find("<") == std::string::npos) //expression in rectangular form
			newComplexNumber = convertRectangularFormToComplexNumber(theListIn[i]);
		else //expression in polar form
			newComplexNumber = convertPolarFormToComplexNumber(theListIn[i]);

		coefficients[i] = newComplexNumber;
	}
}

//------------------------------------------Function Separator --------------------------------------------------------
void forceActive::testPrint()
{
	cout << "#Active Forces##" << endl;
	cout << "Name: " << forceName << endl;
	for(unsigned int i = 0; i < MAX_COEFFICIENTS; i++)
	{
		cout << "Equation [" << i+1 << "]: " << coefficients[i] << endl;
	}
	cout<< endl;
}

//------------------------------------------Function Separator --------------------------------------------------------
complexDouble forceActive::convertRectangularFormToComplexNumber(string expression)
{
	char imaginaryChar = 'i';

	//index indicates where to split string for real and imaginary parts
	int index = expression.find("+"); 
	if(index == std::string::npos)
		index = expression.find("-");

	if(index == std::string::npos)
		return NULL; //return empty if expression not in proper format contain + or -

	//Complex Number must be input in one of the following forms
	//a+bi, a-bi, a+ib, a-ib
	double real = atof(expression.substr(0, index).c_str()); //real part is always first half of string
	string imagTemp = expression.substr(index); //get the rest of string which represents imaginary part
	imagTemp.erase(std::remove(imagTemp.begin(), imagTemp.end(), imaginaryChar), imagTemp.end()); //remove 'i' char from string
	double imaginary = atof(imagTemp.c_str()); //cast imaginary string to double

	complexDouble newComplexDouble(real , imaginary); //construct complex number with real & imaginary parts

	return newComplexDouble;
}

//------------------------------------------Function Separator --------------------------------------------------------
complexDouble forceActive::convertPolarFormToComplexNumber(string expression)
{
	char divider = '<';

	int index = expression.find(divider); //index represents location to split string

	if(index == std::string::npos)
		return NULL; //return empty if expression not in proper format contain + or -

	double magnitude = atof(expression.substr(0, index).c_str()); //magnitude is first half of string
	double phaseAngle = atof(expression.substr(index+1).c_str()); //phase angle is scong half of string

	complexDouble newComplexDouble = polar(magnitude, phaseAngle); //construct complex number from magnitude and phase angle

	return newComplexDouble;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<complexDouble> &forceActive::getCoefficients()
{
    return coefficients;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<complexDouble> &forceActive::Equations()
{
    return this->getCoefficients();
}

//------------------------------------------Function Separator --------------------------------------------------------
double forceActive::getEquation(int number)
{
    //Return the input coefficient for the equation specified.
    return coefficients[number];
}

