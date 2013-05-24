#ifndef MOTIONMODEL_H
#define MOTIONMODEL_H
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"
#include "equationofmotion_01.h"

using namespace arma;
using namespace std;

const string EQUATION_01 = "6dof"; //Equation Of Motion 01
const int EQUATION_01_SIZE = 6;


class MotionModel
{
public:
	MotionModel();
	BodyWithForceMatrix setBodyData(Body, UserForces);
	~MotionModel();
	void setWaveFrequencies(vector<double>);
	static int getMatrixSize(string);

	vector<double> theWaveFreq;
	
};
#endif

