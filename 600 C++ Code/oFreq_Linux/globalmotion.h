#ifndef GLOBALMOTION_H
#define GLOBALMOTION_H
#include "globalsolution.h"
using namespace std;
const string MOTION_NAME = "motglobal";

class GlobalMotion : public GlobalSolution
{
public:
	GlobalMotion();
	~GlobalMotion();
};
#endif
