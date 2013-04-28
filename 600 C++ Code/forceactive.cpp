#include "forceactive.h"


ForceActive::ForceActive(): Force()
{
}


ForceActive::~ForceActive()
{
}

void ForceActive::setCoeff(vector<string> newListIn, bool isDirectList)
{
	for(int i = 0 ; i < MAX_COEFFICIENTS; i++)
		coefficients[i] = newListIn[i];
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