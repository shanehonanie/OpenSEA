#ifndef FORCEEQUATION_H
#define FORCEEQUATION_H
#include "forcederivative.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_DERIVATIVE = 3;

class Equation
{
public:
	Equation();
	~Equation();
private:
	int equationNumber;
	Derivative derivative[MAX_DERIVATIVE];
};
#endif