#ifndef GLOBALVELOCITY_H
#define GLOBALVELOCITY_H
#include "globalsolution.h"
using namespace std;

const string VELOCITY_NAME = "velglobal";

class GlobalVelocity : public GlobalSolution
{
public:
	GlobalVelocity();
	~GlobalVelocity();
};
#endif
