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
 *May 15, 2013	Shane Honanie		Initially Created
 *Aug 01, 2013  Nicholas Barczak    Added support for unlimited number of bodies in assembled global motion matrix.
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
 * This class holds data for the motion solver and performs calculations on all of the data to get the solution matrix.
 * The motion solver performs a series of operations.
 * 1.)  Sum each force object for all forces within a set.
 * 2.)  Sum each force object for all the derivatives defined within each force.  Applied frequency dependence.
 * 3.)  Sum user reactive forces, hydro reactive forces, and body mass into a single object for each body.
 * 4.)  Sum user cross-body forces, hydro cross-body forces into a single object for each body.
 * 5.)  Sum user active forces and hydro active forces into a single object for each body.
 * 6.)  Assemble reactive forces and cross-body forces into a single global response matrix. ([A])
 * 7.)  Assemble active forces into a single global active force matrix. ([F])
 * 8.)  Solve the linear system system of equations formed by the equation [A] * [x] = [F]
 * 9.)  Redistribute the solution back to each body object.
 */

#ifndef MOTIONSOLVER_H
#define MOTIONSOLVER_H
#include <complex>
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif
#include "matbody.h"
#include "matreactforce.h"
#include "matcrossforce.h"

using namespace arma;
using namespace std;

class MotionSolver
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The default constructor.
     */
    MotionSolver();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Constructor.  Initialize with objects already added.
     *
     * This constructor combines creation of the class with adding the body objects to the class at the same time.
     * The list of matBody objects is added to the set of bodies that the motion solver solves.  Bodies inputs are
     * passed by value, and not by reference.
     * @param listBodIn The vector list of bodies to add to the motion solver object.
     */
    MotionSolver(vector<matBody> listBodIn);

    //------------------------------------------Function Separator ----------------------------------------------------
	~MotionSolver(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Add a body to the motion solver set.
     *
     * Add a body to the motion solver set.  After initialization, this is how the motion solver gets the correct data
     * to perform math operations on.
     * @param The matBody object to add the motion solver set.  Body inputs are added passed by value, and not by
     * reference.
     */
    void AddBody(matBody bodIn);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
     * @brief Sum Reactive forces for each set.
     *
     * Sum Reactive forces for each set.  This iterates through each reactive force in a set and adds the forces
     * together.  It respects derivatives in the summation.
     * @param listForces The list of reactive forces associated with each body.  This list may be anything from
     * zero to infinite number of entries.
     * @return The sum of reactive force matrices.
	 */
    matReactForce sumReactSet(vector<matReactForce> listForces);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sum cross-body forces for each set.
     *
     * Sum cross-body forces for each set.  This gets handled a little differently from reactive forces, as the linked
     * body for the force depends on whether two objects are summed together.  Output from this function is a
     * vector of cross-body forces.  Each entry in the vector contains a cross-body force object.
     * @param CrossBodMat The vector of cross-body force matrices.
     * @return A vector of complex matrices, with each entry in the vectors representing a cross-body force linked to
     * a specific body.
     */
    vector<matCrossForce> sumCrossSet(vector<matCrossForce> listForces);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
     * @brief Sum active forces for each set.
     *
	 * Sum active forces for each set.
     * @param listForces The active force matrix.
	 * @return The sum of active force matrix.
	 */
    cx_mat sumActiveSet(vector<cx_mat> listForces);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
     * @brief Sum Derivatives for reactive force matrix.
     *
	 * Sum Derivatives for reactive force matrix.
	 * @param theReactiveForceMatrix The reactive force matrix.
	 * @return TSingle matrix that is the sum of Matrices passed in.
	 */
    cx_mat sumDerivative(matReactForce forceIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sum Derivatives for reactive force matrix.
     *
     * Sum Derivatives for reactive force matrix.
     * @param forceIn the matrix that contains the set of cross body forces.
     * @return Single matrix that contains the cross body forces for a single definition.
     */
    vector<cx_mat> sumDerivative(vector<matCrossForce> forceIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the current wave frequency.
     *
     * Sets the current wave frequency.  This is used in calculating the summations and must be set before calling
     * the solve method.
     * @param freqIn The input wave frequency.  A double precision floating point value.  Used when summing derivatives.
     */
    void setWaveFreq(double freqIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Calculate the Solution and return the solutions for each body.
     *
     * Calculate the Solution and return the solutions for each body.
     * @return A list of solutions for each body.
     */
    vector<cx_mat> CalculateOutputs();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Get the solution for the solved equation.
     *
     * Get the solution for the solved equation.  Returns the full vector of complex matrices.  Each element in the
     * vector is a solution matrix specific to the body.  The vector is ordered in the same sequence that the bodies
     * were added to the motionsolver object.
     * @return Returns the full vector of complex matrices.  Each element in the
     * vector is a solution matrix specific to the body.  The vector is ordered in the same sequence that the bodies
     * were added to the motionsolver object.
     */
    vector<cx_mat> getSolution();

    //------------------------------------------Function Separator ----------------------------------------------------
    cx_mat getSolution(int bod);



//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    double curWaveFrequency; /**< The current wave frequency */

    //Global Matrices
    cx_mat globReactiveMat; /**< A Matrix (Reactive Force Matrix Global)*/
    cx_mat globActiveMat;   /**< F Matrix (Active Force Matirx Global)*/
    cx_mat globSolnMat;	  /**< X Matrix (Solution Column Matrix)*/

    //Output solution values
    /**
     * @brief The vector list of solutions.
     *
     * The vector list of solutions.  Each entry in the vector contains a matrix of a size specific to each body.
     */
    vector<cx_mat> plistSolution;

    //------------------------------------------Function Separator ----------------------------------------------------
    vector<matBody> plistBody; /**< Body with Force Coefficients */

};
#endif
