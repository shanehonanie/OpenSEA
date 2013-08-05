/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date              Author                  Description
 *---------------------------------------------------------------------------------------------------------------------
 *Aug 03 2013       Nicholas Barczak        Initially created
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
 * This class provides the functionality to translate between input coefficients in the body class and the force
 * coefficients in the matBody class.  Most important, it acts as an interface for advanced users to enter their own
 * equations of motion.  This was devised to create a very generic interface that could allow any sort of definition
 * for equations.  The use of functions for the class should use the following sequence.
 * 1.)  Create class:  constructor
 * 2.)  Set body data (if not already done in constructor):  setListBodies
 * 3.)  Set the current body working with:  setBody
 * 4.)  Set the current wave frequency working with:  setFreq
 * 5.)  Set whether calculating coefficients or values (default:  Values):  calcCoefficient
 * 6.)  Reset the forces you wish to use.
 * 7.)  Set the new list of forces you wish to use.:
 *      useForceAct_usr
 *      useForceAct_hydro
 *      useForceReact_usr
 *      useForceReact_hydro
 *      useForceCross_usr
 *      useForceCross_hydro
 *      useForceMass
 * 7.)  Evaluate the motion model to produce a single complex value result.
 */
#ifndef MOTIONMODEL_H
#define MOTIONMODEL_H
#include <vector>
#include <complex>
#include "../motion_solver/body.h"
#include "equationofmotion.h"
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif
#include "../motion_solver/body.h"

using namespace std;
using namespace arma;

//######################################### Class Separator ###########################################################
class motionModel
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Default constructor.
     *
     * Default constructor.
     */
    motionModel();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Constructor.  This is the preferred constructor as it supplies the body data.
     * @param listBodIn The vector of the body objects to input.
     */
    motionModel(const vector<Body> &listBodIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * Default destructor.
     */
    ~motionModel();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Inputs the list of body data.
     * @param listBodIn The vector of body objects to input.
     */
    void setListBodies(const vector<Body> &listBodIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the index for the body that all calculations are based on.
     * @param Integer input specifying the number of the body to use.  Integer corresponds to the sequence of bodies
     * in the vector supplied with the body.
     */
    void setBody(int bod);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Determines whether the class should calculate force coefficients or actual force values.
     * True = Calculate force coefficients only.
     * False = Calculate force values.
     * Default = (False) Calculate force values.
     * @param Boolean to determine whether should calculate coefficients or values.
     */
    void calcCoefficient(bool calc);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Resets the class data to have all input coefficients.  Any evaluation after a reset will produce a
     * value of zero.  Force coefficients will be zero and force values will be zero.
     */
    void Reset();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the current operating frequency for the function.  Only necessary when calculating true forces
     * and using derivatives defined in the motion model.  Otherwise, you can safely ignore this function.
     * @param Double precision value that sets the current wave frequency value.
     */
    void setFreq(double freq);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param eqn Integer specifying which equation to use in the selected force.
     */
    void useForceAct_usr(int force, int eqn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param eqn Integer specifying which equation to use in the selected force.
     */
    void useForceAct_hydro(int force, int ord, int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param ord Integer specifying which order of derviative to use for the selected force.
     * @param eqn Integer specifying which equation to use in the selected force.
     * @param var Integer specifying which variable to use from the selected equation.
     */
    void useForceReact_usr(int force, int ord, int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param ord Integer specifying which order of derviative to use for the selected force.
     * @param eqn Integer specifying which equation to use in the selected force.
     * @param var Integer specifying which variable to use from the selected equation.
     */
    void useForceReact_hydro(int force, int ord, int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param ord Integer specifying which order of derviative to use for the selected force.
     * @param eqn Integer specifying which equation to use in the selected force.
     * @param var Integer specifying which variable to use from the selected equation.
     */
    void useForceCross_usr(int force, int ord, int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param force Integer specifying which force to use in the set of forces for the given force type.
     * @param ord Integer specifying which order of derviative to use for the selected force.
     * @param eqn Integer specifying which equation to use in the selected force.
     * @param var Integer specifying which variable to use from the selected equation.
     */
    void useForceCross_hydro(int force, int ord, int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Passes information to the object to use input coefficients from the entry specified.
     *
     * Passes information to the object to use input coefficients from the entry specified.  Limits inputs to
     * only the force object type specified by the method.  Calls to useForce methods are cumulative.  Sucessive calls
     * to different entries in the same force sequence will add their coefficients to the sets for evaluation.  Can be
     * combined with other useForce methods.  Multiple calls to the same useForce method with the same index coordinates
     * are not cumulative.  An input coefficient can either be on or off, not multiple instances of the exact same
     * coefficient.
     * @param eqn Integer specifying which equation to use in the selected force.
     * @param var Integer specifying which variable to use from the selected equation.
     */
    void useForceMass(int eqn, int var);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Triggers evaluation of the currently activated set of input coefficients.
     *
     * Triggers evaluation of the currently activated set of input coefficients.  If Calc_Coeff is set to True, then
     * evaluation will only generate the force coefficients from the resulting evaluation.  Otherwise, the evaluation
     * will use the currently defined solution data and evaluate for force values.
     * @param eqn Integer representing which equation object to evaluate.
     * @return Returns a complex number representing the force under the currently set conditions.
     */
    complex<double> Evaluate(int eqn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Reports the number of equations used in the motion model.
     *
     * Reports the number of equations used in the motion model.  This lets the matBody object know how many
     * equations to prepare for.
     * @return Returns the number of equations used in the motion model.
     */
    int numEquations();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns a vector containing all equation indices.  This may be the same as the number of equations.  Very
     * few equations may be used.  However, if they are custom equations, they must avoid the first six indices, which
     * are reserved for standard 6dof models.
     * @return Returns the highest count of the equation index.
     */
    vector<int> DataIndex();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the maximum number of the data index.
     *
     * Returns the maximum number of the data index.  This may be the same as the number of equations.  Very
     * few equations may be used.  However, if they are custom equations, they must avoid the first six indices, which
     * are reserved for standard 6dof models.
     * @return Returns integer number representing the maximum number of the data index found from all equations.
     */
    int MaxDataIndex();

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Pointer to the bodies vector.
     *
     * Pointer to the bodies vector.
     */
    vector<Body> &listBody;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Vector containing the currently activated body data.  A call to the Reset method copies all data over
     * to this list and fills it with Body objects that contain the same number and sizes of forces as the originals,
     * but all entries within the copied objects are zeros.
     */
    vector<Body> listData;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Current wave frequency.  Used for calculating derivatives.
     */
    double pFreq;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of equations of motion to use in the motion model.  The sequence of equations in the list is
     * important.  Equations appear in the list as they appear in the matrix model of the body.
     */
    vector<EquationofMotion*> listEquations;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets whether the force coefficients should be calculated, or values of response.
     */
    bool calcCoeff;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Copies the matrix and outputs a matrix that is the same size, but filled with zeros.
     * @param The matrix to copy.  Matrix of double precision floating numbers.
     */
    Mat<double> CopyZero(Mat<double> &copyMat);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The current body to perform calculations on.
     */
    int curBody;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Checks to make sure the number of bodies matches the input data.  If not, fills out the body data.
     *
     * Checks to make sure the number of bodies matches the input data.  If not, fills out the body data.  Operates
     * on listData vector.  Adds items to the vector and assigns basic properties to those items.
     */
    void fillBodies();
};

#endif // MOTIONMODEL_H
