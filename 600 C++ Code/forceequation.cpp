#include "forceequation.h"


Equation::Equation()
{
}


Equation::~Equation()
{
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

