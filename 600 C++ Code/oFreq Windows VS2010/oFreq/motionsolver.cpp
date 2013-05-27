#include "motionsolver.h"

MotionSolver::MotionSolver(vector<Body> bodyDataIn, UserForces userForcesIn, vector<double> newWaveFreq) 
	: theBodyData(bodyDataIn), theForcesData(userForcesIn), waveFrequencies(newWaveFreq)
{
	theMotionModel.setWaveFrequencies(waveFrequencies);
	maxMatrixSize = theMotionModel.getMatrixSize(theBodyData[0].getMotionModel());
}


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

	//Each index represents the single matrix for each body
	vector<cx_mat> reactiveForceMatrix;
	vector<cx_mat> crossBodyForceMatrix;
	vector<cx_mat> activeForceMatrix;
	
	for(int i = 0; i < theBodyMassMatrices.size(); i++) //1 body mass matrix per body
	{
		//"Sum Forces for Each Set"
		vector<cx_mat> userReactiveForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[i].userReactiveForceMatrix);
		vector<cx_mat> userCrossBodyForceMatrix = sumReactiveForceEachSet(theBodyWithForceMatrix[i].userCrossBodyForceMatrix);
		cx_mat userActiveForceMatrix = sumActiveForceEachSet(theBodyWithForceMatrix[i].userActiveForceMatrix);

		//"Sum Derivatives"
		cx_mat userReactiveForceSingleMatrix = sumDerivatives(userReactiveForceMatrix);
		cx_mat userCrossBodyForceSingleMatrix = sumDerivatives(userCrossBodyForceMatrix);

		//"Sum Force Types"
		reactiveForceMatrix.push_back(userReactiveForceSingleMatrix + theBodyMassMatrices[i]);
		crossBodyForceMatrix.push_back(userCrossBodyForceSingleMatrix); //Hydro Matrix not supported yet
		activeForceMatrix.push_back(userActiveForceMatrix); //Hydro Matrix not supported yet
	}

	//"Assemble Global Matrix"
	if(theBodyMassMatrices.size() == 1) //Single Body Matrix
	{
		//Dont include cross body forces if only 1 matrix and just use first index of vector
		reactiveForceMatrixGlobal = reactiveForceMatrix[0]; //A Matrix
		activeForceMatrixGlobal = activeForceMatrix[0];     //F Matrix
	}
	else //Multiple Bodies, must resize the matrices
	{
		int newMatrixSize = 0;

		for(int j = 0; j < theBodyMassMatrices.size(); j++) //get the size of new matrix by summing all reactiveForceMatrices
			newMatrixSize += reactiveForceMatrix[j].n_cols;

		
		complexDouble zeroVal(0.0,0.0);
		//A Matrix
		reactiveForceMatrixGlobal.resize(newMatrixSize, newMatrixSize); //resize matrix to include all bodies reactiveforces & cross Body Forces, matrix must be square (ex. 6x6)
		reactiveForceMatrixGlobal.fill(zeroVal); //Fill the newly created matrix with 0s temporarily
		//F Matrix
		activeForceMatrixGlobal.resize(newMatrixSize, 1); //column Matrix
		activeForceMatrixGlobal.fill(zeroVal); //Fill the newly created matrix with 0s temporarily

		setMatrixIndexPositions(theBodyMassMatrices.size(), maxMatrixSize); //sets the index for variables used to place the submatrixes in global matrix

		//Calculate the Reactive Matrix & Acives Matrix depedong on number of bodies
		switch(theBodyMassMatrices.size())
		{
			case 2:
				//Body 1 Reactive & CrossBody Forces
				reactiveForceMatrixGlobal.submat(body1ReactivePos[0],body1ReactivePos[1], body1ReactivePos[0] + (maxMatrixSize-1), body1ReactivePos[1] + (maxMatrixSize-1)) = reactiveForceMatrix[0];
				reactiveForceMatrixGlobal.submat(body1CrossPos1[0], body1CrossPos1[1], body1CrossPos1[0] + (maxMatrixSize-1), body1CrossPos1[1] + (maxMatrixSize-1)) = crossBodyForceMatrix[0];

				//Body 1 Active Forces
				activeForceMatrixGlobal.submat(0,0, maxMatrixSize - 1, 0) = activeForceMatrix[0];

				//Body 2 Reactive & CrossBody Forces
				reactiveForceMatrixGlobal.submat(body2ReactivePos[0], body2ReactivePos[1], body2ReactivePos[0] + (maxMatrixSize-1), body2ReactivePos[1] + (maxMatrixSize-1)) = reactiveForceMatrix[1];
				reactiveForceMatrixGlobal.submat(body2CrossPos1[0], body2CrossPos1[1], body2CrossPos1[0] + (maxMatrixSize-1), body2CrossPos1[1] + (maxMatrixSize-1)) = crossBodyForceMatrix[1];

				//Body 2 Active Forces
				activeForceMatrixGlobal.submat(maxMatrixSize,0, maxMatrixSize*2 - 1, 0) = activeForceMatrix[1];
				break;
			case 3:
				//Body 1 Reactive & CrossBody Forces
				reactiveForceMatrixGlobal.submat(body1ReactivePos[0],body1ReactivePos[1], body1ReactivePos[0] + (maxMatrixSize-1), body1ReactivePos[1] + (maxMatrixSize-1)) = reactiveForceMatrix[0];
				reactiveForceMatrixGlobal.submat(body1CrossPos1[0], body1CrossPos1[1], body1CrossPos1[0] + (maxMatrixSize-1), body1CrossPos1[1] + (maxMatrixSize-1)) = crossBodyForceMatrix[0];
				//reactiveForceMatrixGlobal.submat(body1CrossPos2[0], body1CrossPos2[1], body1CrossPos2[0] + (maxMatrixSize-1), body1CrossPos2[1] + (maxMatrixSize-1)) = 

				//Body 1 Active Forces
				activeForceMatrixGlobal.submat(0,0, maxMatrixSize - 1, 0) = activeForceMatrix[0];

				//Body 2 Reactive & CrossBody Forces
				reactiveForceMatrixGlobal.submat(body2ReactivePos[0], body2ReactivePos[1], body2ReactivePos[0] + (maxMatrixSize-1), body2ReactivePos[1] + (maxMatrixSize-1)) = reactiveForceMatrix[1];
				reactiveForceMatrixGlobal.submat(body2CrossPos1[0], body2CrossPos1[1], body2CrossPos1[0] + (maxMatrixSize-1), body2CrossPos1[1] + (maxMatrixSize-1)) = crossBodyForceMatrix[1];
				//reactiveForceMatrixGlobal.submat(body3CrossPos2[0], body3CrossPos2[1], body3CrossPos2[0] + maxMatrixSize, body3CrossPos2[1] + maxMatrixSize) = 

				//Body 2 Active Forces
				activeForceMatrixGlobal.submat(maxMatrixSize,0, maxMatrixSize*2 - 1, 0) = activeForceMatrix[1];

				//Body 3 Reactive & CrossBody Forces
				reactiveForceMatrixGlobal.submat(body3ReactivePos[0], body3ReactivePos[1], body3ReactivePos[0] + maxMatrixSize, body3ReactivePos[2] + maxMatrixSize) = reactiveForceMatrix[2];
				reactiveForceMatrixGlobal.submat(body3CrossPos1[0], body3CrossPos1[1], body3CrossPos1[0] + maxMatrixSize, body3CrossPos1[1] + maxMatrixSize) = crossBodyForceMatrix[2];
				//reactiveForceMatrixGlobal.submat(body3CrossPos2[0], body3CrossPos2[1], body3CrossPos2[0] + maxMatrixSize, body3CrossPos2[1] + maxMatrixSize) = 

				//Body 3 Active Forces
				activeForceMatrixGlobal.submat(maxMatrixSize*2,0, maxMatrixSize*3 - 1, 0) = activeForceMatrix[2];
				break;
			default:
				cout << "Error: Max Bodies supported is 3" << endl; //<--Temporary
		}	
	}

	//Solve for Unknown Matrix (the X Matrix) --    A*X=B where X is the unknown
	solutionColumnMatrix = solve(reactiveForceMatrixGlobal, activeForceMatrixGlobal, true); //true arg for more precise calculations

	//Assign solutions to each bodys solutionMatrix
	for(int i = 0; i < theBodyData.size(); i++)
	{
		cx_mat perBodySolution = solutionColumnMatrix.submat((i*maxMatrixSize),0, ((i+1)*maxMatrixSize-1),0);
		theBodyData[i].solutionMatrix = perBodySolution;
	}

	////Test print A & F Matrix
	//cout << "-- Body " << i+1 << " --" << endl;
	//reactiveForceMatrixGlobal.raw_print("Reactive Matrix");
	//activeForceMatrixGlobal.raw_print("Active Matrix");

	//Test print A & F & X Matrix to myfile
	ofstream myfile;
	myfile.open("motionsolverResults.txt");
	reactiveForceMatrixGlobal.raw_print(myfile, "Reactive Matrix"); myfile <<endl;
	activeForceMatrixGlobal.raw_print(myfile, "Active Matrix"); myfile <<endl;
	solutionColumnMatrix.raw_print(myfile, "Solution Matrix"); myfile <<endl;

	//cx_mat solutionColumnMatrix2(6,1);
	//myfile << "Column Size " << solutionColumnMatrix2.n_cols << endl;
	//myfile << "Row Size " << solutionColumnMatrix2.n_rows << endl;
	//solutionColumnMatrix2.raw_print(myfile, "Solution Matrix2"); myfile <<endl;

	myfile.close();
}

cx_mat MotionSolver::sumActiveForceEachSet(vector<cx_mat> theActiveForceMatrix)
{
	cx_mat singleForceMarix(maxMatrixSize,1); //6x1 column matrix

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
		cx_mat temp(maxMatrixSize, maxMatrixSize);
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
	cx_mat singleReactiveForceMatrix(maxMatrixSize, maxMatrixSize);

	for(int i = 0 ; i < theReactiveForceMatrix.size(); i++) //size should be 3 for derivative order (0-2)
	{
		//This code below returns a 0x0 solution matrix, uncomment below and comment single line above
		complexDouble curWaveFrequency(waveFrequencies[0], 0.0); //<---FIX, only uses 1 wave frequency for now
		complexDouble complexImaginary(0.0,1.0);
		complexDouble scalarMultiplier = pow(curWaveFrequency, i) * pow(complexImaginary, i);

		for(int col = 0; col < theReactiveForceMatrix[i].n_cols; col++)
		{
			for(int row = 0; row < theReactiveForceMatrix[i].n_rows; row++)
			{
				singleReactiveForceMatrix.at(col,row) += scalarMultiplier * theReactiveForceMatrix[i].at(col,row);
			}
		}
	}
	return singleReactiveForceMatrix;
}

void MotionSolver::setMatrixIndexPositions(int numBodies,int perMatrixSize)
{
	switch(numBodies)
	{
	case 1:
		body1ReactivePos[0] = 0;
		body1ReactivePos[1] = 0;
		break;
	case 2:
		body1ReactivePos[0] = 0;
		body1ReactivePos[1] = 0;
		body1CrossPos1[0] = perMatrixSize - 1;
		body1CrossPos1[1] = 0;
		body2CrossPos1[0] = perMatrixSize;;
		body2CrossPos1[1] = 0;
		body2ReactivePos[0] = perMatrixSize;
		body2ReactivePos[1] = perMatrixSize;
		break;
	case 3:
		body1ReactivePos[0] = 0;
		body1ReactivePos[1] = 0;
		body1CrossPos1[0] = perMatrixSize - 1;
		body1CrossPos1[1] = 0;
		body2CrossPos1[0] = perMatrixSize;;
		body2CrossPos1[1] = 0;
		body2ReactivePos[0] = perMatrixSize;
		body2ReactivePos[1] = perMatrixSize;

		body1CrossPos2[0] = perMatrixSize*2;
		body1CrossPos2[1] = 0;
		body2CrossPos2[0] = perMatrixSize*2;
		body2CrossPos2[1] = perMatrixSize;
		body3ReactivePos[0] = perMatrixSize*2;
		body3ReactivePos[1] = perMatrixSize*2;
		body3CrossPos1[0] = 0;
		body3CrossPos1[1] = perMatrixSize*2;
		body3CrossPos2[0] = perMatrixSize;
		body3CrossPos2[1] = perMatrixSize*2;
		break;
	default: //nothing
		break;
	}
}
