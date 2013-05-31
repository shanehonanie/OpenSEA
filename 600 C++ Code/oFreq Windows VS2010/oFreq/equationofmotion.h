#ifndef EQUATIONOFMOTION_H
#define EQUATIONOFMOTION_H
#include <math.h>
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"

using namespace arma;
using namespace std;

class EquationOfMotion
{
public:
	EquationOfMotion();
	~EquationOfMotion();
	void setWaveFreq(double);
	virtual void setBodyData(Body, UserForces) = 0;
	BodyWithForceMatrix getBodyForceData();
	double kroneckerDelta(int, int);
	complexDouble timeDifferentiation(complexDouble, int); 
	BodyWithForceMatrix newBodyMatrix; 
private:
	double curWaveFreq;
};
#endif
