/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
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
#include "equationofmotion.h"

//==========================================Section Separator =========================================================
//Public Members
//------------------------------------------Function Separator --------------------------------------------------------
EquationofMotion::EquationofMotion(motionModel &modelIn)
{
    //Default constructor.  Requires declaration
    //of the object which created the equation object.

    //Assign the calling body to private variable.
    pParentModel = modelIn;

    //Create default value for data index.
    pDataIndex = -1;

    //Set the private index as a backup to an unset Data index value.
    pPrivateIndex = pParentModel.listEquations.size() - 1;
}

//------------------------------------------Function Separator --------------------------------------------------------
EquationofMotion::EquationofMotion(motionModel &modelIn, string NameIn)
{
    //Constructor with specifying name.

    //Assign the calling body to private variable.
    this->EquationofMotion(modelIn);

    //Assign the equation name
    pName = NameIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
EquationofMotion::EquationofMotion(motionModel &modelIn, string NameIn, int IndexIn)
{
    //Constructor with specifying name and data index of the equation.

    //Assign the calling body and enter the name.
    this->EquationofMotion(modelIn, NameIn);

    //Assign the data index.
    pDataIndex = IndexIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
EquationofMotion::~EquationofMotion()
{
    //Default destructor
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::Evaluate()
{
    /*Evaluate is just another expression of the Formula object.
     *They are separated because mathematicians will write children of this object.
     *Many of the functions implemented in this object are purely to create names and other nomenclature
     *to mathematicians.
     *
     *For a quick summary:  Evaluate is the function that actually returns the value of the equation
     *of motion object.
     */

    return this->Formula();
}

//------------------------------------------Function Separator --------------------------------------------------------
void EquationofMotion::setDataIndex(int DataIn)
{
    //Sets the data index.
    pDataIndex = DataIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::getDataIndex()
{
    //Returns the data index.
    return this->eqn();
}

//------------------------------------------Function Separator --------------------------------------------------------
int &EquationofMotion::DataIndex()
{
    //Exposes the data index object.  Passed by reference.
    return this->eqn();
}

//------------------------------------------Function Separator --------------------------------------------------------
void EquationofMotion::setArguments(int argn, vector<double> argv)
{
    //Sets the input arguments.  These are arbitrary arguments that the user may or may not use.
    argcount = argn;
    argvalue = argv;
}

//------------------------------------------Function Separator --------------------------------------------------------
void &EquationofMotion::Name()
{
    //Exposes the object name
    return pName;
}

//------------------------------------------Function Separator --------------------------------------------------------
void &EquationofMotion::Description()
{
    //Exposes the object description
    return pDescription;
}

//==========================================Section Separator =========================================================
//Protected Members

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::kronecker(int var1, int var2, bool anti)
{
    complex<double> out(0,0);

    //Implementation of the kronecker delta function.
    if (var1 == var2)
        out.real() = 1.0;
    else
        out.real() = 0.0;

    //Check if using reverse kronecker delta.
    if (anti)
    {
        if (out.real() == 1.0)
            out.real() = 0.0;
        else
            out.real() = 1.0;
    }

    //write output
    return out;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ddt(int var, int ord, int bodIn=-1)
{
    //set initial value for bodIn
    if (bodIn == -1)
        bodIn = pCurBod;

    //Calculate time differential.
    complex<double> out(0,0);

    //First check if calculating coefficients.
    if (pParentModel.calcCoeff)
    {
        //Only calculating coefficients.  Write out unit value.
        out.real() = 1.0;
    }
    else
    {
        //Not calculating coefficients.  Get actual values.
        complex<double> freq(0,0);
        complex<double> imagI(0,1.0);

        //get wave frequency.
        freq = pParentModel.pFreq;
        //get value to calculate refDerivative for.
        out = pParentModel.listData[bodIn].Solution()(var(), 1);

        //Calculate refDerivative
        for (int i = 0; i <= ord; i++)
        {
            out = out * freq * imagI;
        }
    }

    //Write output
    return out;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::sum(complex<double> force, string index, int from = -1, int to = -1)
{
    //Create variable for output
    complex<double> output(0,0);        //Output variable

    //Select which index to sum over.
    switch (index)
    {
    case "var" "v" "V" "Var" "VAR":
        //Sum for variable count.
        for (pCurVar = from ; pCurVar <= to; pCurVar++)
        {
            output = output + force;
        }
        break;
    case "ord" "o" "O" "Ord" "ORD":
        //Sum for order of refDerivative.
        for (pCurOrd = from ; pCurOrd <= to; pCurOrd++)
        {
            output = output + force;
        }
        break;
    case "bod" "b" "B" "Bod" "BOD":
        //Sum for bodies.
        for (pCurBod = from ; pCurBod <= to; pCurBod++)
        {
            output = output + force;
        }
        break;
    }
    //write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceActive_hydro()
{
    //Returns the active force object for the currently defined indices.
    complex<double> output(0,0);         //Temporary value for variable.
    complex<double> reverse(-1,0);         //Reverses sign of active force variable.

    //The coefficients in the active force matrix for hydrodynamics can only be one
    //set.  These are the reserved functions.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check.  Ensure that the requested data index is not out of bounds.
    if (eqn() <= 5 )
    {
        //Add up for all forces
        for (pCurForce = 0; pCurForce < pParentModel.listData[pCurBod].listForceActive_hydro().size() ; pCurForce++)
        {
            //Get value and add.
            output +=
                    pParentModel.listData[pCurBod].
                    listForceActive_hydro()[force()].
                    getEquation(eqn());
        }
    }

    //Check if need to reverse sign of variable.
    if (pParentModel.pActiveOnly)
        output = output * reverse;

    //write output
    return output;

    //cleanup
    delete output;
    delete reverse;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceActive_user()
{
    //Returns the active force object for the currently defined indices.  User force.
    complex<double> output(0,0);    //Temporary value for variable.
    complex<double> reverse(-1,0);         //Reverses sign of active force variable.

    //The coefficients in the active force matrix must match the equations of motion, in the sequence that they
    //were entered.  Therefore, don't need the eqn object.  This defaults to the private variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check for equations
    if (eqn() <= pParentModel.listData[pCurBod].listForceActive_user()[force()].Equations.size() - 1)
    {
        //Add up for all forces
        for (pCurForce = 0; pCurForce < pParentModel.listData[pCurBod].listForceActive_user().size() ; pCurForce++)
        {
            //get value
            output +=
                    pParentModel.listData[pCurBod].
                    listForceActive_user()[force()].
                    getEquation(pPrivateIndex);
        }
    }

    //Check if need to reverse sign of variable.
    if (pParentModel.pActiveOnly)
        output = output * reverse;

    //write output
    return output;

    //cleanup
    delete output;
    delete reverse;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceReact_hydro(int ordIn, int varIn)
{
    //Returns the reactive force value for the indices specified by the input variables.
    complex<double> output(0,0);    //Temporary value for variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check for refDerivatives
    if (ordIn <= pParentModel.listData[pCurBod].listForceReact_hydro()[force()].refDerivatives.size() - 1)
    {
        //Out of bounds check for variables
        if (varIn <= pParentModel.listData[pCurBod].listForceReact_hydro()[force()].refDerivative(ordIn).indexEquation(eqn()).getCoefficientListSize())
        {
            //Add up for all force objects.
            for (pCurForce ; pCurForce < pParentModel.listData[pCurBod].listForceReact_hydro().size() ; pCurForce++)
            {
                //get value
                output.real() = output.real() +
                        pParentModel.listData[pCurBod].
                        listForceReact_hydro()[force()].
                        refDerivative(ordIn).
                        IndexEquation(eqn()).
                        getCoefficient(varIn);
            }
        }
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceReact_user(int ordIn, int varIn)
{
    //Returns the reactive force value for the indices specified by the input variables.
    complex<double> output(0,0);    //Temporary value for variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check for refDerivatives
    if (ordIn <= pParentModel.listData[pCurBod].listForceReact_user()[force()].refDerivatives.size() - 1)
    {
        //Out of bounds check for variables
        if (varIn <= pParentModel.listData[pCurBod].listForceReact_user()[force()].refDerivative(ordIn).indexEquation(eqn()).getCoefficientListSize())
        {
            //Add up for all force objects.
            for (pCurForce ; pCurForce < pParentModel.listData[pCurBod].listForceReact_user().size() ; pCurForce++)
            {
                //get value
                output.real() =
                        pParentModel.listData[pCurBod].
                        listForceReact_user()[force()].
                        refDerivative(ordIn).
                        IndexEquation(eqn()).
                        getCoefficient(varIn);
            }
        }
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceCross_hydro(int bodIn, int ordIn, int varIn)
{
    //Returns the reactive force value for the indices specified by the input variables.
    complex<double> output(0,0);    //Temporary value for variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Check out of bounds for bodIn
    if (bodIn > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check for refDerivatives
    if (ordIn <= pParentModel.listData[pCurBod].listForceCross_hydro()[force()].refDerivatives.size() - 1)
    {
        //Out of bounds check for variables
        if (varIn <= pParentModel.listData[pCurBod].listForceCross_hydro()[force()].refDerivative(ordIn).indexEquation(eqn()).getCoefficientListSize())
        {
            //Add up for all force objects.
            for (pCurForce ; pCurForce < pParentModel.listData[pCurBod].listForceCross_hydro().size() ; pCurForce++)
            {
                //Check that bodIn matches the body specified by the cross body force.
                if (bodIn == pParentModel.pCompCrossBod_hydro[pCurForce])
                {
                //get value
                output.real() = output.real() +
                        pParentModel.listData[pCurBod].
                        listForceCross_hydro()[force()].
                        refDerivative(ordIn).
                        IndexEquation(eqn()).
                        getCoefficient(varIn);
                }
            }
        }
    }
    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceCross_user(int bodIn, int ordIn, int varIn)
{
    //Returns the reactive force value for the indices specified by the input variables.
    complex<double> output(0,0);    //Temporary value for variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Check out of bounds for bodIn
    if (bodIn > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Out of bounds check for refDerivatives
    if (ordIn <= pParentModel.listData[pCurBod].listForceCross_user()[force()].refDerivatives.size() - 1)
    {
        //Out of bounds check for variables
        if (varIn <= pParentModel.listData[pCurBod].listForceCross_user()[force()].refDerivative(ordIn).indexEquation(eqn()).getCoefficientListSize())
        {
            //Add up for all force objects.
            for (pCurForce ; pCurForce < pParentModel.listData[pCurBod].listForceCross_user().size() ; pCurForce++)
            {
                //Check that bodIn matches the body specified by the cross body force.
                if (bodIn == pParentModel.pCompCrossBod_user[pCurForce])
                {
                //get value
                output.real() = output.real() +
                        pParentModel.listData[pCurBod].
                        listForceCross_user()[force()].
                        refDerivative(ordIn).
                        IndexEquation(eqn()).
                        getCoefficient(varIn);
                }
            }
        }
    }
    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> EquationofMotion::ForceMass(int varIn)
{
    //Returns the mass object.
    complex<double> output(0,0);    //Temporary value for variable.

    //Check out of bounds for body.
    if (pCurBod > pParentModel.listData.size() - 1)
    {
        return output;
        exit;
    }

    //Check out of bounds for equation
    if (eqn() <= 5)
    {
        //No need to check for out of bounds error.  Object creates enough entries by default.
        //No need to add multiple entries.  There can only be one mass object for each body.
        output.real() = pParentModel.listData[pCurBod].MassMatrix(eqn(), varIn);
    }
    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::var()
{
    //Returns the index integer for iteration on variable.
    int output;
    output = pCurVar;

    return output;
    delete output;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::eqn()
{
    /*Returns the index integer for iteration on equation number.
     *Includes error handling for out-of-bounds checking.
     *
     *The equation function also includes additional provisions to check the Data Index of each equation.
     *The Data index is the solution to a problem:  We want the matrices and data storage to be as few entries
     *as possible.  This is to minimize memory usage.  The presence of hydrodynamic forces provides that
     *there will always be _data_ for at least six forces, which are reserved as the first six entries of any
     *equation vector.
     *
     *However, the equations of motion may not use those indices.  And the use forces may use other higher indices.
     *To allievate this problem, each Equation object, and each Equation of Motion object has a property of DataIndex.
     *The eqn() function searches through the DataIndices and matches these items, instead of matching the index
     *of the equation's position in the vector.  If the DataIndex property is not defined, then the position
     *in the vector is used as the index.
     */

    //Get index of equation of motion.
    if (pDataIndex < 0)
    {
        //Data index not defined.
        //Use private index.
        return pPrivateIndex;
    }
    else
    {
        return pDataIndex;
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::ord()
{
    //Returns the index integer for iteration on order of derviative.
    //Includes error handling for out-of-bounds checking.
    int output;
    output = pCurOrd;

    return output;
    delete output;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::body()
{
    //Returns integer for the current body.  Also includes checks for out-of-bounds error limits.
    int output;
    output = pCurBod;

    return output;
    delete output;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::maxbody()
{
    //Returns the maximum index of body variable.
    return pParentModel.listData.size() - 1;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::maxord()
{
    //Returns the maximum index of order of refDerivative variable.
    //This will be the maximum order for any of the forces.

    //Only need to check the user forces because the hydro forces can never contain data beyond second order.
    int maxme = 2;          //Initialize tracking variable with second order.
    int temp;               //Retrieves value of order of refDerivative.

    //Check through Reactive forces.
    for (int i = 0; i < pParentModel[pCurBod].listForceReact_user().size(); i++)
    {
        //Get maximum order
        temp = pParentModel[pCurBod].listForceReact_user[i].getMaxOrd();

        //Compare values.
        if (temp > maxme)
            maxme = temp;
    }

    //Check through Cross-body forces
    for (int i = 0; i < pParentModel[pCurBod].listForceCross_user().size(); i++)
    {
        //Get maximum order
        temp = pParentModel[pCurBod].listForceCross_user[i].getMaxOrd();

        //Compare values.
        if (temp > maxme)
            maxme = temp;
    }

    //Write output
    return maxme;

    //Cleanup
    delete temp;
    delete maxme;
}

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::maxvar()
{
    //Returns the maximum index of variables.
    return pParentModel.listEquations.size() - 1;
}

//==========================================Section Separator =========================================================
//Private Members

//------------------------------------------Function Separator --------------------------------------------------------
int EquationofMotion::force()
{
    //Returns integer for the current force.  Also includes checks for out-of-bounds error limits.
    int output;
    output = pCurForce;

    return output;
    delete output;
}
