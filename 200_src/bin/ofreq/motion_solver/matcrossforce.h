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
 *Aug 01 2013   Nicholas Barczak    Initially created
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
 *This class defines the cross body force matrix.  It is an extension of the reactive force matrix class.  The main
 *difference is that this class includes an additional property for the connected body.
 */

#ifndef MATCROSSFORCE_H
#define MATCROSSFORCE_H
#include "matreactforce.h"
#include "matbody.h"
#include <vector>
#include <complex>
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

using namespace arma;
using namespace std;

//######################################### Class Separator ###########################################################
//Createa a forward declaration of class matBody to keep the compiler happy.
//The full definition for class matBody happens later in file matbody.h.
class matBody;


//######################################### Class Separator ###########################################################
class matCrossForce : matReactForce
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * The default constructor
     */
    matCrossForce();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The constructor.  Takes a vector of complex matrices and stores them as derivatives.
     *
     * The constructor.  Takes a vector of complex matrices and stores them as derivatives.  Assumes that the matrices
     * in the vector are order in sequence of increasing order of derivative. (index 0 = derivative order 0.)
     * @param forceIn The list of forces.
     */
    matCrossForce(vector<cx_mat> forceIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * The default destructor.  Nothing happens here.
     */
    ~matCrossForce();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Operator overload to add two matCrossForce objects together.
     *
     * This overloads the + operator to add two matCrossForce objects together.  Functions are added on a per-derivative
     * basis.  The function recognizes the derivative matrices contained within each object.  Only derivatives of the
     * same order are added together.  The function also checks the linked body parameter.  Only objects with the
     * same linked body are added together.
     * @param forceOther The other objects of type matCrossForce that will be added.
     * @return Returns an object of type matCrossForce.  The new object will contain the same order of derivatives as
     * the highest derivative of the two added functions.
     */
    matCrossForce operator+(const matCrossForce& forceOther);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Operator overload to subtract two matCrossForce objects together.
     *
     * This overloads the - operator to subtract two matCrossForce objects together.  Functions are subtracted on a
     * per-derivative basis.  The function recognizes the derivative matrices contained within each object.
     * Only derivatives of the same order are subtracted together.  Order of operations does matter.
     * The function also checks the linked body parameter.  Only objects with the
     * same linked body are added together.
     * @param forceOther The other objects of type matCrossForce that will be subtracted.  forceOther is always
     * subtracted from the calling object.
     * @return Returns an object of type matCrossForce.  The new object will contain the same order of derivatives as
     * the highest derivative of the two subtracted functions.
     */
    matCrossForce operator-(const matCrossForce& forceOther);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * Set linked body for cross body object.
     * @param BodIn pointer to the matBody object that this linked force relates to.
     */
    void setlinkedbody( int & BodIn );

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * Return the linked body for the cross body object
     * @return Returns a pointer to the matBody object that this force relates to.
     */
    matBody getlinkedbody();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the id of the linked body.
     *
     * Sets the id of the linked body.  The id is like the body's name.  This is normally the index of the body
     * within the vector of other bodies.
     * @param bodId The integer of the body id.  This is normally the index of the body within the vector of other
     * bodies.
     */
    void setlinkedId(int bodId);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the id of the linked body.
     *
     * Gets the id of the linked body.  The id is like the body's name.  This is normally the index of the body
     * within the vector of other bodies.
     * @return Integer value which is the body's id.  This is normally the index of the body within the vector of other
     * bodies.
     */
    int getlinkedId();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the size of the matrix in each order of derivative.
     *
     * Returns the size of the matrix in each order of derivative.  Integer output type.  Reports both number of columns
     * and number of rows.  Vector of 2 integers output.
     * @return Returns a vector of two integers specifying size of matrix.  First output is number of rows. Second
     * output is number of columns.
     */
    vector<int> getmatDims();

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    int plinkbody;
    int plinkid;

};

#endif // MATCROSSFORCE_H
