#ifndef BODY_H
#define BODY_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Body
{
public:
	Body();
	~Body();
private:
	string bodyName;
	string hydroBody;
	double heading;
	string motionModel;
	vector<string> userAciveForce;
	vector<string> userReactiveForce;
	vector<string> crossBodyForce;
	string linkedBody;

	struct Mass
	{
		double mass;
		double momentOfInertiaXX; //Ixx
		double momentOfInertiaYY; //Iyy
		double momentOfInertiaZZ; //Izz
		double crossMomentOfInertiaXY;
		double crossMomentOfInertiaXZ;
		double crossMomentOfInertiaYZ;
	};

	struct CenterOfGravity
	{
		double centroidX;
		double centroidY;
		double centroidZ;
	};
};
#endif
