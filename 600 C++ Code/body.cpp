#include "body.h"


Body::Body()
{
}


Body::~Body()
{
}

void Body::testPrint()
{
	cout << "bodyName: " << bodyName << endl;
	cout << "hydrobody: " << hydroBody << endl;
	cout << "heading: " << heading << endl;
	cout << "motionModel: " << motionModel << endl;
	cout << "mass: " << mass << endl;
	cout << "ixx: " << momentOfInertiaXX << endl; //Ixx
	cout << "iyy: " << momentOfInertiaYY << endl; //Iyy
	cout << "izz: " << momentOfInertiaZZ << endl; //Izz
	cout << "ixy: " << crossMomentOfInertiaXY << endl;
	cout << "ixz" << crossMomentOfInertiaXZ << endl;
	cout << "iyz: " << crossMomentOfInertiaYZ << endl;
	cout << "centroidX: " << centroidX << endl;
	cout << "centroidY: " << centroidY << endl;
	cout << "centroidZ: " << centroidZ << endl;
	for(int i = 0 ;i < userActiveForce.size(); i++)
		cout << "activeForce[" << i << "]: " << userActiveForce[i] << endl;
	for(int i = 0 ;i < userReactiveForce.size(); i++)
		cout << "reactiveForce[" << i << "]: " << userReactiveForce[i] << endl;
	cout << "linkedBody: " << linkedBody << endl;
	cout << "crossBodyForceName: " << crossBodyName << endl;
	//for(int i = 0 ;i < crossBodyForces.size(); i++)
	//	cout << "crossBodyForce[" << i << "]: " << crossBodyForces[i] << endl;
}

void Body::setBodyName(string newName)
{
	bodyName = newName;
}

void Body::setHydroBodyName(string newName)
{
	hydroBody = newName;
}

void Body::setHeading(double newHeading)
{
	heading = newHeading;
}

void Body::setMotionModel(string newMotionModel)
{
	motionModel = newMotionModel;
}

void Body::setUserActiveForces(vector<string> newForceList)
{
	userActiveForce = newForceList;
}

void Body::setUserReactiveForces(vector<string> newForceList)
{
	userReactiveForce = newForceList;
}

void Body::setUserCrossBodyForces(vector<string> newForceList)
{
	userCrossBodyForces = newForceList;
}

void Body::setHydroActiveForces(vector<string> newForceList)
{
	hydroActiveForce = newForceList;
}

void Body::setHydroReactiveForces(vector<string> newForceList)
{
	hydroReactiveForce = newForceList;
}

void Body::setHydroCrossBodyForces(vector<string> newForceList)
{
	hydroCrossBodyForces = newForceList;
}

void Body::setLinkedBody(string newLinkedBody)
{
	linkedBody = newLinkedBody;
}

void Body::setMass(double newMass)
{
	mass = newMass;
}

void Body::setMomentXX(double newXX)
{
	momentOfInertiaXX = newXX;
}

void Body::setMomentYY(double newYY)
{
	momentOfInertiaYY = newYY;
}

void Body::setMomentZZ(double newZZ)
{
	momentOfInertiaZZ = newZZ;
}

void Body::setCrossMomentXY(double newXY)
{
	crossMomentOfInertiaXY = newXY;
}

void Body::setCrossMomentXZ(double newXZ)
{
	crossMomentOfInertiaXZ = newXZ;
}

void Body::setCrossMomentYZ(double newYZ)
{
	crossMomentOfInertiaYZ = newYZ;
}

void Body::setCentroidX(double newCenX)
{
	centroidX = newCenX;
}

void Body::setCentroidY(double newCenY)
{
	centroidY = newCenY;
}

void Body::setCentroidZ(double newCenZ)
{
	centroidZ = newCenZ;
}

void Body::setCrossBodyName(string newName)
{
	crossBodyName = newName;
}

string Body::getMotionModel()
{
	return motionModel;
}
