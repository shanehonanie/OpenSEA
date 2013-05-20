#ifndef EQUATIONOFMOTION_01_H
#define EQUATIONOFMOTION_01_H
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"
#include "equationofmotion.h"

using namespace arma;
using namespace std;

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

class EquationOfMotion_01 : public EquationOfMotion
{
public:
	EquationOfMotion_01();
	~EquationOfMotion_01();
	void setBodyData(Body, UserForces);	
//	void calculateEquations(ReactiveForceMatrix); //calculate equtaions 0-5
	void calculateEquations(BodyWithForceMatrix); //calculate equtaions 0-5
	complexDouble getBodyMassVal(int, int); //first int implies row, second int selects the cell
	void setBodyMassIndexs(int);
	complexDouble getUserReactSum(int,int,int);
	complexDouble getHydroReactSum(int,int,int);
	complexDouble getHydroCrossSum(int,int,int,int);
	complexDouble getUserCrossSum(int,int,int,int);


	int bodyMassIndexs[5];
	

private:
	
};
#endif
