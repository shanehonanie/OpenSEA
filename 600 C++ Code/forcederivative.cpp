#include "forcederivative.h"


Derivative::Derivative()
{
}


Derivative::~Derivative()
{

}

void Derivative::testPrint()
{
	
	for(int i = 0; i < MAX_EQUATIONS; i++)
	{
		cout << "Equation #: " << i+1 << endl;
		equationList[i].testPrint();
	}
}
