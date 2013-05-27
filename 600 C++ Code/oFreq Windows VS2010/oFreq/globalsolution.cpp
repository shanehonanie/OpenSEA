#include "globalsolution.h"


GlobalSolution::GlobalSolution() : OutputDerived(), orderDerivative(-1)
{
}


GlobalSolution::~GlobalSolution()
{
}

cx_mat GlobalSolution::calculateOutput(cx_mat matrixIn, double curWaveFreq)
{
	cx_mat newMatrix(matrixIn.n_rows,1);
	complexDouble compI(0,1); //comlex number w/ 0 real, 1 imaginary used below for computations

	for(int i = 0; i < matrixIn.n_rows; i++)
	{
		newMatrix[i] = pow(curWaveFreq, orderDerivative) * pow(compI, orderDerivative) * matrixIn[i];
	}
	return newMatrix;
}
