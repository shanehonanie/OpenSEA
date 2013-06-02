#ifndef GLOBALVELOCITY_H
#define GLOBALVELOCITY_H
#include "globalsolution.h"
using namespace std;

const string VELOCITY_NAME = "velglobal"; /**< Used for reference in file output. */

/**
 * This class represents the Global Velocity Solution.
 */

class GlobalVelocity : public GlobalSolution
{
public:
	GlobalVelocity(); /**< This default constructor creates a Global Velocity object. */
	~GlobalVelocity(); /**< The default destructor, nothing happens here. */
};
#endif
