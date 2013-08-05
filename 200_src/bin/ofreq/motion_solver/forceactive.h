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
 * This class holds data for an active force.
 */

#ifndef FORCEACIVE_H
#define FORCEACTIVE_H
#include "force.h"
#include "equation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
using namespace std;

typedef complex<double> complexDouble;

class forceActive: public Force
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    forceActive(); /**< The default constructor. */

    //------------------------------------------Function Separator ----------------------------------------------------
    ~forceActive(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
	void testPrint(); /**< Test print to console the values of all data members. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Converts string in rectanguluar form to a complex number.
	 * @param expression The string in Rectanguluar form.
	 * @return a complex number.
	 */
	complexDouble convertRectangularFormToComplexNumber(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Converts string in polar form to a complex number.
	 * @param expression The string in polar form.
	 * @return a complex number.
	 */
	complexDouble convertPolarFormToComplexNumber(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Set the coefficients.
	 * @param theListIn The list of coefficients.
	 * @param isDirectList Specifies whether list of coefficients is direct list or sequential list.
	 */
	void setCoeff(vector<string>, bool); 

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Retrieve the list of coefficients.
	 * @return The list of coefficients.
	 */
    vector<complexDouble> &getCoefficients();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Another implementation of function getCoefficients.
     * @return Vector containing the list of coefficients.  Argument passed by reference.
     */
    vector<complexDouble> &Equations();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Get a specific number from the list of coefficients.
     *
     * Get a specific number from the list of coefficients.  Similar to getCoefficients(), only instead of returning
     * the entire vector of coefficients, this only returns a single value in the list.
     * @param number Integer specifying which number should be retrieved from the list.
     * @return Double which is the input coefficient for the active force on the equation specified by number.  Returns
     * by value, not by reference.
     */
    double getEquation(int number);

//==========================================Section Separator =========================================================
protected:
    //------------------------------------------Function Separator ----------------------------------------------------
    vector<complexDouble> coefficients; /**< The list of force coeffients. */

//==========================================Section Separator =========================================================
private:

};
#endif
