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

typedef complex<double> complexDouble;

class BodyWithForceMatrix
{
public:
	BodyWithForceMatrix();
	BodyWithForceMatrix(Body, UserForces);
	~BodyWithForceMatrix();
	
	cx_mat massMatrix;
	vector<ReactiveForceMatrix> userReactiveForceMatrix;
	vector<ReactiveForceMatrix> userCrossBodyForceMatrix;
	vector<cx_mat> userActiveForceMatrix;
	vector<string> userActiveForce;
	vector<string> userReactiveForce;
	vector<string> userCrossBodyForces;
	//void setData(Body, UserForces);
private:

};
#endif
