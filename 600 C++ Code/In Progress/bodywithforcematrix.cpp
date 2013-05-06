#include "bodywithforcematrix.h"


BodyWithForceMatrix::BodyWithForceMatrix()
{
}

BodyWithForceMatrix::BodyWithForceMatrix(Body bodyIn, UserForces userForcesIn)
{
	setData(bodyIn, userForcesIn);
}


BodyWithForceMatrix::~BodyWithForceMatrix()
{
}

void BodyWithForceMatrix::setData(Body bodyIn, UserForces userForcesIn)
{
	userReactiveForce = bodyIn.userReactiveForce;
	userActiveForce = bodyIn.userActiveForce;
	userCrossBodyForces = bodyIn.crossBodyForces;

	//mass matrix
	cx_mat temp(6,6);
	massMatrix = temp;
	massMatrix(0,0) = bodyIn.mass;
	massMatrix(1,1) = bodyIn.mass;
	massMatrix(2,2) = bodyIn.mass;
	massMatrix(3,3) = bodyIn.momentOfInertiaXX;
	massMatrix(4,3) = bodyIn.crossMomentOfInertiaXY;
	massMatrix(5,3) = bodyIn.crossMomentOfInertiaXZ;
	massMatrix(3,4) = bodyIn.crossMomentOfInertiaXY;
	massMatrix(4,4) = bodyIn.momentOfInertiaYY;
	massMatrix(5,4) = bodyIn.crossMomentOfInertiaYZ;
	massMatrix(3,5) = bodyIn.crossMomentOfInertiaXZ;
	massMatrix(4,5) = bodyIn.crossMomentOfInertiaYZ;
	massMatrix(5,5) = bodyIn.momentOfInertiaZZ;

	//active matrix(s)
	for(int i = 0; i < userActiveForce.size(); i++)
	{
		vector<complexDouble> temp = userForcesIn.getActiveForce(userActiveForce[i]);

		if (temp.size() > 0)
		{
			cx_mat coeffFound(temp);
			userActiveForceMatrix.push_back(coeffFound);
		}
		else
			break;
	}
	/*vector<ReactiveForceMatrix> userReactiveForceMatrix;
	vector<ReactiveForceMatrix> userCrossBodyForceMatrix;*/

	//reactive matrix(s)
	for(int i = 0; i < userReactiveForce.size(); i++)
	{
		vector<Derivative> temp = userForcesIn.getReactiveForce(userReactiveForce[i]);

		if(temp.size() > 0)
		{
			ReactiveForceMatrix tempReactiveMatrix(temp);
			userReactiveForceMatrix.push_back(tempReactiveMatrix);
		}
	}

	//CrossBody matrix(s)
	for(int i = 0; i < userCrossBodyForces.size(); i++) 
	{
		vector<Derivative> temp = userForcesIn.getCrossBodyForce(userCrossBodyForces[i]);

		if(temp.size() > 0)
		{
			ReactiveForceMatrix tempCrossBodyMatrix(temp);
			userCrossBodyForceMatrix.push_back(tempCrossBodyMatrix);
		}
	}
}