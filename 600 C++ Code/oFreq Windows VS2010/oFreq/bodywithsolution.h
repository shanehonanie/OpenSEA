#ifndef BODYWITHSOLUTION_H
#define BODYWITHSOLUTION_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "armadillo"

using namespace std;
using namespace arma;

class BodyWithSolution
{
public:
	BodyWithSolution(string);
	~BodyWithSolution();
	string bodyName;
	vector<cx_mat> solutionMatrix;
};
#endif
