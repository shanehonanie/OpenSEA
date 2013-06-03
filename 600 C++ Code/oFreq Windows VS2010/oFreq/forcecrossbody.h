#ifndef FORCECROSSBODY_H
#define FORCECROSSBODY_H
#include "forcereactive.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds data for a cross body force.
 */

class ForceCrossBody: public ForceReactive
{
public:
	ForceCrossBody(); /**< This default constructor creates a Body object. */
	~ForceCrossBody(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */
};
#endif

