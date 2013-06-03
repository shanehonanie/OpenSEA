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

/**
 * This class holds data for the motion solver and performs calculations on all of the data to get the solution matrix.
 */

class MotionSolver
{
public:

	/**
	 * The constructor.
	 * @param bodyDataIn The body.
	 * @param userForcesIn The User Forces.
	 * @param newWaveFreq The wave frequencies.
	 */
	MotionSolver(vector<Body>, UserForces, double);
	~MotionSolver(); /**< The default destructor, nothing happens here. */

	vector<Body> theBodyData; /**< original body data from input files */
	UserForces theForcesData; /**< original force data from input files */
	vector<BodyWithForceMatrix> theBodyWithForceMatrix; /**< Body with Force Coefficients */

	/**
	 * Set the matrix index positions in the reactive force matrix.
	 * @param numBodies The number of bodies.
	 * @param perMatrixSize The roww/column length of matrix.
	 */
	void setMatrixIndexPositions(int,int);

	/**
	 * Sum Reactive forces for each set.
	 * @param theReactiveForceMatrix The Reactive force matrix.
	 * @return The sum of reactive force matrices.
	 */
	vector<cx_mat> sumReactiveForceEachSet(vector<ReactiveForceMatrix>); 

	/**
	 * Sum active forces for each set.
	 * @param theActiveForceMatrix The active force matrix.
	 * @return The sum of active force matrix.
	 */
	cx_mat sumActiveForceEachSet(vector<cx_mat>);

	/**
	 * Sum Derivatives for reactive force matrix.
	 * @param theReactiveForceMatrix The reactive force matrix.
	 * @return TSingle matrix that is the sum of Matrices passed in.
	 */
	cx_mat sumDerivatives(vector<cx_mat>); //sum derivatives order 0-2 into 1 value

	/**
	 * Calculate the Solution and return the solutions for each body.
	 * @return A list of solutions for each body.
	 */
	vector<cx_mat> CalculateOutputs();

	MotionModel theMotionModel; /**< The motion model. */
	double curWaveFrequency; /**< The current wave frequency */
	int maxMatrixSize; /**< The max row/column size of the matrix */

	//Global Matrices
	cx_mat reactiveForceMatrixGlobal; /**< A Matrix (Reactive Force Matrix Global)*/
	cx_mat activeForceMatrixGlobal;   /**< F Matrix (Active Force Matirx Global)*/
	cx_mat solutionColumnMatrix;	  /**< X Matrix (Solution Column Matrix)*/

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
