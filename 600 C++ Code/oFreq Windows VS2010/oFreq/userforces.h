#ifndef USERFORCES_H
#define USERFORCES_H
#include "forceactive.h"
#include "forcereactive.h"
#include "forcecrossbody.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef complex<double> complexDouble;

class UserForces
{
public:
	UserForces();
	~UserForces();
	void addNewForce(string);
	void setCoeff(vector<string>, bool); ///need to hange to double to handle complex numbers
	void setOrderDerivative(int);
	void setEquationNumber(int);
	void setCurForceAsActive();
	void setCurForceAsReactive();
	void setCurForceAsCrossBody();
	void testPrint();
	vector<complexDouble> getUserActiveForce(string);
	vector<Derivative> getUserReactiveForce(string);
	vector<Derivative> getUserCrossBodyForce(string);

private:
	vector<ForceActive> userActiveForces;
	vector<ForceReactive> userReactiveForces;
	vector<ForceCrossBody> userCrossBodyForces;
	int curForceType;
	//int curOrderDerivative;
	//int curEquationNum;
	int ACTIVE_FORCE;
	int REACTIVE_FORCE;
	int CROSSBODY_FORCE;
};
#endif
