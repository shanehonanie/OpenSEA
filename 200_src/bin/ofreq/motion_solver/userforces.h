#ifndef USERFORCES_H
#define USERFORCES_H
#include "forceactive.h"
#include "forcereactive.h"
#include "forcecrossbody.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef complex<double> complexDouble;

/**
 * This class holds all of the data for the forces objects.
 */

class UserForces
{
public:
	UserForces(); /**< The default constructor */
	~UserForces(); /**< The default destructor, nothing happens here. */

	/**
	 * Adds a new force to the list.
	 * @param newForceName The name of the force.
	 */
	void addNewForce(string);

	/**
	 * Sets the coefficients.
	 * @param theListIn The list of coefficients.
	 * @param isDirectList Specifies whether the list is direct or sequential.
	 */
	void setCoeff(vector<string>, bool); 

	/**
	 * Sets the current order derivative.
	 * @param newOrder The order derivative.
	 */
	void setOrderDerivative(int);

	/**
	 * Sets the current equation number.
	 * @param newEquationNum The number if the equation.
	 */
	void setEquationNumber(int);
	void setCurForceAsActive(); /**< Set the current force as an active force. */
	void setCurForceAsReactive(); /**< Set the current force as a reactive force. */
	void setCurForceAsCrossBody(); /**< Set the current force as a cross body force force. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Retrieve the active force by name.
	 * @param activeForceName The name of the active force.
	 * @return Return the active force if found.
	 */
	vector<complexDouble> getUserActiveForce(string);

	/**
	 * Retrieve the reactive force by name.
	 * @param reactiveForceName The name of the reactive force.
	 * @return Return the reactive force if found.
	 */
	vector<Derivative> getUserReactiveForce(string);

	/**
	 * Retrieve the cross body force by name.
	 * @param crossBodyForceName The name of the cross body force.
	 * @return Return the cross body force if found.
	 */
	vector<Derivative> getUserCrossBodyForce(string);

private:
	vector<ForceActive> userActiveForces; /**< The list of all user active forces. */
	vector<ForceReactive> userReactiveForces; /**< The list of all user reactive forces. */
	vector<ForceCrossBody> userCrossBodyForces; /**< The list of all user cross body forces. */
	int curForceType; /**< Represents the current force type. */
	int ACTIVE_FORCE; /**< int assigned to represent active force type. */
	int REACTIVE_FORCE; /**< int assigned to represent reactive force type. */
	int CROSSBODY_FORCE; /**< int assigned to represent cross body force type. */
};
#endif
