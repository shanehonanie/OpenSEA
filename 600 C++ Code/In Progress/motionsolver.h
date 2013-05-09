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
	vector<Body> theBodyData; //original body data from input files
	UserForces theForcesData; //original force data from input files
	vector<BodyWithForceMatrix> theBodyWithForceMatrix; //Body with Force Coefficients

	vector<cx_mat> sumReactiveForceEachSet(vector<ReactiveForceMatrix>); 
	//cx_mat sumReactiveForceEachSetHelper(cx_mat[]); 

	cx_mat sumActiveForceEachSet(vector<cx_mat>);
	//cx_mat sumActiveForceEachSetHelper();

	cx_mat sumDerivatives(vector<cx_mat>); //sum derivatives order 0-2 into 1 value
	void CalculateOutputs();
	//void createNewBodyForceMatrix();

	MotionModel theMotionModel;


};
#endif
