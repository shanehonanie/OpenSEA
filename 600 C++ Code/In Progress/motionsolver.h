#ifndef MOTIONSOLVER_H
#define MOTIONSOLVER_H
#include <complex>
#include "armadillo"
#include "body.h"
#include "userforces.h"
#include "motionmodel.h"
#include "bodywithforcematrix.h"

using namespace arma;
using namespace std;

class MotionSolver
{
public:
	MotionSolver(vector<Body>, UserForces);
	~MotionSolver();
	vector<Body> theBodyData;
	UserForces theForcesData;
	vector<BodyWithForceMatrix> theBodyWithForceMatrix;
	cx_mat sumForceEachSet(vector<ReactiveForceMatrix>); //sum each order derivative and return single matrix
	cx_mat sumForceEachSetHelper(cx_mat[]);
	cx_mat sumDerivatives(cx_mat); //sum derivatives order 0-2 into 1 value
	void CalculateOutputs();
	//void createNewBodyForceMatrix();

	MotionModel theMotionModel;


};
#endif
