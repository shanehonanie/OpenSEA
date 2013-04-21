#ifndef FORCEDERIVATIVE_H
#define FORCEDERIVATIVE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Derivative
{
public:
	Derivative();
	~Derivative();
private:
	int order;
	vector<double> coefficient;
};
#endif

