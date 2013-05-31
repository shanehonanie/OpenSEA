#ifndef MOTIONSOLVER_H
#define MOTIONSOLVER_H
#include <complex>
#include "armadillo"
#include "body.h"
#include "bodywithsolution.h"
#include "userforces.h"
#include "motionmodel.h"
#include "bodywithforcematrix.h"
#pragma comment( lib, "lapack_win32_MT" ) //include lappack
#pragma comment( lib, "blas_win32_MT" ) //include blas

using namespace arma;
using namespace std;

class MotionSolver
{
public:
	MotionSolver(vector<Body>, UserForces, double);
	~MotionSolver();
	vector<Body> theBodyData; //original body data from input files
	UserForces theForcesData; //original force data from input files
	vector<BodyWithForceMatrix> theBodyWithForceMatrix; //Body with Force Coefficients 
	void setMatrixIndexPositions(int,int);

	vector<cx_mat> sumReactiveForceEachSet(vector<ReactiveForceMatrix>); 
	cx_mat sumActiveForceEachSet(vector<cx_mat>);
	cx_mat sumDerivatives(vector<cx_mat>); //sum derivatives order 0-2 into 1 value
	vector<cx_mat> CalculateOutputs();

	MotionModel theMotionModel;
	double curWaveFrequency;
	int maxMatrixSize;

	//Global Matrices
	cx_mat reactiveForceMatrixGlobal; //A Matrix
	cx_mat activeForceMatrixGlobal;   //F Matrix
	cx_mat solutionColumnMatrix;	  //X Matrix

private:
	int body1ReactivePos[2];
	int body1CrossPos1[2];
	int body1CrossPos2[2];
	int body2ReactivePos[2];
	int body2CrossPos1[2];
	int body2CrossPos2[2];
	int body3ReactivePos[2];
	int body3CrossPos1[2];
	int body3CrossPos2[2];
};
#endif
