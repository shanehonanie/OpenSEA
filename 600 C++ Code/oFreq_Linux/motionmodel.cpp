#include "motionmodel.h"

MotionModel::MotionModel()
{}

MotionModel::~MotionModel()
{}

BodyWithForceMatrix MotionModel::setBodyData(Body bodyDataIn, UserForces userForcesIn) //Assume 6DOF only
{
	BodyWithForceMatrix theBodyForceMatrix;

	if(bodyDataIn.getMotionModel() == EQUATION_01) //6DOF
	{
		EquationOfMotion_01 motionModel_6DOF; //create new 6DOF object
		motionModel_6DOF.setWaveFreq(curWaveFreq); 
		motionModel_6DOF.setBodyData(bodyDataIn, userForcesIn); //perform calcultions for force coefficients
		theBodyForceMatrix = motionModel_6DOF.getBodyForceData();
	}
	
	return theBodyForceMatrix;
}

void MotionModel::setWaveFrequencies(double newWaveFreq)
{
	curWaveFreq = newWaveFreq;
}

int MotionModel::getMatrixSize(string motionType)
{
	if(motionType == EQUATION_01)
		return EQUATION_01_SIZE;
	else 
		return -1;
}
