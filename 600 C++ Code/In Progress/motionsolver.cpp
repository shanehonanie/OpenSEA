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

	vector<cx_mat> theBodyMassMatrices;

	for(int i = 0; i < theBodyWithForceMatrix.size(); i ++) //get Each Body Mass Matrix
	{
		theBodyMassMatrices.push_back(theBodyWithForceMatrix[i].massMatrix);
	}

	vector<cx_mat> solutionPerBodyMatrix; //This is a column matrix

	//Create Solution Matrix for each Body
	for(int i = 0; i < theBodyMassMatrices.size(); i++)
	{
		//cx_mat bodyMassMatrix = theBodyWithForceMatrix[i].massMatrix; //<--Delete afer add support for multiple bodies

		//"Sum Forces for Each Set"
		vector<cx_mat> userReactiveForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[i].userReactiveForceMatrix);
		vector<cx_mat> userCrossBodyForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[i].userCrossBodyForceMatrix);
		cx_mat userActiveForceMatrix = sumActiveForceEachSet(theBodyWithForceMatrix[i].userActiveForceMatrix);

		//"Sum Derivatives"
		cx_mat userReactiveForceSingleMatrix = sumDerivatives(userReactiveForceMatrix);
		cx_mat userCrossBodyForceSingleMatrix = sumDerivatives(userCrossBodyForceMatrix);

		//"Sum Force Types"
		cx_mat reactiveForceMatrix = (userReactiveForceSingleMatrix + theBodyMassMatrices[i]);
		cx_mat crossBodyForceMatrix = userCrossBodyForceSingleMatrix; //Hydro Matrix not supported yet
		cx_mat activeForceMatrix = userActiveForceMatrix; //Hydro Matrix not supported yet

		//Assemble Global Matrix
		cx_mat reactiveForceMatrixGlobal = reactiveForceMatrix + crossBodyForceMatrix; //A Matrix
		cx_mat activeForceMatrixGlobal = activeForceMatrix;                            //F Matrix

		//Test print A & F Matrix
		cout << "-- Body " << i+1 << " --" << endl;
		reactiveForceMatrixGlobal.print("Reactive Matrix");
		activeForceMatrixGlobal.print("Active Matrix");
	
		//Solve for Unknown Matrix (the X Matrix) --    A*X=B where X is the unknown
		cx_mat unknownMatrix = solve(reactiveForceMatrixGlobal, activeForceMatrixGlobal, true); //true arg for more precise calculations
		solutionPerBodyMatrix.push_back(unknownMatrix);
		unknownMatrix.print("X Matrix");
		cout <<endl;
	}


	////Only Solve for 1 Body (temporary, will be expanded to solver for all bodies
	//cx_mat bodyMassMatrix = theBodyWithForceMatrix[0].massMatrix;

	////"Sum Forces for Each Set"
	//vector<cx_mat> userReactiveForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[0].userReactiveForceMatrix);
	//vector<cx_mat> userCrossBodyForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[0].userCrossBodyForceMatrix);
	//cx_mat userActiveForceMatrix = sumActiveForceEachSet(theBodyWithForceMatrix[0].userActiveForceMatrix);

	////"Sum Derivatives"
	//cx_mat userReactiveForceSingleMatrix = sumDerivatives(userReactiveForceMatrix);
	//cx_mat userCrossBodyForceSingleMatrix = sumDerivatives(userCrossBodyForceMatrix);

	////"Sum Force Types"
	//cx_mat reactiveForceMatrix = (userReactiveForceSingleMatrix + bodyMassMatrix);
	//cx_mat crossBodyForceMatrix = userCrossBodyForceSingleMatrix; //Hydro Matrix not supported yet
	//cx_mat activeForceMatrix = userActiveForceMatrix; //Hydro Matrix not supported yet

	////Assemble Global Matrix
	//cx_mat reactiveForceMatrixGlobal = reactiveForceMatrix + crossBodyForceMatrix; //A Matrix
	//cx_mat activeForceMatrixGlobal = activeForceMatrix;                            //F Matrix

	////Test print A & F Matrix
	//reactiveForceMatrixGlobal.print("Reactive Matrix");
	//activeForceMatrixGlobal.print("Active Matrix");
	//
	////Solve for Unknown Matrix (the X Matrix) --    A*X=B where X is the unknown
	//cx_mat unknownMatrix = solve(reactiveForceMatrixGlobal, activeForceMatrixGlobal);
	//unknownMatrix.print("X Matrix");
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

