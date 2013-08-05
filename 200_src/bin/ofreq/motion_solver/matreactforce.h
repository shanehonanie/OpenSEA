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
 *May 15, 2013	Shane Honanie       Initially created
 *Aug 02, 2013  Nicholas Barczak    Added operator overloads and more consistent matrix definition of forces.
 *                                  Also added methods for derivative access.
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
 * This class holds data for reactive force matrix whch includes force coefficients.
 */

#ifndef MATREACTFORCE_H
#define MATREACTFORCE_H
#include <complex>
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

using namespace arma;
using namespace std;
//const int MAX_ORDER_DERIVATIVE = 3;

typedef complex<double> complexDouble;

class matReactForce
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    matReactForce(); /**< The default constructor. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
     * @brief The constructor.  Takes a vector of complex matrices and stores them as derivatives.
     *
     * The constructor.  Takes a vector of complex matrices and stores them as derivatives.  Assumes that the matrices
     * in the vector are order in sequence of increasing order of derivative. (index 0 = derivative order 0.)
     * @param forceIn The list of forces.
	 */
    matReactForce(vector<cx_mat> forceIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    ~matReactForce(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Operator overload to add two matReactForce objects together.
     *
     * This overloads the + operator to add two matReactForce objects together.  Functions are added on a per-derivative
     * basis.  The function recognizes the derivative matrices contained within each object.  Only derivatives of the
     * same order are added together.
     * @param forceOther The other objects of type matReactForce that will be added.
     * @return Returns an object of type matReactForce.  The new object will contain the same order of derivatives as
     * the highest derivative of the two added functions.
     */
    virtual matReactForce operator+(const matReactForce& forceOther);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Operator overload to subtract two matReactForce objects together.
     *
     * This overloads the - operator to subtract two matReactForce objects together.  Functions are subtracted on a
     * per-derivative basis.  The function recognizes the derivative matrices contained within each object.
     * Only derivatives of the same order are subtracted together.  Order of operations does matter.
     * @param forceOther The other objects of type matReactForce that will be subtracted.  forceOther is always
     * subtracted from the calling object.
     * @return Returns an object of type matReactForce.  The new object will contain the same order of derivatives as
     * the highest derivative of the two subtracted functions.
     */
    virtual matReactForce operator-(const matReactForce& forceOther);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The maximum order of the derivatives.
     *
     * The maximum order of the derivatives (Integer).  Also the total size of the vector containing the derivatives.
     * @return Returns the maximum order of derivatives in the force.
     */
    int getmaxOrder();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Derivative Returns the full vector of derivatives.
     *
     * Derivative Returns the full vector of derivatives.
     * @return  Returns the full vector of derivatives.  Passed as values, not as references.
     */
    vector<cx_mat> getDerivative();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Derivative Returns the complex matrix for only the order of derivative specified.
     *
     * Derivative Returns the complex matrix for only the order of derivative specified.
     * @param order Integer input to specify the order of the derivative.
     * @return Returns a complex matrix that contains the force coefficients for the given order of derivative.  Passed
     * as a value.
     */
    cx_mat getDerivative(int order);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Inputs a derivative matrix
     * @param order The order of the derivative matrix.  Also is sequence in the vector that contains the matrices.
     * @param Coeff The matrix of complex numbers that contains the force coefficients for the derivative.  Passed as a
     * value, not a reference.
     */
    void setDerivative(int order, cx_mat Coeff);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the force id number for the object.
     *
     * This is similar to the name parameter in other force objects.  It is an identifier.  In this case, a numerical
     * identifier.  Normally correlates to the objects index in a vector of other objects of the same class.
     * @param num The integer number to input as the objects integer id.
     */
    void setId(int num);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the force id number for the object.
     *
     * This is similar to the name parameter in other force objects.  It is an identifier.  In this case, a numerical
     * identifier.  Normally correlates to the objects index in a vector of other objects of the same class.
     * @return Returns the force id number, integer data type.
     */
    int getId();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the size of the matrix in each order of derivative.
     *
     * Returns the size of the matrix in each order of derivative.  Integer output type.
     * @return Returns the size of the matrix in each order of derivative.
     */
    int getMatSize();

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Defines the vector of derivatives.
     *
     * Defines the vector of derivatives.  Each entry in vector represents the order of the derivative.
     */
    vector<cx_mat> pderiv;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief the number of the object in the outside vector that contains it.
     *
     * This is similar to the name parameter in other force objects.  It is an identifier.  In this case, a numerical
     * identifier.  Normally correlates to the objects index in a vector of other objects of the same class.
     */
    int pId;

};
#endif
