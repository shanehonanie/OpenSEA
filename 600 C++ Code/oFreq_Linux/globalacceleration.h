#ifndef GLOBALACCELERATION_H
#define GLOBALACCELERATION_H
#include "globalsolution.h"
using namespace std;

const string ACCELERATION_NAME = "accglobal";

class GlobalAcceleration : public GlobalSolution
{
public:
	GlobalAcceleration();
	~GlobalAcceleration();
};
#endif
