#ifndef FORCEEQUATION_H
#define FORCEEQUATION_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_COEFFICIENTS = 6;

class Equation
{
public:
	Equation();
	~Equation();
	void testPrint();
	//void setCoeff(vector<string>, bool);
	string coefficients[MAX_COEFFICIENTS];
private:
	//int equationNumber;
};
#endif