#ifndef EQUATIONOFMOTION_H
#define EQUATIONOFMOTION_H
#include <math.h>
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"

using namespace arma;
using namespace std;

/**
 * This abstract class holds for data for an equaion of motion.
 */

class EquationOfMotion
{
public:
	EquationOfMotion(); /**< The default constructor. */
	~EquationOfMotion(); /**< The default destructor, nothing happens here. */

	/**
	 * Sets the current wave frequency to be used.
	 * @param newFreqIn The current wave frequency.
	 */
	void setWaveFreq(double);

	/**
	 * This pure virtual function must be implemented by child classes.
	 * @param The Body.
	 * @param The User Forces.
	 */
	virtual void setBodyData(Body, UserForces) = 0;

	/**
	 * Retrieve the body with force matrix object.
	 * @return The body with force matrix object.
	 */
	BodyWithForceMatrix getBodyForceData();

	/**
	 * Retrieve the body with force matrix object.
	 * @param num1 An int.
	 * @param num2 An int.
	 * @return Return 0 if two numbers are equal or 1 if not.
	 */
	double kroneckerDelta(int, int);

	/**
	 * Computes the time differention on the values passed in.
	 * @param variable A force coefficient.
	 * @param order The order derivative.
	 * @return Returns the computed time differentiation.
	 */
	complexDouble timeDifferentiation(complexDouble, int); 

	//TO DO : This may need to be provate
	BodyWithForceMatrix newBodyMatrix; /**< The Body with force matrix object.. */
private:
	double curWaveFreq; /**< The current wave frequency. */
};
#endif
