#ifndef OUTPUTDERIVED_H
#define OUTPUTDERIVED_H
#include "../motion_solver/body.h"
using namespace std;

/**
 * This abstract class represents the Derived Outputs.
 */

class OutputDerived
{
public:
	OutputDerived(); /**< This default constructor creates a Output Derived object. */
	~OutputDerived(); /**< The default destructor, nothing happens here. */
	Body theBody; /**< Holds a reference to the body for outputs. */
	int curWaveDirection; /**< The current wave direction. */
	string name; /**< The name.?? NEEDS TO BE FIXED */

	/**
	 * Child class mus implement "Calculates the outputs".
	 * @param matrixIn The original Matrix that is used for calculations.
	 * @param curWaveFreq The current wave frequency.
	 * @return The new matrix with calculations on each index.
	 */
	virtual cx_mat calculateOutput(cx_mat,double) = 0;
};
#endif
