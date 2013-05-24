#ifndef FORCEREACTIVE_H
#define FORCEREACTIVE_H
#include "force.h"
#include "forcederivative.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int MAX_ORDER_DERIVATIVE = 3;

class ForceReactive: public Force
{
public:
	ForceReactive();
	~ForceReactive();
	void setCoeff(vector<string>, bool); //int represents current order derivative
	void setCurDerivative(int);
	void setCurEquationNum(int);
	void testPrint();
	vector<Derivative> getDerivatives();
protected:
	Derivative derivative[MAX_ORDER_DERIVATIVE];
	int currentDerivative;
	int currentEquation;
	
};
#endif

