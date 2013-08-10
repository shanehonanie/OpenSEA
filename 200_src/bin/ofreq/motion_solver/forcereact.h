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
 * This class holds all of the data for a reactive force.
 */

#ifndef FORCEREACTIVE_H
#define FORCEREACTIVE_H
#include "force.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "derivative.h"
using namespace std;

class forceReact: public Force
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    forceReact(); /**< This default constructor. */

    //------------------------------------------Function Separator ----------------------------------------------------
    ~forceReact(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
	void testPrint(); /**< Test print to console the values of all data members. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the list of coeffcients.
	 * @param newList The list of coefficients.
	 * @param isDirectList Specifies whether the list is direct or sequential.
	 */
	void setCoeff(vector<string>, bool);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the current derivative.
	 * @param neworder The order of derivative.
	 */
	void setCurDerivative(int);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the current number of the equation.
	 * @param newEquationNum The number of the equation.
	 */
	void setCurEquationNum(int);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
     * Retrieve the derivatives list.
     * @return The order derivative of this object.  Returned object is by value.
	 */
    vector<Derivative> getDerivatives();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Another implementation of getDerivatives, under a different name.
     * @return Returns the vector of derviative objects.  Returned object is by reference.
     */
    vector<Derivative> &Derivatives();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Retrieve the derivative object specified by the index number.
     *
     * Retrieve the derivative object specified by the index number.
     * @param num The index number of the derivative object.
     * @return Returns the derivative object specified by integer num.  Returned value is by value.
     */
    Derivative getDerivative(int num);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Retrieve the derivative object specified by the index number.
     *
     * Retrieve the derivative object specified by the index number.  Retrieves a pointer to the derivative object.
     * @param num The index number of the derivative object.
     * @return Returns a pointer to the derivative object specified by integer num.  Returned value is by reference.
     */
    Derivative &refDerivative(int num);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the maximum order of the derivatives included in the force object.
     *
     * Returns the maximum order of the derivatives included in the force object.
     * @return Returns integer.  Returns the maximum order of the derivatives included in the force object.  Returned
     * result passed by value.
     */
    int getMaxOrd();

//==========================================Section Separator =========================================================
protected:
    //------------------------------------------Function Separator ----------------------------------------------------
    vector<Derivative> pDerivative; /**< This list of derivatives. */
	int currentDerivative; /**< The current order derivative. */
	int currentEquation; /**< This current equation number. */

//==========================================Section Separator =========================================================
private:

};
#endif

