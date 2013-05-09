#ifndef MOTIONMODEL_H
#define MOTIONMODEL_H
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"

using namespace arma;
using namespace std;

class MotionModel
{
public:
	MotionModel();
	BodyWithForceMatrix setBodyData(Body, UserForces);
	~MotionModel();
};
#endif

