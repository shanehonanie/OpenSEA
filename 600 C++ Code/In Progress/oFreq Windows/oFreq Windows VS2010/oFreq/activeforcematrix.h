#ifndef ACTIVEEFORCEMATRIX_H
#define ACTIVEEFORCEMATRIX_H
#include <complex>
#include "armadillo"

using namespace arma;
using namespace std;

class ActiveForceMatrix
{
public:
	ActiveForceMatrix();
	~ActiveForceMatrix();
	cx_mat coefficients;
};
#endif

