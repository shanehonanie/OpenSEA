#include "motionmodel.h"


MotionModel::MotionModel()
{
}


MotionModel::~MotionModel()
{
}

BodyWithForceMatrix MotionModel::setBodyData(Body bodyDataIn, UserForces userForcesIn) //Assume 6DOF only
{
	BodyWithForceMatrix newBodyMatrix;

	newBodyMatrix.userReactiveForce = bodyDataIn.userReactiveForce;
	newBodyMatrix.userActiveForce = bodyDataIn.userActiveForce;
	newBodyMatrix.userCrossBodyForces = bodyDataIn.crossBodyForces;

	//Body Mass Matrix
	cx_mat temp(6,6);
	newBodyMatrix.massMatrix = temp;
	newBodyMatrix.massMatrix(0,0) = bodyDataIn.mass;
	newBodyMatrix.massMatrix(1,1) = bodyDataIn.mass;
	newBodyMatrix.massMatrix(2,2) = bodyDataIn.mass;
	newBodyMatrix.massMatrix(3,3) = bodyDataIn.momentOfInertiaXX;
	newBodyMatrix.massMatrix(4,3) = bodyDataIn.crossMomentOfInertiaXY;
	newBodyMatrix.massMatrix(5,3) = bodyDataIn.crossMomentOfInertiaXZ;
	newBodyMatrix.massMatrix(3,4) = bodyDataIn.crossMomentOfInertiaXY;
	newBodyMatrix.massMatrix(4,4) = bodyDataIn.momentOfInertiaYY;
	newBodyMatrix.massMatrix(5,4) = bodyDataIn.crossMomentOfInertiaYZ;
	newBodyMatrix.massMatrix(3,5) = bodyDataIn.crossMomentOfInertiaXZ;
	newBodyMatrix.massMatrix(4,5) = bodyDataIn.crossMomentOfInertiaYZ;
	newBodyMatrix.massMatrix(5,5) = bodyDataIn.momentOfInertiaZZ;

	//active matrix(s)
	for(int i = 0; i < newBodyMatrix.userActiveForce.size(); i++)
	{
		vector<complexDouble> temp = userForcesIn.getActiveForce(newBodyMatrix.userActiveForce[i]);

		if (temp.size() > 0)
		{
			cx_mat coeffFound(temp);
			newBodyMatrix.userActiveForceMatrix.push_back(coeffFound);
		}
		else
			break;
	}

	//reactive matrix(s)
	for(int i = 0; i < newBodyMatrix.userReactiveForce.size(); i++)
	{
		vector<Derivative> temp = userForcesIn.getReactiveForce(newBodyMatrix.userReactiveForce[i]);

		if(temp.size() > 0)
		{
			ReactiveForceMatrix tempReactiveMatrix(temp);
			newBodyMatrix.userReactiveForceMatrix.push_back(tempReactiveMatrix);
		}
	}

	//CrossBody matrix(s)
	for(int i = 0; i < newBodyMatrix.userCrossBodyForces.size(); i++) 
	{
		vector<Derivative> temp = userForcesIn.getCrossBodyForce(newBodyMatrix.userCrossBodyForces[i]);

		if(temp.size() > 0)
		{
			ReactiveForceMatrix tempCrossBodyMatrix(temp);
			newBodyMatrix.userCrossBodyForceMatrix.push_back(tempCrossBodyMatrix);
		}
	}

	return newBodyMatrix;
}

