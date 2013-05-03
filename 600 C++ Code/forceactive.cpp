#include "forceactive.h"


ForceActive::ForceActive(): Force()
{
}


ForceActive::~ForceActive()
{
}

void ForceActive::setCoeff(vector<string> theListIn, bool isDirectList)
{
	complexDouble newComplexNumber;

	for(int i = 0 ; i < MAX_COEFFICIENTS; i++)
	{
		if(theListIn[i].find("<") == std::string::npos) //expression in rectangular form
			newComplexNumber = convertRectangularFormToComplexNumber(theListIn[i]);
		else //expression in polar form
			newComplexNumber = convertPolarFormToComplexNumber(theListIn[i]);

		coefficients[i] = newComplexNumber;
	}
}

void ForceActive::testPrint()
{
	cout << "#Active Forces##" << endl;
	cout << "Name: " << forceName << endl;
	for(int i = 0; i < MAX_COEFFICIENTS; i++)
	{
		cout << "Equation [" << i+1 << "]: " << coefficients[i] << endl;
	}
	cout<< endl;
}

complexDouble ForceActive::convertRectangularFormToComplexNumber(string expression)
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

complexDouble ForceActive::convertPolarFormToComplexNumber(string expression)
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

