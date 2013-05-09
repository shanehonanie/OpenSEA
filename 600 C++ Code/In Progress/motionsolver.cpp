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


	//Only Solve for 1 Body (temporary, will be expanded to solver for all bodies
	cx_mat bodyMassMatrix = theBodyWithForceMatrix[0].massMatrix;

	//"Sum Forces for Each Set"
	vector<cx_mat> userReactiveForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[0].userReactiveForceMatrix);
	vector<cx_mat> userCrossBodyForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[0].userCrossBodyForceMatrix);
	cx_mat userActiveForceMatrix = sumActiveForceEachSet(theBodyWithForceMatrix[0].userActiveForceMatrix);

	//"Sum Derivatives"
	cx_mat userReactiveForceSingleMatrix = sumDerivatives(userReactiveForceMatrix);
	cx_mat userCrossBodyForceSingleMatrix = sumDerivatives(userCrossBodyForceMatrix);

	//"Sum Force Types"
	cx_mat reactiveForceMatrix = (userReactiveForceSingleMatrix + bodyMassMatrix);
	cx_mat crossBodyForceMatrix = userCrossBodyForceSingleMatrix; //Hydro Matrix not supported yet
	cx_mat activeForceMatrix = userActiveForceMatrix; //Hydro Matrix not supported yet

	//Assemble Global Matrix
	cx_mat reactiveForceMatrixGlobal = reactiveForceMatrix + crossBodyForceMatrix; //A Matrix
	cx_mat activeForceMatrixGlobal = activeForceMatrix;                                //F Matrix

	reactiveForceMatrixGlobal.print("Reactive Matrix");
	activeForceMatrixGlobal.print("Active Matrix");

	
	//Solve for Unknown Matrix (the X Matrix) --    A*X=B where X is the unknown
	cx_mat unknownMatrix = solve(reactiveForceMatrixGlobal, activeForceMatrixGlobal);
	unknownMatrix.print();
}


cx_mat MotionSolver::sumActiveForceEachSet(vector<cx_mat> theActiveForceMatrix)
{
	cx_mat singleForceMarix(6,1); //6x1 column matrix

	for(int i = 0; i < theActiveForceMatrix.size(); i++)
	{
		singleForceMarix += theActiveForceMatrix[i];
	}

	return singleForceMarix;
}

//Sum all forces in vector and return single matrix
vector<cx_mat> MotionSolver::sumReactiveForceEachSet(vector<ReactiveForceMatrix> theReactiveForceMatrix)
{
	vector<cx_mat> theSingleMatrix; 

	for(int i = 0; i < MAX_ORDER_DERIVATIVE; i++) //create a 6x6 matrix for each order derivative (0-2)
	{
		cx_mat temp(6,6);
		theSingleMatrix.push_back(temp);
	}

	for(int i = 0 ; i < MAX_ORDER_DERIVATIVE; i++)
	{
		for(int j = 0; j < theReactiveForceMatrix.size(); j++)
		{
			theSingleMatrix[i] += theReactiveForceMatrix[j].derivativeMatrix[i];
		}
	}

	return theSingleMatrix;
}

cx_mat MotionSolver::sumDerivatives(vector<cx_mat> theReactiveForceMatrix)
{
	cx_mat singleReactiveForceMatrix(6,6);

	for(int i = 0 ; i < theReactiveForceMatrix.size(); i++) //size should be 3 for derivative order (0-2)
	{
		singleReactiveForceMatrix += theReactiveForceMatrix[i];
	}

	return singleReactiveForceMatrix;
}

////Sum all forces in vector and return single matrix
//cx_mat MotionSolver::sumReactiveForceEachSet(vector<ReactiveForceMatrix> theReactiveForceMatrix)
//{
//	cx_mat singleForceMarix(6,6); // 6x6 matrix
//
//	for(int i = 0; i < theReactiveForceMatrix.size(); i++) //each reactive force matrix
//	{
//		//Perform matrix addition on all matrices in vector
//		cx_mat temp = sumReactiveForceEachSetHelper(theReactiveForceMatrix[i].derivativeMatrix);
//		singleForceMarix += temp;
//	}
//	return singleForceMarix;
//}

//sum each order derivative and return single force type, return single matrix
//cx_mat MotionSolver::sumReactiveForceEachSetHelper(cx_mat theForceMatrices[])
//{
//	cx_mat singleForceMarix(6,6); // 6x6 matrix
//	for(int i = 0; i < 3; i++) //3 represents number of order derivative
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

//cx_mat MotionSolver::sumDerivatives(cx_mat theForceMatrix)
//{
//	cx_mat sumOfDerivativesMatrix(1,1); //create matrix wih 1 single cell for sum of all derivatives
//
//	for(int i = 0 ; i < theForceMatrix.n_cols; i++) //size of theForce Matrix should be 1 x n
//	{
//		sumOfDerivativesMatrix(0,0) += theForceMatrix(0,i); //add each cell in column to new matrix
//	}
//
//	return sumOfDerivativesMatrix;
//}

