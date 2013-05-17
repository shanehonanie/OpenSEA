#include "forcecrossbody.h"


ForceCrossBody::ForceCrossBody() : ForceReactive()
{
}


ForceCrossBody::~ForceCrossBody()
{
}

void ForceCrossBody::testPrint()
{
	cout << "##Cross-Body Forces##" << endl;
	cout << "Name: " << forceName << endl;
	for(int i = 0l; i < MAX_ORDER_DERIVATIVE; i++)
	{
		cout << "Derivative Order#: " << i << endl;
		derivative[i].testPrint();
	}
	cout<< endl;
}


