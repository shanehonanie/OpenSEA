#ifndef FORCEDERIVATIVE_H
#define FORCEDERIVATIVE_H
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int MAX_EQUATIONS = 6;

class Derivative
{
public:
	Derivative();
	~Derivative();
	void testPrint();
	Equation equationList[MAX_EQUATIONS];
private:

};
#endif

