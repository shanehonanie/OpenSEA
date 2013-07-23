#ifndef GLOBALACCELERATION_H
#define GLOBALACCELERATION_H
#include "globalsolution.h"
using namespace std;

const string ACCELERATION_NAME = "accglobal"; /**< Used for reference in file output. */

/**
 * This class represents the Global Acceleraion Solution.
 */

class GlobalAcceleration : public GlobalSolution
{
public:
	GlobalAcceleration(); /**< This default constructor creates a Global Acceleration object. */
	~GlobalAcceleration(); /**< The default destructor, nothing happens here. */
};
#endif
