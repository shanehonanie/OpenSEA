#include "motionmodel.h"

//------------------------------------------Function Separator --------------------------------------------------------
motionModel::motionModel()
{
    //Default constructor.
}

//------------------------------------------Function Separator --------------------------------------------------------
motionModel::motionModel(const vector<Body> &listBodIn)
{
    //Constructor that sets the body reference.
    setListBodies(listBodIn);
}

//------------------------------------------Function Separator --------------------------------------------------------
motionModel::~motionModel()
{
    //Default destructor.
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setListBodies(const vector<Body> &listBodIn)
{
    //Set the list of bodies to use in the motion model.
    listBody = listBodIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setBody(int bod)
{
    //Set the integer for the body to use as the reference.
    curBody = bod;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::calcCoefficient(bool calc)
{
    //Determine if the function should calculate coefficients or not.
    calcCoeff = calc;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::Reset()
{
    //Resets the motion model.
    /*Simply delete all variables.  This has an important caveat.  All variables are deleted to save time and memory.
     *This is better than the alternative of initializing all the variables as zeros.  However, this means that
     *any function which accesses the list data must be prepared to handle the exception of accessing non-existent
     *memory.  The default value to return when no memory is assigned is zero.
     */

    //Delete all variables.
    delete listData;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setFreq(double freq)
{
    //Sets the wave frequency.
    pFreq = freq;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceAct_usr(int force, int eqn)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceActive_user.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceActive_user.resize(force + 1);
    }

    //Check if the designed body has enough equations in the force for the specified number.
    if (listData[curBody].listForceActive_user[force].Equations.size() < eqn + 1)
    {
        //Add enough equations.
        listData[curBody].listForceActive_user[force].Equations.resize(eqn + 1);
    }

    //Set the active force, user.
    complex<double> input;

    //Get the input value.
    input = listBody[curBody].listForceActive_user[force].Equations[eqn];

    //Write the input value.
    listData[curBody].listForceActive_user[force].Equations[eqn] = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceAct_hydro(int force, int eqn)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceActive_hydro.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceActive_hydro.resize(force + 1);
    }

    //Check if the designed body has enough equations in the force for the specified number.
    if (listData[curBody].listForceActive_hydro[force].Equations.size() < eqn + 1)
    {
        //Add enough equations.
        listData[curBody].listForceActive_hydro[force].Equations.resize(eqn + 1);
    }

    //Set the active force, hydro.
    complex<double> input;

    //Get the input value.
    input = listBody[curBody].listForceActive_hydro[force].Equations[eqn];

    //Write the input value.
    listData[curBody].listForceActive_hydro[force].Equations[eqn] = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceReact_usr(int force, int ord, int eqn, int var)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceReact_user.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceReact_user.resize(force + 1);
    }

    //Check if the designated force has enough derivatives for the current number specified.
    if (listData[curBody].listForceReact_user[force].Derivatives.size() < ord + 1)
    {
        //Add enough derivatives.
        listData[curBody].listForceReact_user[force].Derivatives().resize(ord + 1);
    }

    //Check if the designated derivative has enough equations for the current number specified.
    if (listData[curBody].listForceReact_user[force].getDerivative(ord).Equations().size() < eqn + 1)
    {
        listData[curBody].listForceReact_user[force].getDerivative(ord).Equations().resize(eqn + 1);
    }

    //Check if the designated equation has enough coefficients for the current number specified.
    if (listData[curBody].listForceReact_user[force].getDerivative(ord).
           getEquation(eqn).Coefficients.size() < var + 1 )
    {
        listData[curBody].listForceReact_user[force].getDerivative(ord).
                getEquation(eqn).Coefficients.resize(var + 1);
    }

    //temporary variable for data transfer
    double input;

    //Getthe input value.
    input = listBody[curBody].listForceReact_user[force].getDerivative(ord).getEquation(eqn).getCoefficient(var);

    //Write the input value.
    listData[curBody].listForceReact_user[force].getDerivative(ord).getEquation(eqn).setCoefficient(var, input);

    delete input;
    int input_int;

    //Copy over the data Index.
    input_int = listBody[curBody].listForceReact_user[force].getDerivative(ord).getEquation(eqn).DataIndex;

    //Write the input value.
    listData[curBody].listForceReact_user[force].getDerivative(ord).getEquation(eqn).DataIndex = input_int;

    delete input_int;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceReact_hydro(int force, int ord, int eqn, int var)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceReact_hydro.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceReact_hydro.resize(force + 1);
    }

    //Check if the designated force has enough derivatives for the current number specified.
    if (listData[curBody].listForceReact_hydro[force].Derivatives.size() < ord + 1)
    {
        //Add enough derivatives.
        listData[curBody].listForceReact_hydro[force].Derivatives().resize(ord + 1);
    }

    //Check if the designated derivative has enough equations for the current number specified.
    if (listData[curBody].listForceReact_hydro[force].getDerivative(ord).Equations().size() < eqn + 1)
    {
        listData[curBody].listForceReact_hydro[force].getDerivative(ord).Equations().resize(eqn + 1);
    }

    //Check if the designated equation has enough coefficients for the current number specified.
    if (listData[curBody].listForceReact_hydro[force].getDerivative(ord).
           getEquation(eqn).Coefficients.size() < var + 1 )
    {
        listData[curBody].listForceReact_hydro[force].getDerivative(ord).
                getEquation(eqn).Coefficients.resize(var + 1);
    }

    //temporary variable for data transfer
    double input;

    //Getthe input value.
    input = listBody[curBody].listForceReact_hydro[force].getDerivative(ord).getEquation(eqn).getCoefficient(var);

    //Write the input value.
    listData[curBody].listForceReact_hydro[force].getDerivative(ord).getEquation(eqn).setCoefficient(var, input);

    delete input;
    int input_int;

    //Copy over the data Index.
    input_int = listBody[curBody].listForceReact_hydro[force].getDerivative(ord).getEquation(eqn).DataIndex;

    //Write the input value.
    listData[curBody].listForceReact_hydro[force].getDerivative(ord).getEquation(eqn).DataIndex = input_int;

    delete input_int;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceCross_usr(int force, int ord, int eqn, int var)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceCross_user.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceCross_user.resize(force + 1);
    }

    //Check if the designated body has enough linking cross body entries for the current specified number.
    if (listData[curBody].listCrossBody_user().size() < force + 1)
    {
        //Add enough linking cross body entries.
        listData[curBody].listCrossBody_user().resize(force + 1);
    }

    //Check if the designated force has enough derivatives for the current number specified.
    if (listData[curBody].listForceCross_user[force].Derivatives.size() < ord + 1)
    {
        //Add enough derivatives.
        listData[curBody].listForceCross_user[force].Derivatives().resize(ord + 1);
    }

    //Check if the designated derivative has enough equations for the current number specified.
    if (listData[curBody].listForceCross_user[force].getDerivative(ord).Equations().size() < eqn + 1)
    {
        listData[curBody].listForceCross_user[force].getDerivative(ord).Equations().resize(eqn + 1);
    }

    //Check if the designated equation has enough coefficients for the current number specified.
    if (listData[curBody].listForceCross_user[force].getDerivative(ord).
           getEquation(eqn).Coefficients.size() < var + 1 )
    {
        listData[curBody].listForceCross_user[force].getDerivative(ord).
                getEquation(eqn).Coefficients.resize(var + 1);
    }

    //temporary variable for data transfer
    double input;

    //Getthe input value.
    input = listBody[curBody].listForceCross_user[force].getDerivative(ord).getEquation(eqn).getCoefficient(var);

    //Write the input value.
    listData[curBody].listForceCross_user[force].getDerivative(ord).getEquation(eqn).setCoefficient(var, input);

    delete input;

    //Copy over the data Index.
    listData[curBody].listForceCross_user[force].getDerivative(ord).getEquation(eqn).DataIndex =
            listBody[curBody].listForceCross_user[force].getDerivative(ord).getEquation(eqn).DataIndex;

    //Copy over the linked body reference.
    listData[curBody].listCrossBody_user[force] = listBody[curBody].listCrossBody_user[force];
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceCross_hydro(int force, int ord, int eqn, int var)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceCross_hydro.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceCross_hydro.resize(force + 1);
    }

    //Check if the designated body has enough linking cross body entries for the current specified number.
    if (listData[curBody].listCrossBody_hydro().size() < force + 1)
    {
        //Add enough linking cross body entries.
        listData[curBody].listCrossBody_hydro().resize(force + 1);
    }

    //Check if the designated force has enough derivatives for the current number specified.
    if (listData[curBody].listForceCross_hydro[force].Derivatives.size() < ord + 1)
    {
        //Add enough derivatives.
        listData[curBody].listForceCross_hydro[force].Derivatives().resize(ord + 1);
    }

    //Check if the designated derivative has enough equations for the current number specified.
    if (listData[curBody].listForceCross_hydro[force].getDerivative(ord).Equations().size() < eqn + 1)
    {
        listData[curBody].listForceCross_hydro[force].getDerivative(ord).Equations().resize(eqn + 1);
    }

    //Check if the designated equation has enough coefficients for the current number specified.
    if (listData[curBody].listForceCross_hydro[force].getDerivative(ord).
           getEquation(eqn).Coefficients.size() < var + 1 )
    {
        listData[curBody].listForceCross_hydro[force].getDerivative(ord).
                getEquation(eqn).Coefficients.resize(var + 1);
    }

    //temporary variable for data transfer
    double input;

    //Getthe input value.
    input = listBody[curBody].listForceCross_hydro[force].getDerivative(ord).getEquation(eqn).getCoefficient(var);

    //Write the input value.
    listData[curBody].listForceCross_hydro[force].getDerivative(ord).getEquation(eqn).setCoefficient(var, input);

    delete input;

    //Copy over the data Index.
    listData[curBody].listForceCross_hydro[force].getDerivative(ord).getEquation(eqn).DataIndex =
            listBody[curBody].listForceCross_hydro[force].getDerivative(ord).getEquation(eqn).DataIndex;

    //Copy over the linked body reference.
    listData[curBody].listCrossBody_hydro[force] = listBody[curBody].listCrossBody_hydro[force];
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceMass(int eqn, int var)
{
    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Don't need to check that the mass matrix created successfully.
    //Construction of body object automatically initializes with a mass matrix of the correct size.

    //Copy over the mass matrix entry.
    listData[curBody].MassMatrix[eqn, var] = listBody[curBody].MassMatrix[eqn, var];
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> motionModel::Evaluate(int eqn)
{
    //Trigger evaluation of the equation objects.
    return listEquations[eqn].Evaluate;
}

//------------------------------------------Function Separator --------------------------------------------------------
int motionModel::numEquations()
{
    //Reports the number of equations used.
    return listEquations.size();
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<int> motionModel::DataIndex()
{
    //Create a vector containing the data indices used by the equations.
    vector<int> dataOut(this->numEquations());

    for (int i = 0; i < this->numEquations(); i++)
    {
        dataOut[i] = listEquations[i].getIndex();
    }

    //Write output
    return dataOut;

    delete dataOut;
}

//------------------------------------------Function Separator --------------------------------------------------------
int motionModel::MaxDataIndex()
{
    vector<int> listIndex;

    //Get the list.
    listIndex = this->DataIndex();

    //Search through the list to find the largest size.
    int maxSize = -1;
    for (unsigned int i = 0; i < listIndex.size() ; i++)
    {
        if (maxSize < listIndex[i])
        {
            maxSize = listIndex[i];
        }
    }

    //Write output
    return maxSize;

    delete listIndex;
}


//==========================================Section Separator =========================================================
//Private Functions
//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> motionModel::CopyZero(Mat<double> & copyMat)
{
    //Copies the matrix and outputs a matrix of the same size with zeros.
    Mat<double> matOut;

    matOut.zeros(copyMat.n_rows, copyMat.n_cols);

    return matOut;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::fillBodies()
{
    //Fills out the body array
    if (listBody.size() != listData.size())
    {
        //Not equal sized lists.  Create the list.
        listData.resize(listBody.size());
        for (unsigned int i = 0; i < listBody->size(); i++)
        {
            //Assign some critical information that should always be carried through.
            listData[i].BodyName = listBody[i].BodyName;
            listData[i].HydroBodyName = listBody[i].HydroBodyName;
            listData[i].Heading = listBody[i].Heading;
            listData[i].Posn = listBody[i].Posn;
        }
    }
}




