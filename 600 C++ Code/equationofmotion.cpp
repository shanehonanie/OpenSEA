#include "equationofmotion.h"


EquationOfMotion::EquationOfMotion()
{}


EquationOfMotion::~EquationOfMotion()
{}

BodyWithForceMatrix EquationOfMotion::getBodyForceData()
{
	return newBodyMatrix;
}

double EquationOfMotion::kroneckerDelta(int num1, int num2)
{
	if (num1 == num2)
		return 0.0;
	else
		return 1.0;
}

complexDouble EquationOfMotion::timeDifferentiation(complexDouble variable, int order)
{
	complexDouble temp(1,0); //correct?
	if (variable.real() == 1.0) //compare the real part to 1? or entire #?
	{
		return temp;
	}
	else
	{
		return variable* pow(temp, order) * pow(curWaveFreq, order); //need to verify this
	}
}
