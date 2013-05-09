#include "motionsolver.h"

MotionSolver::MotionSolver(vector<Body> bodyDataIn, UserForces userForcesIn) 
	: theBodyData(bodyDataIn), theForcesData(userForcesIn)
{}


MotionSolver::~MotionSolver()
{}

void MotionSolver::CalculateOutputs()
{
	//Convert Input Coefficients to Force Coefficients for each body, add new object to theBodyWithForceMatrix vector
	for(int i = 0; i < theBodyData.size(); i++)
	{
		theBodyWithForceMatrix.push_back(theMotionModel.setBodyData(theBodyData[i], theForcesData)); 
	}

	//Only Solve for 1 Body (temporary, will be expanded to solver for all bodies)
	//cx_mat userReactiveForceMatrix = sumForceEachSet(theBodyWithForceMatrix[0].userReactiveForceMatrix[0].derivativeMatrix);



}




cx_mat MotionSolver::sumForceEachSet(vector<ReactiveForceMatrix> theReactiveForceMatrix)
{
	cx_mat singleForceMarix(6,6); // 6x6 matrix
	vector<cx_mat> allForceMatrix;

	for(int i = 0; i < theReactiveForceMatrix.size(); i++) //each reactive force matrix
	{
		allForceMatrix.push_back(sumForceEachSetHelper(theReactiveForceMatrix[i].derivativeMatrix));
	}

	//TO DO ---Sum all derivative matrixes in allForceMatrix and return single matrix
	return singleForceMarix;
}

//sum each order derivative and return single force type, return single matrix
cx_mat MotionSolver::sumForceEachSetHelper(cx_mat theForceMatrices[])
{
	cx_mat singleForceMarix(6,6); // 6x6 matrix
	for(int i = 0; i < theForceMatrices->size(); i++) //3 represents number of order derivative
	{
		for(int j = 0; j < (int)theForceMatrices->n_rows; j++) //iterate through each row
		{
			for(int k = 0; k < (int)theForceMatrices->n_cols; k++) //iterate through each cell in a row
			{
				singleForceMarix(j,k) += theForceMatrices[i](j,k);
			}
		}
	}
	return singleForceMarix;
}

////sum each order derivative and return single force type, return single matrix
//cx_mat MotionSolver::sumForceEachSet(cx_mat theForceMatrices[])
//{
//	cx_mat singleForceMarix(6,6); // 6x6 matrix
//	for(int i = 0; i < theForceMatrices->size(); i++) //3 represents number of order derivative
//	{
//		for(int j = 0; j < (int)theForceMatrices->n_rows; j++) //iterate through each row
//		{
//			for(int k = 0; k < (int)theForceMatrices->n_cols; k++) //iterate through each cell in a row
//			{
//				singleForceMarix(j,k) += theForceMatrices[i](j,k);
//			}
//		}
//	}
//	return singleForceMarix;
//}

cx_mat MotionSolver::sumDerivatives(cx_mat theForceMatrix)
{
	cx_mat sumOfDerivativesMatrix(1,1); //create matrix wih 1 single cell for sum of all derivatives

	for(int i = 0 ; i < theForceMatrix.n_cols; i++) //size of theForce Matrix should be 1 x n
	{
		sumOfDerivativesMatrix(0,0) += theForceMatrix(0,i); //add each cell in column to new matrix
	}

	return sumOfDerivativesMatrix;
}

