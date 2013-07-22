#include "equationofmotion_01.h"


EquationOfMotion_01::EquationOfMotion_01() : EquationOfMotion()
{
	bodyMassIndexs[0] = EQ_0_BM1;
	bodyMassIndexs[1] = EQ_0_BM2;
	bodyMassIndexs[2] = EQ_0_BM3;
	bodyMassIndexs[3] = EQ_0_BM4;
	bodyMassIndexs[4] = EQ_0_BM5;

	cx_mat temp(6,1); //FIX, Solution Matrix filled with Zeros, needs to be computed values
	temp.zeros();
	solutionMatrix = temp;
}

EquationOfMotion_01::~EquationOfMotion_01()
{}

void EquationOfMotion_01::setBodyData(Body bodyDataIn, UserForces userForcesIn) //Assume 6DOF only
{
	//User Force Matrices Names stored in vector of strings
	newBodyMatrix.userReactiveForce = bodyDataIn.userReactiveForces;
	newBodyMatrix.userActiveForce = bodyDataIn.userActiveForces;
	newBodyMatrix.userCrossBodyForces = bodyDataIn.userCrossBodyForces;

	//Hydro Force Matrices Names stored in vector of strings
	newBodyMatrix.hydroReactiveForce = bodyDataIn.hydroReactiveForces;
	newBodyMatrix.hydroActiveForce = bodyDataIn.hydroActiveForces;
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
			//convert to force coefficients
			cx_mat coeffFound(temp);
			newBodyMatrix.userActiveForceMatrix.push_back(coeffFound);
		}
		else
			break;
	}

	//user Reactive matrices
	for(int i = 0; i < newBodyMatrix.userReactiveForce.size(); i++)
	{
		//Retrieve the User Reactive Force Object by passing in the name of force (string)
		vector<Derivative> temp = userForcesIn.getUserReactiveForce(newBodyMatrix.userReactiveForce[i]);

		if(temp.size() > 0) //if found then add to vector
		{
			//Convert to ReactiveForceMatrix object which converts which contains the force coefficients
			ReactiveForceMatrix tempReactiveMatrix(temp);
			newBodyMatrix.userReactiveForceMatrix.push_back(tempReactiveMatrix);
		}
	}

	//user CrossBody matrix(s)
	for(int i = 0; i < newBodyMatrix.userCrossBodyForces.size(); i++) 
	{
		//Retrieve the User Reactive Force Object by passing in the name of force (string)
		vector<Derivative> temp = userForcesIn.getUserCrossBodyForce(newBodyMatrix.userCrossBodyForces[i]);

		if(temp.size() > 0)
		{
			//Convert to ReactiveForceMatrix object which converts which contains the force coefficients
			ReactiveForceMatrix tempCrossBodyMatrix(temp);
			newBodyMatrix.userCrossBodyForceMatrix.push_back(tempCrossBodyMatrix);
		}
	}

	//Testing that cross body read in correctly, REMOVE after verification complete
	//for(int i = 0; i < 3; i++)
	//{
	//	newBodyMatrix.userCrossBodyForceMatrix[0].derivativeMatrix[i].raw_print();
	//	cout << endl;
	//}

	//Make calculations according to the 6DOF model
	calculateEquations(newBodyMatrix);
}

void EquationOfMotion_01::calculateEquations(BodyWithForceMatrix theBodyWithForceMatrices)
{
	//Calculate the Body Mass Matrix
	for(int i = 0; i < theBodyWithForceMatrices.massMatrix.n_cols; i++)
	{
		setBodyMassIndexs(i); //set the correct values Body Mass for each equation
		for(int j = 0; j < theBodyWithForceMatrices.massMatrix.n_rows; j++)
		{
			if (isCurrentBodyMassIndex(j))
				theBodyWithForceMatrices.massMatrix.at(i,j) = theBodyWithForceMatrices.massMatrix.at(i,j)*timeDifferentiation(solutionMatrix[j], 2);
		}
	}

	//calculate user reactive force matrices
	for(int i = 0; i < theBodyWithForceMatrices.userReactiveForceMatrix.size(); i ++) //iterate through all user reacive force matrices
	{
		for(int order = 0; order < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix.size(); order++) //iterate through each order derivative
		{
			for(int row = 0; row < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix[order].n_rows;row++) //iterate through each row
			{
				for(int col = 0; col < theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix[order].n_cols; col++) //iterate through each col * row (cell)
				{
					theBodyWithForceMatrices.userReactiveForceMatrix[i].derivativeMatrix[order].at(row,col) *= timeDifferentiation(solutionMatrix.at(row,1),order);
				}
			}
		}
	}

	//calculate hydro reactive force matrices
	for(int i = 0; i < theBodyWithForceMatrices.hydroReactiveForceMatrix.size(); i ++) //iterate through all hydro reacive force matrices
	{
		for(int order = 0; order < theBodyWithForceMatrices.hydroReactiveForceMatrix[i].derivativeMatrix.size(); order++) //iterate through each order derivative
		{
			for(int row = 0; row < theBodyWithForceMatrices.hydroReactiveForceMatrix[i].derivativeMatrix[order].n_rows;row++) //iterate through each row
			{
				for(int col = 0; col < theBodyWithForceMatrices.hydroReactiveForceMatrix[i].derivativeMatrix[order].n_cols; col++) //iterate through each col * row (cell)
				{
					theBodyWithForceMatrices.hydroReactiveForceMatrix[i].derivativeMatrix[order].at(row,col) *= timeDifferentiation(solutionMatrix.at(row,1),order);
				}
			}
		}
	}
	
	//FIX, need to add support for multiple bodies and hydro forces
	////calculate user cross body force matrices
	//for(int i = 0; i < theBodyWithForceMatrices.userCrossBodyForceMatrix.size(); i ++) //iterate through all user reacive force matrices
	//{
	//	for(int order = 0; order < theBodyWithForceMatrices.userCrossBodyForceMatrix[i].derivativeMatrix.size(); order++) //iterate through each order derivative
	//	{
	//		for(int row = 0; row < theBodyWithForceMatrices.userCrossBodyForceMatrix[i].derivativeMatrix[order].n_rows;row++) //iterate through each row
	//		{
	//			for(int col = 0; col < theBodyWithForceMatrices.userCrossBodyForceMatrix[i].derivativeMatrix[order].n_cols; col++) //iterate through each col * row (cell)
	//			{
	//				theBodyWithForceMatrices.userCrossBodyForceMatrix[i].derivativeMatrix[order].at(row,col) *= timeDifferentiation(solutionMatrix.at(row,1),order);
	//			}
	//		}
	//	}
	//}

	////calculate hydro cross body force matrices
	//for(int i = 0; i < theBodyWithForceMatrices.hydroCrossBodyForceMatrix.size(); i ++) //iterate through all user reacive force matrices
	//{
	//	for(int order = 0; order < theBodyWithForceMatrices.hydroCrossBodyForceMatrix[i].derivativeMatrix.size(); order++) //iterate through each order derivative
	//	{
	//		for(int row = 0; row < theBodyWithForceMatrices.hydroCrossBodyForceMatrix[i].derivativeMatrix[order].n_rows;row++) //iterate through each row
	//		{
	//			for(int col = 0; col < theBodyWithForceMatrices.hydroCrossBodyForceMatrix[i].derivativeMatrix[order].n_cols; col++) //iterate through each col * row (cell)
	//			{
	//				theBodyWithForceMatrices.hydroCrossBodyForceMatrix[i].derivativeMatrix[order].at(row,col) *= timeDifferentiation(solutionMatrix.at(row,1),order);
	//			}
	//		}
	//	}
	//}
}

complexDouble EquationOfMotion_01::getBodyMassVal(int equationNum, int var)
{
	if(equationNum < 0 || var < 0 || equationNum > (newBodyMatrix.massMatrix.n_rows - 1) 
		|| var >  (newBodyMatrix.massMatrix.n_cols - 1)) 
		return 0.0; //out of bounds, return 0

	return newBodyMatrix.massMatrix(equationNum, var);
}

bool EquationOfMotion_01::isCurrentBodyMassIndex(int curIndex)
{
	//iterate through current bodyMassIndex and see if valid
	for(int i = 0; i < bodyEquationSize; i++)
	{
		if(curIndex == bodyMassIndexs[i])
		{
			return true; //assign true if a valid index
		}
	}
	return false; //return false is current index not found
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
