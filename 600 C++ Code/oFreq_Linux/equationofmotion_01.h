#ifndef EQUATIONOFMOTION_01_H
#define EQUATIONOFMOTION_01_H
#include <complex>
#include <armadillo>
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"
#include "equationofmotion.h"

using namespace arma;
using namespace std;

const int bodyEquationSize = 5;
const int EQ_0_BM1 = 0;
const int EQ_0_BM2 = 4;
const int EQ_0_BM3 = 5;
const int EQ_0_BM4 = -1;
const int EQ_0_BM5 = -1;
const int EQ_1_BM1 = 1;
const int EQ_1_BM2 = 3;
const int EQ_1_BM3 = 5;
const int EQ_1_BM4 = -1;
const int EQ_1_BM5 = -1;
const int EQ_2_BM1 = 2;
const int EQ_2_BM2 = 3;
const int EQ_2_BM3 = 4;
const int EQ_2_BM4 = -1;
const int EQ_2_BM5 = -1;
const int EQ_3_BM1 = 1;
const int EQ_3_BM2 = 2;
const int EQ_3_BM3 = 3;
const int EQ_3_BM4 = 4;
const int EQ_3_BM5 = 5;
const int EQ_4_BM1 = 0;
const int EQ_4_BM2 = 2;
const int EQ_4_BM3 = 3;
const int EQ_4_BM4 = 4;
const int EQ_4_BM5 = 5;
const int EQ_5_BM1 = 0;
const int EQ_5_BM2 = 1;
const int EQ_5_BM3 = 3;
const int EQ_5_BM4 = 4;
const int EQ_5_BM5 = 5;

/**
 * This class holds data and functions to calculate the 6DOF Equation of Motion.
 */

class EquationOfMotion_01 : public EquationOfMotion
{
public:
	EquationOfMotion_01(); /**< The default constructor. */
	~EquationOfMotion_01(); /**< The default destructor, nothing happens here. */

	/**
	 * Sets the body and forces data for this object.
	 * @param bodyDataIn The Body.
	 * @param userForcesIn The user forces.
	 */
	void setBodyData(Body, UserForces);	

	/**
	 * Perform the calculations for the 6DOF Motion Model.
	 * @param theBodyWithForceMatrices The Body with force matrices.
	 */
	void calculateEquations(BodyWithForceMatrix); //calculate equtaions 0-5

	/**
	 * Retrieve a variable in the equaion from the mass matrix.
	 * @param equationNum The equation number (row in mass matrix).
	 * @param var The variable in the equation (column in mass matrix).
	 * @return The variable in the specified equation from the mass matrix.
	 */
	complexDouble getBodyMassVal(int, int); //first int implies row, second int selects the cell

	/**
	 * Sets the Indexs in solution matrix, This Needs to be fixed, only supports 2 bodies max.
	 * @param curIndex The current index in the matrix.
	 */
	void setBodyMassIndexs(int);

	/**
	 * Check if current index is valid in the mass matrix.
	 * @param curIndex The current index in mass matrix.
	 * return True if a valid entry in mass matrix.
	 */
	bool isCurrentBodyMassIndex(int);

	int bodyMassIndexs[bodyEquationSize]; /**< The indexs in solution matrix for all sub matrices. */
	
	cx_mat solutionMatrix; /**< The solution matirx. */

private:
	
};
#endif
