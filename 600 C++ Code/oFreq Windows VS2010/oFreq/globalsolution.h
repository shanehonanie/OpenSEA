#ifndef GLOBALSOLUTION_H
#define GLOBALSOLUTION_H
#include "outputderived.h"
#include "armadillo"

using namespace std;
using namespace arma;

const int GLOBAL_MOTION_DERIVATIVE = 0;
const int GLOBAL_VELOCITY_DERIVATIVE = 1;
const int GLOBAL_ACCELERATION_DERIVATIVE = 2;

typedef complex<double> complexDouble;

class GlobalSolution : public OutputDerived
{
public:
	GlobalSolution();
	~GlobalSolution();
	int orderDerivative;
	virtual cx_mat calculateOutput(cx_mat,double);
};
#endif
