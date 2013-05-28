#include "globalacceleration.h"


GlobalAcceleration::GlobalAcceleration() 
	: GlobalSolution()
{
	name = ACCELERATION_NAME;
	orderDerivative = GLOBAL_ACCELERATION_DERIVATIVE;
}


GlobalAcceleration::~GlobalAcceleration()
{
}
