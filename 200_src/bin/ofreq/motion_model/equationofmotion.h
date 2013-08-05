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
 * The Equation of motion class defines a single equation of motion.  Each object of the class represents a new
 * instance.  This is the base class, which gets inheritted by any custom class.  The only major definition added
 * to any inherrited class is the actual formula definition for the equation.  It may be that the equation are
 * repetitions of the same sequence, just with a different equation index.  In that case, multiple instances of the
 * same class can be created and the equation index changed.  This can save on typing.  Or, if the equations are truly
 * different for each equation, you can create a separate equation of motion class for each equation, and initiate with
 * just one object from each class.
 *
 * In addition to the regular object entries, the class also has provision for a list of arbitrary arguments.
 */
#ifndef EQUATIONOFMOTIONBASE_H
#define EQUATIONOFMOTIONBASE_H
#include <vector>
#include <complex>
#include <motion_model/motionmodel.h>"
#include <string>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

using namespace std;
using namespace arma;

class EquationofMotion
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Default contrustor.  Contains a reference to the motion model class which constructs it.
     *
     * Default contrustor.  Contains a reference to the motion model class which constructs it.  The constructing class
     * is necessary because several functions in the EquationOfMotion class use data in the constructing class, the
     * motion model class.
     * @param modelIn A pointer to the motion model object that created the equation of motion.
     */
    EquationofMotion(const motModelBase & modelIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Contrustor with name.  Contains a reference to the motion model class which constructs it.
     *
     * Default contrustor.  Contains a reference to the motion model class which constructs it.  The constructing class
     * is necessary because several functions in the EquationOfMotion class use data in the constructing class, the
     * motion model class.
     * @param modelIn A pointer to the motion model object that created the equation of motion.
     * @param NameIn A name for what physical property the equation solves for.  Used for user output.  Not critical
     * to program execution.
     */
    EquationofMotion(const motModelBase & modelIn, string NameIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Contrustor with name and index.  Contains a reference to the motion model class which constructs it.
     *
     * Default contrustor.  Contains a reference to the motion model class which constructs it.  The constructing class
     * is necessary because several functions in the EquationOfMotion class use data in the constructing class, the
     * motion model class.
     * @param modelIn A pointer to the motion model object that created the equation of motion.
     * @param NameIn A name for what physical property the equation solves for.  Used for user output.  Not critical
     * to program execution.
     * @param IndexIn
     */
    EquationofMotion(const motModelBase & modelIn, string NameIn, int IndexIn);


    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Default destructor.
     */
    ~EquationofMotion();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The formula used by the equation of motion.
     *
     * The formula used by the equation of motion.  The formula gets rewritten in a unique form.  Rearrange any
     * equations so that they have zero on the right hand size.
     *
     * Example:  If the formula were Ax + By = F, it must be rearranged to:  Ax + By - F = 0
     *
     * The formula can also make use of several math functions provided by the equation of motion object.
     */
    virtual void Formula();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The mathematical kronecker-delta function.
     *
     * The mathematical kronecker-delta function.  Used to filter out terms when doing a double summation between
     * two indices.  The function evaluates to zero when the two indices are equal, and evaluates to one any other time.
     * Multiplying a term by the kronecker-delta ensures that the results will be filtered to only have terms of
     * unequal indices.  If this relates back to a matrix, the kronecked delta filters the deta to only include off-
     * diagonal terms.
     * @param var1 Integer variable.  The first index that is being summed across.
     * @param var2 Integer variable.  The second index that is being summed across.
     * @return Complex number.  Evaluates to either zero (0 + 0j), or one (1 + 0j).
     */
    complex<double> kronecker(int var1, int var2);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Time differential function.
     *
     * Time differential function.  Used to calculate the time derivative of a reponse.  Can convert from response
     * amplitude to velocity to acceleration, and further.  Used to calculated amplitude of response.
     * @param var Index of the variable to use for the time differential.  If included with the function var(), the
     * index is automatically determined by the summation functions that you include ddt() into.
     * @param ord Integer.  The order of the differential.  If the function ord() is used, the order is automatically
     * determined by the summation function that you include ddt() into.
     * @return Returns a complex value that is the time differential, transposed into a frequency domain.  If absolute
     * values of response were desired, the function will include the effects of response amplitude.
     */
    complex<double> ddt(int var, int ord);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sums acros a variable.
     *
     * Sums across a variable.  The index limits can be specified.  Or the keyword functions can be used to
     * automatically sum across the entire index range.
     * @param from Integer for the beginning value of the summation.
     * @param to Integer for the ending value of the summation.
     * @param force Integer to specify which force function the results should sum across.
     * @param index String specifying which variable should be summed on.  This may be any one of these options:
     * Order of derivative = "ord"
     * Variable = "var"
     * @return Returns a complex value that is the summation of the index and limits specified.
     */
    complex<double> sum(int from, int to, complex<double> force, string index);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceActive_hydro.
     * @return Returns the data set for the ForceActive_hydro.  Indices can be specified to access individual elements.
     */
    complex<double> ForceActive_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceActive_user.
     * @return Returns the data set for the ForceActive_user.  Indices can be specified to access individual elements.
     */
    complex<double> ForceActive_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceReact_hydro.
     * @return Returns the data set for the ForceReact_hydro.  Indices can be specified to access individual elements.
     */
    complex<double> ForceReact_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceReact_user.
     * @return Returns the data set for the ForceReact_user.  Indices can be specified to access individual elements.
     */
    complex<double> ForceReact_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceCross_hydro.
     * @return Returns the data set for the ForceCross_hydro.  Indices can be specified to access individual elements.
     */
    complex<double> ForceCross_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceCross_user.
     * @return Returns the data set for the ForceCross_user.  Indices can be specified to access individual elements.
     */
    complex<double> ForceCross_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceMass.
     * @return Returns the data set for the ForceMass.  Indices can be specified to access individual elements.
     */
    complex<double> ForceMass();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Triggers evaluation of the equation of motion object.
     * @return Returns a complex number that is the result of evaluating the equation of motion object.
     */
    complex<double> Evaluate();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the index for the equation of motion.
     *
     * Sets the index for the equation of motion.  The index is how the equation determines which numbers to access
     * on the data.  The following indices are used.  Any higher indices can extend beyond this range, and the program
     * easily adapts.  But the following three are reserved.  Unused indices are not transferred to the matrices when
     * solved.  So unused indices to not negatively impact calculation performance.  However, using excessively large
     * indices (say 500 when you only have 3 equations) will result in large matrices and unecessary memory
     * requirements.  THe following index reservations apply.
     * 1:  Translation in x-direction.
     * 2:  Translation in y-direction.
     * 3:  Translation in z-direction.
     * 4:  Rotation about x-direction.
     * 5:  Rotation about y-direction.
     * 6:  Rotation about z-direction.
     */
    void setIndex();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the index for the equation of motion.
     *
     * Gets the index for the equation of motion.  The index is how the equation determines which numbers to access
     * on the data.  The following indices are used.  Any higher indices can extend beyond this range, and the program
     * easily adapts.  But the following three are reserved.  Unused indices are not transferred to the matrices when
     * solved.  So unused indices to not negatively impact calculation performance.  However, using excessively large
     * indices (say 500 when you only have 3 equations) will result in large matrices and unecessary memory
     * requirements.  THe following index reservations apply.
     * 1:  Translation in x-direction.
     * 2:  Translation in y-direction.
     * 3:  Translation in z-direction.
     * 4:  Rotation about x-direction.
     * 5:  Rotation about y-direction.
     * 6:  Rotation about z-direction.
     * @return Returns an integer number representing the data index used by the equation.
     */
    int getIndex();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets any values for arguments that may be used by the equation of motion.
     *
     * Sets any values for arguments that may be used by the equation of motion.  These can be any numerical value
     * as needed by the equation of motion.
     * @param argn The number of arguments to expect.
     * @param argv The vector containing the argument values.
     */
    void setArguments(int argn, vector<double> argv);

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer of the current value of var() index.  Used for iteration and summation functions.
     */
    int pCurVar;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer of the current value of eqn() index.  Used for iteration and summation functions.
     */
    int pCurEqn;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer of the current value of ord() index.  Used for iteration and summation functions.
     */
    int pCurOrd;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer specifying the current body which is active for summation and iteration.
     */
    int pCurBod;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Integer that stores the equation index.  Used to retrieving data from the calling object motion model.
     * Reserved indices are:
     * 1:  Translation in x-direction.
     * 2:  Translation in y-direction.
     * 3:  Translation in z-direction.
     * 4:  Rotation about x-direction.
     * 5:  Rotation about y-direction.
     * 6:  Rotation about z-direction.
     */
    int pEqnIndex;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Used to supply arguments to the equation of motion.  Recods the number of arguments.
     *
     * Used to supply arguments to the equation of motion.  Recods the number of arguments.  Not required for use of
     * the equation of motion object.
     */
    int argcount;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Used to supply arguments to the equation of motion.  Uknown, arbitrary double precision values.
     * A vector of uknown size.
     *
     * Used to supply arguments to the equation of motion.  Uknown, arbitrary double precision values.
     * A vector of uknown size.  Not required for use fo the equation of motion object.
     */
    vector<double> argvalue;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the index integer for iteration on variable.
     * @return Returns the index integer for iteration on variable.
     */
    int var();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the index integer for iteration on equation number.
     * @return Returns the index integer for iteration on equation number.
     */
    int eqn();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the index integer for iteration on order of derviative.
     * @return Returns the index integer for iteration on order of derviative.
     */
    int ord();
};

#endif // EQUATIONOFMOTION_H
