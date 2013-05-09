#include "forceequation.h"


Equation::Equation()
{
	initCoeff();
}


Equation::~Equation()
{
}
void Equation::initCoeff()
{
	for(int i = 0 ; i < MAX_COEFFICIENTS; i++)
		coefficients[i] = 0;
}


//void Equation::setCoeff(vector<string> newList, bool isDirectList)
//{
//	if (isDirectList)
//	{
//		for(int i = 0; i < newList.size()/2; i++)
//			coefficients[atoi(newList[i].c_str())] = newList[i+1];
//	}
//	else 
//	{
//		for(int i = 0; i < MAX_COEFFICIENTS; i++)
//			coefficients[i] = newList[i];
//	}
//}

void Equation::testPrint()
{
	cout << "Coefficients" << endl;
	for(int i = 0; i < MAX_COEFFICIENTS; i++)
		cout << "[" << i+1 << "]: " << coefficients[i] << endl;
}

int Equation::getCoefficientListSize()
{
	return MAX_COEFFICIENTS;
}
