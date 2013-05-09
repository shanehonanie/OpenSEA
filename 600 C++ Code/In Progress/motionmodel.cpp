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
	/*vector<ReactiveForceMatrix> userReactiveForceMatrix;
	vector<ReactiveForceMatrix> userCrossBodyForceMatrix;*/

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

/////////////////////////////
//void BodyWithForceMatrix::setData(Body bodyIn, UserForces userForcesIn)
//{
	//userReactiveForce = bodyIn.userReactiveForce;
	//userActiveForce = bodyIn.userActiveForce;
	//userCrossBodyForces = bodyIn.crossBodyForces;

	////mass matrix
	//cx_mat temp(6,6);
	//massMatrix = temp;
	//massMatrix(0,0) = bodyIn.mass;
	//massMatrix(1,1) = bodyIn.mass;
	//massMatrix(2,2) = bodyIn.mass;
	//massMatrix(3,3) = bodyIn.momentOfInertiaXX;
	//massMatrix(4,3) = bodyIn.crossMomentOfInertiaXY;
	//massMatrix(5,3) = bodyIn.crossMomentOfInertiaXZ;
	//massMatrix(3,4) = bodyIn.crossMomentOfInertiaXY;
	//massMatrix(4,4) = bodyIn.momentOfInertiaYY;
	//massMatrix(5,4) = bodyIn.crossMomentOfInertiaYZ;
	//massMatrix(3,5) = bodyIn.crossMomentOfInertiaXZ;
	//massMatrix(4,5) = bodyIn.crossMomentOfInertiaYZ;
	//massMatrix(5,5) = bodyIn.momentOfInertiaZZ;

	//massMatrix.print("Mass Matrix");

	//active matrix(s)
//	for(int i = 0; i < userActiveForce.size(); i++)
//	{
//		vector<complexDouble> temp = userForcesIn.getActiveForce(userActiveForce[i]);
//
//		if (temp.size() > 0)
//		{
//			cx_mat coeffFound(temp);
//			userActiveForceMatrix.push_back(coeffFound);
//		}
//		else
//			break;
//	}
//	/*vector<ReactiveForceMatrix> userReactiveForceMatrix;
//	vector<ReactiveForceMatrix> userCrossBodyForceMatrix;*/
//
//	//reactive matrix(s)
//	for(int i = 0; i < userReactiveForce.size(); i++)
//	{
//		vector<Derivative> temp = userForcesIn.getReactiveForce(userReactiveForce[i]);
//
//		if(temp.size() > 0)
//		{
//			ReactiveForceMatrix tempReactiveMatrix(temp);
//			userReactiveForceMatrix.push_back(tempReactiveMatrix);
//		}
//	}
//
//	//CrossBody matrix(s)
//	for(int i = 0; i < userCrossBodyForces.size(); i++) 
//	{
//		vector<Derivative> temp = userForcesIn.getCrossBodyForce(userCrossBodyForces[i]);
//
//		if(temp.size() > 0)
//		{
//			ReactiveForceMatrix tempCrossBodyMatrix(temp);
//			userCrossBodyForceMatrix.push_back(tempCrossBodyMatrix);
//		}
//	}
//}

