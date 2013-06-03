#ifndef BODYWITHFORCEMATRIX_H
#define BODYWITHFORCEMATRIX_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include "armadillo"
#include "body.h"
#include "forcederivative.h"
#include "reactiveforcematrix.h"
#include "activeforcematrix.h"
#include "userforces.h"

using namespace arma;
using namespace std;

/**
 * This class holds all data for a body and related force matrices.
 */

typedef complex<double> complexDouble;

class BodyWithForceMatrix
{
public: 
	BodyWithForceMatrix(); /**< The default constructor. */

	/**
	 * The Constructor. Not used.
	 * @param bodyIn The body.
	 * @param The forces list.
	 */
	BodyWithForceMatrix(Body, UserForces); 
	~BodyWithForceMatrix(); /**< The default destructor, nothing happens here. */
	
	//Body Mass Matrix
	cx_mat massMatrix; /**< The Mass Matrix. */

	//User Force Coefficient Matrices
	vector<ReactiveForceMatrix> userReactiveForceMatrix; /**< List of user reactive force matrices. */
	vector<ReactiveForceMatrix> userCrossBodyForceMatrix; /**< List of user cross body force matrices. */
	vector<cx_mat> userActiveForceMatrix; /**< List of user active force matrices. */

	//Hydro Force Coefficient Matrices
	vector<ReactiveForceMatrix> hydroReactiveForceMatrix; /**< List of hydro reactive force matrices. */
	vector<ReactiveForceMatrix> hydroCrossBodyForceMatrix; /**< List of hydro cross body force matrices. */
	vector<cx_mat> hydroActiveForceMatrix; /**< List of hydro active force matrices. */

	//Hold the names of the Force Matrices which correspond to the above data structures
	vector<string> userActiveForce; /**< The name of the user active forces in the matrices list. */
	vector<string> userReactiveForce; /**< The name of the user reactive forces in the matrices list. */
	vector<string> userCrossBodyForces; /**< The name of the user cross body forces in the matrices list. */
	vector<string> hydroActiveForce; /**< The name of the hydro active forces in the matrices list. */
	vector<string> hydroReactiveForce; /**< The name of the hydro reactive forces in the matrices list. */
	vector<string> hydroCrossBodyForces; /**< The name of the hydro cross body forces in the matrices list. */
};
#endif
