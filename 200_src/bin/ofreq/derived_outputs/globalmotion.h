#ifndef GLOBALMOTION_H
#define GLOBALMOTION_H
#include "globalsolution.h"
using namespace std;
const string MOTION_NAME = "motglobal"; /**< Used for reference in file output. */

/**
 * This class represents the Global Motion Solution.
 */

class GlobalMotion : public GlobalSolution
{
public:
	GlobalMotion(); /**< This default constructor creates a Global Motion object. */
	~GlobalMotion(); /**< The default destructor, nothing happens here. */
};
#endif
