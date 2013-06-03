#ifndef FORCEDERIVATIVE_H
#define FORCEDERIVATIVE_H
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int MAX_EQUATIONS = 6;

/**
 * This class holds data for a derivative.
 */

class Derivative
{
public:
	Derivative(); /**< This default constructor creates a Body object. */
	~Derivative(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */
	Equation equationList[MAX_EQUATIONS]; /**< The list of equations. */

	/**
	 * Retrieve the size of the equation list.
	 * @return The size of the equation list.
	 */
	int getEquationListSize();
private:

};
#endif

