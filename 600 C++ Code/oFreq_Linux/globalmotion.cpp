#include "globalmotion.h"


GlobalMotion::GlobalMotion() 
	: GlobalSolution()
{
	name = MOTION_NAME;
	orderDerivative = GLOBAL_MOTION_DERIVATIVE;
}


GlobalMotion::~GlobalMotion()
{
}
