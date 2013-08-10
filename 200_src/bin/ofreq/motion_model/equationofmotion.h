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
#include <string>
#include "motionmodel.h"
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
    EquationofMotion(const motionModel &modelIn);

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
    EquationofMotion(const motionModel &modelIn, string NameIn);

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
    EquationofMotion(const motionModel &modelIn, string NameIn, int IndexIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Default destructor.
     */
    ~EquationofMotion();

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
     * @param DataIn The integer of the data index to use.
     */
    void setDataIndex(int DataIn);

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
    int getDataIndex();

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
     * @return Returns a reference to the protected data index variable contained in the class.
     */
    int &DataIndex();

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

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The name for the equation object.
     *
     * The name for the equation object.  This is the short name that user will use to identify the meaning of the
     * equation.
     * @return Returns pointer to the protected pName variable.
     */
    string &Name();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The description for the equation object.
     *
     * The description for the equation object.  This is an expanded version of the name.  Again, purely for user
     * identification of the EquationofMotion object.  Brief names go under the Name property.  More extensive
     * descriptions go under this property.  These would be useful to the user for describing the physical meaning
     * behind the equation of motion.
     * @return Returns pointer to the protected pDescription variable.
     */
    string &Description();

//==========================================Section Separator =========================================================
protected:
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
     * @brief The mathematical kronecker delta function.
     *
     * The mathematical kronecker-delta function.  Used to filter out terms when doing a double summation between
     * two indices.  The function evaluates to one when the two indices are equal, and evaluates to zero any other time.
     * Multiplying a term by the kronecker delta ensures that the results will be filtered to only have terms of
     * equal indices.  If this relates back to a matrix, the kronecked delta filters the deta to only include diagonal
     * terms.
     * @param var1 Integer variable.  The first index that is being summed across.
     * @param var2 Integer variable.  The second index that is being summed across.
     * @param anti Boolean variable.  Sometimes the researcher may be interested in the off diagonal terms.  Cases
     * when var1 does not equatl var2.  In those cases, the kronecker delta function should work in reverse and
     * filter out the diagonal terms in a matrix.  The anti variable is a trigger for the kronecker delta function to
     * work in reverse of its normal method.  The default setting for this variable is false.  By default, the
     * kronecker delta function evaluates with one when var1 = var2.
     * @return Complex number.  Evaluates to either zero (0 + 0j), or one (1 + 0j).
     */
    complex<double> kronecker(int var1, int var2, bool anti = false);

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
     * @param bodIn The body to retrieve variable data for.
     * @return Returns a complex value that is the time differential, transposed into a frequency domain.  If absolute
     * values of response were desired, the function will include the effects of response amplitude.
     */
    complex<double> ddt(int var, int ord, int bodIn=-1);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sums across a variable.
     *
     * Sums across a variable.  The index limits can be specified.  Or the keyword functions can be used to
     * automatically sum across the entire index range.
     * @param force Input to specify which items the results should sum across.  Typically, this is one of the built-in
     * force functions. However, it can be any function, any item, any calculation.  The only catch is that the
     * input value must be a complex<double> data type.
     * @param index String specifying which variable should be summed on.  This may be any one of these options:
     * Order of derivative = "ord"
     * Variable = "var"
     * Body = "bod"
     * @param from Integer for the beginning value of the summation.  Default value of negative one (-1) indicates that
     * the summation will happen at the lowest value of the variable index specified.
     * @param to Integer for the ending value of the summation.  Default value of negative one (-1) indicates that
     * the summation will happen at the highest value of the variable index specified.
     * @return Returns a complex value that is the summation of the index and limits specified.
     */
    complex<double> sum(complex<double> force, string index, int from = -1, int to = -1);

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
     * @param ordIn Integer.  Represents the input variable for the order of derivative.
     * @param varIn Integer.  Represents the input varaible for the variable.
     * @return Returns the data set for the ForceReact_hydro.  Indices can be specified to access individual elements.
     */
    complex<double> ForceReact_hydro(int ordIn, int varIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceReact_user.
     * @param ordIn Integer.  Represents the input variable for the order of derivative.
     * @param varIn Integer.  Represents the input varaible for the variable.
     * @return Returns the data set for the ForceReact_user.  Indices can be specified to access individual elements.
     */
    complex<double> ForceReact_user(int ordIn, int varIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceCross_hydro.
     * @param bodIn Integer.  Represents the input variable for the body that the cross body force is linked to.
     * @param ordIn Integer.  Represents the input variable for the order of derivative.
     * @param varIn Integer.  Represents the input varaible for the variable.
     * @return Returns the data set for the ForceCross_hydro.  Indices can be specified to access individual elements.
     */
    complex<double> ForceCross_hydro(int bodIn, int ordIn, int varIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceCross_user.
     * @param bodIn Integer.  Represents the input variable for the body that the cross body force is linked to.
     * @param ordIn Integer.  Represents the input variable for the order of derivative.
     * @param varIn Integer.  Represents the input varaible for the variable.
     * @return Returns the data set for the ForceCross_user.  Indices can be specified to access individual elements.
     */
    complex<double> ForceCross_user(int bodIn, int ordIn, int varIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief A reference to the data set of the ForceMass.
     * @param varIn Integer.  Represents the input varaible for the variable.
     * @return Returns the data set for the ForceMass.  Indices can be specified to access individual elements.
     */
    complex<double> ForceMass(int varIn);

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
     * @brief Returns the index integer for iteration on order of derviative.
     * @return Returns the index integer for iteration on order of derviative.
     */
    int ord();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the index integer for the current body used by the motion model that created this equation of
     * motions.
     *
     * Returns the index integer for the current body used by the motion model that created this equation of
     * motions.  This index cannot be modified through this function.  It is purely meant for access of the variable.
     * @return Returns the index integer for the current body used by the motion model that created this equation of
     * motions.
     */
    int body();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the maximum number of items that can be iterated through on the variable index.
     *
     * Returns the maximum number of items that can be iterated through on the variable index.  Used for summation
     * functions.  Automatically finds the upper limit of any summation loops.  The lower limit is always 0 and does
     * not require a special function.
     * @return Returns the maximum number of items that can be iterated through on the variable index.
     */
    int maxvar();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the maximum number of items that can be iterated through on the order of derivative index.
     *
     * Returns the maximum number of items that can be iterated through on the order of derivative index.  Used for summation
     * functions.  Automatically finds the upper limit of any summation loops.  The lower limit is always 0 and does
     * not require a special function.
     * @return Returns the maximum number of items that can be iterated through on the order of derivative index.
     */
    int maxord();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the maximum number of items that can be iterated through on the body index.
     *
     * Returns the maximum number of items that can be iterated through on the body index.  Used for summation
     * functions.  Automatically finds the upper limit of any summation loops.  The lower limit is always 0 and does
     * not require a special function.
     * @return Returns the maximum number of items that can be iterated through on the body index.
     */
    int maxbody();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The name for the equation object.
     *
     * The name for the equation object.  This is the short name that user will use to identify the meaning of the
     * equation.
     */
    string pName;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The description for the equation object.
     *
     * The description for the equation object.  This is an expanded version of the name.  Again, purely for user
     * identification of the EquationofMotion object.  Brief names go under the Name property.  More extensive
     * descriptions go under this property.  These would be useful to the user for describing the physical meaning
     * behind the equation of motion.
     */
    string pDescription;

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Reference to the motion model object which created the object.
     *
     * Reference to the motion model object which created the object.  This is necessary because the equation of motion
     * object needs to access several data members that are on the motion model which called it.
     */
    motionModel &pParentModel;

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
     * @brief The integer of the current value of force() index.  Used to track the forces recorded.
     */
    int pCurForce;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer of the current body.  Used for iteration and summation functions.
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
    int pDataIndex;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Used to identify the Equation of Motion object if the DataIndex property doesn't get set.
     *5
     * Used to identify the Equation of Motion object if the DataIndex property doesn't get set.  This integer is set
     * at object creation and then not changed.  If the object needs to lookup its position in the motionmodel object,
     * it can use the private index to identify itself.
     */
    int pPrivateIndex;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The integer of the current value of force() index.  Used to track the forces recorded.
     *
     * The integer of the current value of force() index.  Used to track the forces recorded.  Intentionally kept as a
     * private variable.  The user should not be able to access individual forces within an equation of motion.  The
     * equation of motion can only depend on the type of force, not the individual force designation.
     * @return Returns integer value of the current force object.
     */
    int force();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the index integer for iteration on equation number.
     * @return Returns the index integer for iteration on equation number.
     */
    int eqn();
};

#endif // EQUATIONOFMOTION_H
