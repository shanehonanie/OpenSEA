#ifndef FORCEREACTIVE_H
#define FORCEREACTIVE_H
#include "force.h"
#include "forcederivative.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int MAX_ORDER_DERIVATIVE = 3;

/**
 * This class holds all of the data for a reactive force.
 */


class ForceReactive: public Force
{
public:
	ForceReactive(); /**< This default constructor. */
	~ForceReactive(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Sets the list of coeffcients.
	 * @param newList The list of coefficients.
	 * @param isDirectList Specifies whether the list is direct or sequential.
	 */
	void setCoeff(vector<string>, bool);

	/**
	 * Sets the current derivative.
	 * @param neworder The order of derivative.
	 */
	void setCurDerivative(int);

	/**
	 * Sets the current number of the equation.
	 * @param newEquationNum The number of the equation.
	 */
	void setCurEquationNum(int);

	/**
	 * Retrieve the order derivative
	 * @return The order derivative of this object.
	 */
	vector<Derivative> getDerivatives();
protected:
	Derivative derivative[MAX_ORDER_DERIVATIVE]; /**< This list of derivatives. */
	int currentDerivative; /**< The current order derivative. */
	int currentEquation; /**< This current equation number. */
	
};
#endif

