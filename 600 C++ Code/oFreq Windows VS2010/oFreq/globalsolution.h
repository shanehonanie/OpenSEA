#ifndef GLOBALSOLUTION_H
#define GLOBALSOLUTION_H
#include "outputderived.h"
#include "armadillo"

using namespace std;
using namespace arma;

const int GLOBAL_MOTION_DERIVATIVE = 0; /**< Used for referencing Global Motion Derivative */
const int GLOBAL_VELOCITY_DERIVATIVE = 1; /**< Used for referencing Global Velocity Derivative */
const int GLOBAL_ACCELERATION_DERIVATIVE = 2; /**< Used for referencing Global Acceleration Derivative */

typedef complex<double> complexDouble; /**< Simple typedef for complexDouble represents complex<double> */

/**
 * This class represents the Global Solution.
 */

class GlobalSolution : public OutputDerived
{
public:
	GlobalSolution(); /**< This default constructor creates a Global Solution object. */
	~GlobalSolution(); /**< The default destructor, nothing happens here. */
	int orderDerivative; /**< Set by child classes */

	/**
	 * Calculates the outputs for Global Solution children classes
	 * @param matrixIn The original Matrix that is used for calculations.
	 * @param curWaveFreq The current wave frequency.
	 * @return The new matrix with calculations on each index.
	 */
	virtual cx_mat calculateOutput(cx_mat,double);
};
#endif
