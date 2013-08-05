/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date          Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15, 2013  Shane Honanie       Initially created.
 *
\*-------------------------------------------------------------------------------------------------------------------*/

//License
/*-------------------------------------------------------------------------------------------------------------------*\
 *Copyright Datawave Marine Solutions, 2013.
 *This file is part of OpenSEA.

 *OpenSEA is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *OpenSEA is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with OpenSEA.  If not, see <http://www.gnu.org/licenses/>.
\*-------------------------------------------------------------------------------------------------------------------*/



//######################################### Class Separator ###########################################################
/**
 * This class holds all of the data for the forces objects.
 */

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

class UserForces
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
	UserForces(); /**< The default constructor */

    //------------------------------------------Function Separator ----------------------------------------------------
	~UserForces(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Adds a new force to the list.
	 * @param newForceName The name of the force.
	 */
	void addNewForce(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the coefficients.
	 * @param theListIn The list of coefficients.
	 * @param isDirectList Specifies whether the list is direct or sequential.
	 */
	void setCoeff(vector<string>, bool); 

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the current order derivative.
	 * @param newOrder The order derivative.
	 */
	void setOrderDerivative(int);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the current equation number.
	 * @param newEquationNum The number if the equation.
	 */

    //------------------------------------------Function Separator ----------------------------------------------------
	void setEquationNumber(int);
	void setCurForceAsActive(); /**< Set the current force as an active force. */
	void setCurForceAsReactive(); /**< Set the current force as a reactive force. */
	void setCurForceAsCrossBody(); /**< Set the current force as a cross body force force. */
	void testPrint(); /**< Test print to console the values of all data members. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Retrieve the active force by name.
	 * @param activeForceName The name of the active force.
	 * @return Return the active force if found.
	 */
	vector<complexDouble> getUserActiveForce(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Retrieve the reactive force by name.
	 * @param reactiveForceName The name of the reactive force.
	 * @return Return the reactive force if found.
	 */
	vector<Derivative> getUserReactiveForce(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Retrieve the cross body force by name.
	 * @param crossBodyForceName The name of the cross body force.
	 * @return Return the cross body force if found.
	 */
	vector<Derivative> getUserCrossBodyForce(string);

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
	vector<forceActive> userActiveForces; /**< The list of all user active forces. */
	vector<forceReact> userReactiveForces; /**< The list of all user reactive forces. */
	vector<forceCross> userCrossBodyForces; /**< The list of all user cross body forces. */
	int curForceType; /**< Represents the current force type. */
	int ACTIVE_FORCE; /**< int assigned to represent active force type. */
	int REACTIVE_FORCE; /**< int assigned to represent reactive force type. */
	int CROSSBODY_FORCE; /**< int assigned to represent cross body force type. */
};
#endif
