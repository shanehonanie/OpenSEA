#include "forcereactive.h"


ForceReactive::ForceReactive() : Force()
{
}


ForceReactive::~ForceReactive()
{
}

void ForceReactive::setCurDerivative(int newOrder)
{
	currentDerivative = newOrder;
}

void ForceReactive::setCurEquationNum(int newEquationNum)
{
	currentEquation = newEquationNum -1;
}


void ForceReactive::setCoeff(vector<string> newList, bool isDirectList)
{
	if(isDirectList) //key value pair
	{
		for(int i = 0; i <= newList.size()/2; i+=2)
		{
			derivative[currentDerivative].equationList[currentEquation].
			coefficients[atoi(newList[i].c_str())-1] = newList[i+1];
		}
	}
	else //is sequential
	{
		for(int i = 0; i < MAX_COEFFICIENTS; i++)
			derivative[currentDerivative].equationList[currentEquation].
			coefficients[i] = newList[i];
	}
}

void ForceReactive::testPrint()
{
	
	cout << "##Reactive Forces##" << endl;
	cout << "Name: " << forceName << endl;
	for(int i = 0l; i < MAX_ORDER_DERIVATIVE; i++)
	{
		cout << "Derivative Order#: " << i << endl;
		derivative[i].testPrint();
	}
	cout<< endl;
}
