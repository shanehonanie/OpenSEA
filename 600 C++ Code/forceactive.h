#ifndef FORCEACIVE_H
#define FORCEACTIVE_H
#include "force.h"
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ForceActive: public Force
{
public:
	ForceActive();
	~ForceActive();
	void setCoeff(vector<string>, bool); 
	void testPrint();
protected:
	string coefficients[MAX_COEFFICIENTS];
};
#endif
