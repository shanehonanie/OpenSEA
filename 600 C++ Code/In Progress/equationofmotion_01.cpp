#include "equationofmotion_01.h"


EquationOfMotion_01::EquationOfMotion_01() : EquationOfMotion()
{
	bodyMassIndexs[0] = EQ_0_BM1;
	bodyMassIndexs[1] = EQ_0_BM2;
	bodyMassIndexs[2] = EQ_0_BM3;
	bodyMassIndexs[3] = EQ_0_BM4;
	bodyMassIndexs[4] = EQ_0_BM5;
}


EquationOfMotion_01::~EquationOfMotion_01()
{
}

void EquationOfMotion_01::setBodyData(Body bodyDataIn, UserForces userForcesIn) //Assume 6DOF only
{
	//User Force Matrices
	newBodyMatrix.userReactiveForce = bodyDataIn.userReactiveForce;
	newBodyMatrix.userActiveForce = bodyDataIn.userActiveForce;
	newBodyMatrix.userCrossBodyForces = bodyDataIn.userCrossBodyForces;

	//Hydro Force Matrices
	newBodyMatrix.hydroReactiveForce = bodyDataIn.hydroReactiveForce;
	newBodyMatrix.hydroActiveForce = bodyDataIn.hydroActiveForce;
	newBodyMatrix.hydroCrossBodyForces = bodyDataIn.hydroCrossBodyForces;

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

	//user active matrix(s)
	for(int i = 0; i < newBodyMatrix.userActiveForce.size(); i++)
	{
		vector<complexDouble> temp = userForcesIn.getUserActiveForce(newBodyMatrix.userActiveForce[i]);

		if (temp.size() > 0)
		{
			cx_mat coeffFound(temp);
			newBodyMatrix.userActiveForceMatrix.push_back(coeffFound);
		}
		else
			break;
	}

	//hydro active matrix(s)
	//for(int i = 0; i < newBodyMatrix.hydroActiveForce.size(); i++)
	//{
	//	vector<complexDouble> temp = userForcesIn.getActiveForce(newBodyMatrix.userActiveForce[i]);

	//	if (temp.size() > 0)
	//	{
	//		cx_mat coeffFound(temp);
	//		newBodyMatrix.userActiveForceMatrix.push_back(coeffFound);
	//	}
	//	else
	//		break;
	//}

	//user reactive matrices
	for(int i = 0; i < newBodyMatrix.userReactiveForce.size(); i++)
	{
		//Retrieve the User Reactive Force Object by passing in the name of force (string)
		vector<Derivative> temp = userForcesIn.getUserReactiveForce(newBodyMatrix.userReactiveForce[i]);

		if(temp.size() > 0) //if found then add to vector
		{
			//Convert to ReactiveForceMatrix object which converts and contains the force coefficients
			ReactiveForceMatrix tempReactiveMatrix(temp);

			//calculateEquations(tempReactiveMatrix);
			newBodyMatrix.userReactiveForceMatrix.push_back(tempReactiveMatrix);
		}
	}

	//user reactive matrix(s)
	//for(int i = 0; i < newBodyMatrix.userReactiveForce.size(); i++)
	//{
	//	//Retrieve the User Reactive Force Object by passing in the name of force (string)
	//	vector<Derivative> temp = userForcesIn.getUserReactiveForce(newBodyMatrix.userReactiveForce[i]);

	//	if(temp.size() > 0) //if found then add to vector
	//	{
	//		//convert the input force to force coeff then add to the vector which contains all User Reactive Forces
	//		ReactiveForceMatrix tempReactiveMatrix(temp);
	//		newBodyMatrix.userReactiveForceMatrix.push_back(tempReactiveMatrix);
	//	}
	//}

	//user CrossBody matrix(s)
	for(int i = 0; i < newBodyMatrix.userCrossBodyForces.size(); i++) 
	{
		vector<Derivative> temp = userForcesIn.getUserCrossBodyForce(newBodyMatrix.userCrossBodyForces[i]);

		if(temp.size() > 0)
		{
			ReactiveForceMatrix tempCrossBodyMatrix(temp);
			newBodyMatrix.userCrossBodyForceMatrix.push_back(tempCrossBodyMatrix);
		}
	}
}

//void EquationOfMotion_01::calculateEquations(ReactiveForceMatrix theReactiveForceMatrix)
//{
//	for(int i = 0; i < theReactiveForceMatrix.derivativeMatrix.size(); i++) //iterate through each order derivative (i)
//	{
//		for(int j = 0; j < theReactiveForceMatrix.derivativeMatrix[i].n_rows; j++) //iterate through each row
//		{
//			setBodyMassIndexs(j); //set indices for calls to BodyMass(x) depending on current equation
//			for(int k = 0; k < theReactiveForceMatrix.derivativeMatrix[i].n_cols; k++) //iterate through each row * col (cell)
//			{
//				complexDouble newVal = getBodyMassVal(j, bodyMassIndexs[0]) + getBodyMassVal(j, bodyMassIndexs[1]) + getBodyMassVal(j, bodyMassIndexs[2]) 
//					+ getBodyMassVal(j, bodyMassIndexs[3]) + getBodyMassVal(j, bodyMassIndexs[4])
//					//+HydroReactSum
//					+
//			}
//		}
//	}
//}

void EquationOfMotion_01::calculateEquations(BodyWithForceMatrix theBodyWithForceMatrices)
{
	//calculate user reactive force matrices
	for(int i = 0; i < theBodyWithForceMatrices.userReactiveForceMatrix.size(); i ++) //iterate through all user reacive force matrices
	{
		for(int j = 0; j < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix.size(); j++) //iterate through each order derivative
		{
			for(int k = 0; k < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix[j].n_cols;k++) //iterate through each column
			{
				setBodyMassIndexs(k); //set indices for calls to BodyMass(x) depending on current equation
				for(int a = 0; a < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix[j].n_rows; a++) //iterate through each col * row (cell)
				{
					complexDouble newVal = getBodyMassVal(j, bodyMassIndexs[0]) + getBodyMassVal(j, bodyMassIndexs[1]) + getBodyMassVal(j, bodyMassIndexs[2]) 
					+ getBodyMassVal(j, bodyMassIndexs[3]) + getBodyMassVal(j, bodyMassIndexs[4])
					//+ getHydroReactSum(j,k,a) +
					+ getUserReactSum(j,k,a);
					// - theBodyWithForceMatrices.hydroActiveForceMatrix[k][a] - //FIX <---Which
					//theBodyWithForceMatrices.userActiveForceMatrix[k][a];

				}
			}
		}
	}
}

complexDouble EquationOfMotion_01::getUserReactSum(int order,int col, int row)
{
	complexDouble newVal(0,0);

	for(int i = 0; i < newBodyMatrix.userReactiveForceMatrix.size(); i++)
	{
		newVal += newBodyMatrix.userReactiveForceMatrix[i].derivativeMatrix[order].at(col,row);
	}

	return newVal;
}

complexDouble EquationOfMotion_01::getHydroReactSum(int order,int col, int row)
{
	complexDouble newVal(0,0);

	for(int i = 0; i < newBodyMatrix.hydroReactiveForceMatrix.size(); i++)
	{
		newVal += newBodyMatrix.hydroReactiveForceMatrix[i].derivativeMatrix[order].at(col,row);
	}

	return newVal;
}

complexDouble EquationOfMotion_01::getHydroCrossSum(int,int,int,int)
{
	return complexDouble(0,0); //FIX
}

complexDouble EquationOfMotion_01::getUserCrossSum(int,int,int,int)
{
	return complexDouble(0,0); //FIX
}

complexDouble EquationOfMotion_01::getBodyMassVal(int equationNum, int var)
{
	if(equationNum < 0 || var < 0 || equationNum > (newBodyMatrix.massMatrix.n_rows - 1) 
		|| var >  (newBodyMatrix.massMatrix.n_cols - 1)) 
		return 0.0; //out of bounds, return 0

	return newBodyMatrix.massMatrix(equationNum, var);
}

void EquationOfMotion_01::setBodyMassIndexs(int curIndex)
{
	switch(curIndex)
	{
		case 0:
			bodyMassIndexs[0] = EQ_0_BM1;
			bodyMassIndexs[1] = EQ_0_BM2;
			bodyMassIndexs[2] = EQ_0_BM3;
			bodyMassIndexs[3] = EQ_0_BM4;
			bodyMassIndexs[4] = EQ_0_BM5;
			break;
		case 1:
			bodyMassIndexs[0] = EQ_1_BM1;
			bodyMassIndexs[1] = EQ_1_BM2;
			bodyMassIndexs[2] = EQ_1_BM3;
			bodyMassIndexs[3] = EQ_1_BM4;
			bodyMassIndexs[4] = EQ_1_BM5;
			break;
		case 2:
			bodyMassIndexs[0] = EQ_2_BM1;
			bodyMassIndexs[1] = EQ_2_BM2;
			bodyMassIndexs[2] = EQ_2_BM3;
			bodyMassIndexs[3] = EQ_2_BM4;
			bodyMassIndexs[4] = EQ_2_BM5;
			break;
		case 3:
			bodyMassIndexs[0] = EQ_3_BM1;
			bodyMassIndexs[1] = EQ_3_BM2;
			bodyMassIndexs[2] = EQ_3_BM3;
			bodyMassIndexs[3] = EQ_3_BM4;
			bodyMassIndexs[4] = EQ_3_BM5;
			break;
		case 4:
			bodyMassIndexs[0] = EQ_4_BM1;
			bodyMassIndexs[1] = EQ_4_BM2;
			bodyMassIndexs[2] = EQ_4_BM3;
			bodyMassIndexs[3] = EQ_4_BM4;
			bodyMassIndexs[4] = EQ_4_BM5;
			break;
		case 5:
			bodyMassIndexs[0] = EQ_5_BM1;
			bodyMassIndexs[1] = EQ_5_BM2;
			bodyMassIndexs[2] = EQ_5_BM3;
			bodyMassIndexs[3] = EQ_5_BM4;
			bodyMassIndexs[4] = EQ_5_BM5;
			break;
	}
}
