#include "globalvelocity.h"


GlobalVelocity::GlobalVelocity() 
	: GlobalSolution()
{
	name = VELOCITY_NAME;
	orderDerivative = GLOBAL_VELOCITY_DERIVATIVE;
}


GlobalVelocity::~GlobalVelocity()
{
}
