#ifndef FORCEACIVE_H
#define FORCEACTIVE_H
#include "force.h"
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
using namespace std;

typedef complex<double> complexDouble;

class ForceActive: public Force
{
public:
	ForceActive();
	~ForceActive();
	complexDouble convertRectangularFormToComplexNumber(string);
	complexDouble convertPolarFormToComplexNumber(string);
	void setCoeff(vector<string>, bool); 
	void testPrint();
	vector<complexDouble> getCoefficients();
protected:
	complexDouble coefficients[MAX_COEFFICIENTS];
};
#endif
