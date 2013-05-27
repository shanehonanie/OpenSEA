#ifndef BODY_H
#define BODY_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "armadillo"

using namespace std;
using namespace arma;

class Body
{
public:
	Body();
	~Body();

	void testPrint();
	void setBodyName(string);
	void setHydroBodyName(string);
	void setHeading(double);
	void setMotionModel(string);
	void setUserActiveForces(vector<string>);
	void setUserReactiveForces(vector<string>);
	void setUserCrossBodyForces(vector<string>);
	void setHydroActiveForces(vector<string>);
	void setHydroReactiveForces(vector<string>);
	void setHydroCrossBodyForces(vector<string>);
	void addLinkedBody(string);
	void setMass(double);
	void setMomentXX(double);
	void setMomentYY(double);
	void setMomentZZ(double);
	void setCrossMomentXY(double);
	void setCrossMomentXZ(double);
	void setCrossMomentYZ(double);
	void setCentroidX(double);
	void setCentroidY(double);
	void setCentroidZ(double);
	void setCrossBodyName(string);
	vector<string> userActiveForce;
	vector<string> userReactiveForce;
	vector<string> userCrossBodyForces;
	vector<string> hydroActiveForce;
	vector<string> hydroReactiveForce;
	vector<string> hydroCrossBodyForces;
	vector<string> linkedBody;
	string getMotionModel();
	Body getBody();

	//should be private
	string bodyName;
	string hydroBody;
	double heading;
	string motionModel;
	
	double mass;
	double momentOfInertiaXX; //Ixx
	double momentOfInertiaYY; //Iyy
	double momentOfInertiaZZ; //Izz
	double crossMomentOfInertiaXY;
	double crossMomentOfInertiaXZ;
	double crossMomentOfInertiaYZ;
	double centroidX;
	double centroidY;
	double centroidZ;

	cx_mat getSolutionMatrix() const;
	cx_mat solutionMatrix;

private:
	
};
#endif
