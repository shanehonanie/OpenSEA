#include "reactiveforcematrix.h"


ReactiveForceMatrix::ReactiveForceMatrix()
{
	//Add 3 matrices to derivative matrix
	for(int i = 0; i < 3; i++) //<---Fix, change to const
	{
		cx_mat temp(6,6);
		derivativeMatrix.push_back(temp);
	}

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
		//derivativeMatrix[i] = tempMatrix; //assign derivative order matrix to proper index
		derivativeMatrix.push_back(tempMatrix);
	}
}

//TO DO : FIX so const
int ReactiveForceMatrix::getSize()
{
	return 3; //<-----Fix, change to const
}

