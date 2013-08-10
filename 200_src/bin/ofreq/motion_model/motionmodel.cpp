#include "motionmodel.h"

//------------------------------------------Function Separator --------------------------------------------------------
motionModel::motionModel()
{
    //Default constructor.

    //Initialize Active force variable.
    pActiveOnly = true;

    //Create initial value for wave frequency
    pFreq = 0.0;
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

    //Erase the cross body objects.  No longer valid.
    delete pCompCrossBod_hydro;
    delete pCompCrossBod_user;
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

    //Initialize Active force variable.
    pActiveOnly = true;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setFreq(double freq)
{
    //Sets the wave frequency.
    pFreq = freq;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceActive_user(int force, int eqn)
{
    //Trigger to use active forces.
    pActiveOnly = pActiveOnly * true;       //Will still evaluate to false if a reactive force was already triggered.

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
void motionModel::useForceActive_hydro(int force, int eqn)
{
    //Trigger to use active forces.
    pActiveOnly = pActiveOnly * true;       //Will still evaluate to false if a reactive force was already triggered.

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
void motionModel::useForceReact_user(int force, int ord, int eqn, int var)
{
    //Turn off active force evaluation.
    pActiveOnly = false;

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
    //Turn off active force evaluation.
    pActiveOnly = false;

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
void motionModel::useForceCross_user(int force, int ord, int eqn, int var)
{
    //Turn off active force evaluation.
    pActiveOnly = false;

    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Check if the designated body has enough forces for the current specified number.
    if (listData[curBody].listForceCross_user.size() < force + 1)
    {
        //Add enough forces.
        listData[curBody].listForceCross_user.resize(force + 1);
    }

    //Check if the list of linked cross-bodies has enough entries for the current number specified.
    if (pCompCrossBod_user.size() < force + 1)
    {
        //Add enough entries.
        pCompCrossBod_user.resize(force + 1);
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
    for (int i = 0 ; i < listBody.size() ; i++)
    {
        //Check if the cross body force matches.
        if (&listBody[i] == listBody[curBody].listCrossBody_user()[force])
        {
            //True.  Copy integer and stop.
            pCompCrossBod_user[force] = i;
            break;
        }
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceCross_hydro(int force, int ord, int eqn, int var)
{
    //Turn off active force evaluation.
    pActiveOnly = false;

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

    //Check if the list of linked cross-bodies has enough entries for the current number specified.
    if (pCompCrossBod_hydro.size() < force + 1)
    {
        //Add enough entries.
        pCompCrossBod_hydro.resize(force + 1);
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
    if (listData[curBody].listForceCross_hydro[force].getDerivative(ord).getEquation(eqn).Coefficients.size() < var + 1 )
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
    for (int i = 0 ; i < listBody.size() ; i++)
    {
        //Check if the cross body force matches.
        if (&listBody[i] == listBody[curBody].listCrossBody_hydro()[force])
        {
            //True.  Copy integer and stop.
            pCompCrossBod_hydro[force] = i;
            break;
        }
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::useForceMass(int eqn, int var)
{
    //Turn off active force evaluation.
    pActiveOnly = false;

    //Check if there are enough bodies for the current called functions.
    //All happens in the fillBodies function.
    fillBodies();

    //Don't need to check that the mass matrix created successfully.
    //Construction of body object automatically initializes with a mass matrix of the correct size.

    //Copy over the mass matrix entry.
    listData[curBody].MassMatrix(eqn, var) = listBody[curBody].MassMatrix(eqn, var);
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceActive_user(int force)
{
    //Create force matrix.
    cx_mat outputmat;       //output matrix
    int rows;               //Number of rows

    //resize output matrix
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(rows,1);

    //Run evaluation of equations for each equation in the force object.
    //Reset the model
    Reset();
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Activate the appropriate user force.
        useForceActive_user(force, i);

        //Evaluate the equation of motion and store in matrix.
        outputmat(i,0) = Evaluate(i);
    }

    //Write output
    return outputmat;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceActive_hydro(int force)
{
    //Create force matrix.
    cx_mat outputmat;       //output matrix
    int rows;               //Number of rows

    //resize output matrix
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(rows,1);

    //Run evaluation of equations for each equation in the force object.
    //Reset the model
    Reset();
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Activate the appropriate hydro force.
        useForceActive_hydro(force, i);

        //Evaluate the equation of motion and store in matrix.
        outputmat(i,0) = Evaluate(i);
    }

    //Write output
    return outputmat;

    //cleanup
    delete outputmat;
    delete rows;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceReact_user(int force, int ord)
{
    //Create force matrix
    cx_mat outputmat;       //outputmatrix
    int n_row;              //number of rows for new matrix.

    //resize output matrix.
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(n_row, n_row);         //Only needed one dimension because the matrix must be square.

    //Run evaluation for each variable in the force object.
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Reset the model
        Reset();

        //Run evaluation for each equation in the force object.
        for (int j = 0; j < listEquations.size(); j++)
        {
            //Promote the reactive force to use, on the correct order of derivative.
            useForceReact_user(force, ord, j, i);

            //Evaluate the equation of motion and store in matrix.
            outputmat(j,i) = Evaluate(j);
        }
    }

    //Write output
    return outputmat;

    //Cleanup
    delete outputmat;
    delete n_row;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceReact_hydro(int force, int ord)
{
    //Create force matrix
    cx_mat outputmat;       //outputmatrix
    int n_row;              //number of rows for new matrix.

    //resize output matrix.
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(n_row, n_row);         //Only needed one dimension because the matrix must be square.

    //Run evaluation for each variable in the force object.
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Reset the model
        Reset();

        //Run evaluation for each equation in the force object.
        for (int j = 0; j < listEquations.size(); j++)
        {
            //Promote the reactive force to use, on the correct order of derivative.
            useForceReact_hydro(force, ord, j, i);

            //Evaluate the equation of motion and store in matrix.
            outputmat(j,i) = Evaluate(j);
        }
    }

    //Write output
    return outputmat;

    //Cleanup
    delete outputmat;
    delete n_row;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceCross_user(int force, int ord)
{
    //Create force matrix
    cx_mat outputmat;       //outputmatrix
    int n_row;              //number of rows for new matrix.

    //resize output matrix.
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(n_row, n_row);         //Only needed one dimension because the matrix must be square.

    //Run evaluation for each variable in the force object.
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Reset the model
        Reset();

        //Run evaluation for each equation in the force object.
        for (int j = 0; j < listEquations.size(); j++)
        {
            //Promote the reactive force to use, on the correct order of derivative.
            useForceCross_user(force, ord, j, i);

            //Evaluate the equation of motion and store in matrix.
            outputmat(j,i) = Evaluate(j);
        }
    }

    //Write output
    return outputmat;

    //Cleanup
    delete outputmat;
    delete n_row;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceCross_hydro(int force, int ord)
{
    //Create force matrix
    cx_mat outputmat;       //outputmatrix
    int n_row;              //number of rows for new matrix.

    //resize output matrix.
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(n_row, n_row);         //Only needed one dimension because the matrix must be square.

    //Run evaluation for each variable in the force object.
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Reset the model
        Reset();

        //Run evaluation for each equation in the force object.
        for (int j = 0; j < listEquations.size(); j++)
        {
            //Promote the reactive force to use, on the correct order of derivative.
            useForceCross_hydro(force, ord, j, i);

            //Evaluate the equation of motion and store in matrix.
            outputmat(j,i) = Evaluate(j);
        }
    }

    //Write output
    return outputmat;

    //Cleanup
    delete outputmat;
    delete n_row;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat motionModel::getMatForceMass()
{
    //Create force matrix
    cx_mat outputmat;       //outputmatrix
    int n_row;              //number of rows for new matrix.

    //resize output matrix.
    n_row = listBody[curBody].getEquationCount();
    outputmat.resize(n_row, n_row);         //Only needed one dimension because the matrix must be square.

    //Run evaluation for each variable in the force object.
    for (int i = 0; i < listEquations.size(); i++)
    {
        //Reset the model
        Reset();

        //Run evaluation for each equation in the force object.
        for (int j = 0; j < listEquations.size(); j++)
        {
            //Promote the reactive force to use, on the correct order of derivative.
            useForceMass(j, i);

            //Evaluate the equation of motion and store in matrix.
            outputmat(j,i) = Evaluate(j);
        }
    }

    //Write output
    return outputmat;

    //Cleanup
    delete outputmat;
    delete n_row;
}

//------------------------------------------Function Separator --------------------------------------------------------
complex<double> motionModel::Evaluate(int eqn)
{
    //Trigger evaluation of the equation objects.
    return listEquations[eqn].Evaluate();
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

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setName(string nameIn)
{
    pName = nameIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
string motionModel::getName()
{
    return pName;
}

//------------------------------------------Function Separator --------------------------------------------------------
void motionModel::setDescription(string DescIn)
{
    pDesc = DescIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
string motionModel::getDescription()
{
    return pDesc;
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
