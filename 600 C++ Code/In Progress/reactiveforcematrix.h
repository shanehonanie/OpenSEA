#ifndef REACTICEFORCEMATRIX_H
#define REACTICEFORCEMATRIX_H
#include <complex>
#include "armadillo"
#include "forcederivative.h"

using namespace arma;
using namespace std;
//const int MAX_ORDER_DERIVATIVE = 3;

typedef complex<double> complexDouble;

class ReactiveForceMatrix
{
public:
	ReactiveForceMatrix();
	ReactiveForceMatrix(vector<Derivative>);
	~ReactiveForceMatrix();
	vector<cx_mat> derivativeMatrix;
	int getSize();
	

};
#endif


