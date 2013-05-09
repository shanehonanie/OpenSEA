#include "reactiveforcematrix.h"


ReactiveForceMatrix::ReactiveForceMatrix()
{
}

ReactiveForceMatrix::~ReactiveForceMatrix()
{
}

ReactiveForceMatrix::ReactiveForceMatrix(vector<Derivative> forceListIn)
{
	for(int i = 0 ;i < forceListIn.size(); i++) //3 derivative objects (default)
	{
		cx_mat tempMatrix(6,6); //<----6x6 matrix of complex Doubles
		for(int j = 0; j < forceListIn[i].getEquationListSize(); j++) //6 equations (default)
		{
			for(int k = 0; k < forceListIn[i].equationList[j].getCoefficientListSize(); k++) //6 coefficients (default)
			{
				complexDouble tempComplex(forceListIn[i].equationList[j].coefficients[k], 0); //create complex # w/ 0i
				tempMatrix(j,k) = tempComplex; //j is equation #, k is coefficient
			}
		}
		derivativeMatrix[i] = tempMatrix; //assign derivative order matrix to proper index
	}
}



