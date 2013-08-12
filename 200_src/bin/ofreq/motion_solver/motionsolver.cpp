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

#include "motionsolver.h"

//------------------------------------------Function Separator --------------------------------------------------------
MotionSolver::MotionSolver()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
MotionSolver::MotionSolver(vector<matBody> listBodIn)
{
    for (int i; i < listBodIn.size(); i++)
    {
        this->AddBody(listBodIn[i]);
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
MotionSolver::~MotionSolver()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
void MotionSolver::AddBody(matBody bodIn)
{
    this->plistBody.push_back(bodIn);
}

//------------------------------------------Function Separator --------------------------------------------------------
matReactForce MotionSolver::sumReactSet(vector<matReactForce> listForces)
{
    //Create output object.
    matReactForce output;

    //Iterate through the list and sum the forces in each item.
    for (int i; i < listForces.size(); i++)
    {
        output = output + listForces[i];
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<matCrossForce> MotionSolver::sumCrossSet(vector<matCrossForce> listForces)
{
    //Create output object
    vector<matCrossForce> output(this->plistBody.size());

    //Run through the list and set the link id to the index of the cell.
    for (int i = 0; i < output.size(); i++)
    {
        output[i].linkedid(i);
    }

    //Go through the list.  For each entry in the list, also run through
    //the full forces list and add all forces to each entry.
    //The class for matCrossForce automatically handles the filtering
    //to ensure only the correct items are added together.
    //(those with matching linkedid's).
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 0; j < listForces.size(); j++)
        {
            output[i] = output[i] + listForces[j];
        }
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat MotionSolver::sumActiveSet(vector<cx_mat> listForces)
{
    cx_mat singleForceMarix(maxMatrixSize,1); //6x1 column matrix

    for(unsigned int i = 0; i < listForces.size(); i++)
    {
        singleForceMarix += listForces[i];
    }
    return singleForceMarix;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat MotionSolver::sumDerivative(matReactForce forceIn)
{
    //complex version of current wave frequency.
    complexDouble waveFreq(this->curWaveFrequency, 0.0);
    //Complex version of imaginary variable i.
    complexDouble imagI(0.0, 1.0);
    //complex scalar multiple.  Will calculate later.
    complexDouble scalarMult;

    cx_mat output;

    //resize output matrix
    output.zeros(forceIn.matSize());

    //Iterate through each derivative order and add them together.
    for (int i = 0 ; i <= forceIn.maxOrder() ; i++)
    {
        //Calculate scalar product.
        scalarMult = pow(waveFreq, i) * pow(imagI, i);

        //Multiply through to derivative terms and add to total.
        for (int row = 0 ; row < forceIn.Derivative(i).n_rows ; row++)
        {
            for (int col = 0 ; col < forceIn.Derivative(i).n_cols ; col++)
            {
                output.at(row,col) += scalarMult * forceIn.Derivative(i).at(row,col);
            }
        }
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<cx_mat> MotionSolver::sumDerivative(vector<matCrossForce> forceIn)
{
    //complex version of current wave frequency.
    complexDouble waveFreq(this->curWaveFrequency, 0.0);
    //Complex version of imaginary variable i.
    complexDouble imagI(0.0, 1.0);
    //complex scalar multiple.  Will calculate later.
    complexDouble scalarMult;

    vector<cx_mat> output;

    for (int x = 0 ; x < forceIn.size() ; x++)
    {
        //resize output matrix
        output[x].zeros(forceIn[x].matSize());

        //Iterate through each derivative order and add them together.
        for (int i = 0 ; i <= forceIn[x].maxOrder() ; i++)
        {
            //Calculate scalar product.
            scalarMult = pow(waveFreq, i) * pow(imagI, i);

            //Multiply through to derivative terms and add to total.
            for (int row = 0 ; row < forceIn[x].Derivative(i).n_rows ; row++)
            {
                for (int col = 0 ; col < forceIn[x].Derivative(i).n_cols ; col++)
                {
                    output[x].at(row,col) += scalarMult * forceIn.Derivative(i).at(row,col);
                }
            }
        }
    }

    //Write output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
void MotionSolver::setWaveFreq(double freqIn)
{
    //Input wave frequency.
    curWaveFrequency = freqIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
void MotionSolver::CalculateOutputs()
{
    //create a temporary vector to hold outputs of summations - user forces
    vector<matReactForce> tempReactList_usr(plistBody.size());
    vector<cx_mat> ActiveList_usr(plistBody.size());
    vector < vector<matCrossForce> > tempCrossList_usr(plistBody.size, vector<matCrossForce>(plistBody.size()));

    //create a temporary vector to hold outputs of summations - hydro forces
    vector<matReactForce> tempReactList_hydro(plistBody.size());
    vector<cx_mat> ActiveList_hydro(plistBody.size());
    vector < vector<matCrossForce> > tempCrossList_hydro(plistBody.size, vector<matCrossForce>(plistBody.size()));

    //Sum forces for each body in the list.
    for (int i = 0; i< plistBody.size(); i++)
    {
        //Add user forces.
        tempReactList_usr[i] = sumReactSet(plistBody[i].listReactForce_usr);
        ActiveList_usr[i] = sumActiveSet(plistBody[i].listActiveForce_usr);
        tempCrossList_usr[i] = sumCrossSet(plistBody[i].listCrossForce_usr);

        //Add hydro forces.
        tempReactList_hydro[i] = sumReactSet(plistBody[i].listReactForce_hydro);
        ActiveList_hydro[i] = sumActiveSet(plistBody[i].listActiveForce_hydro);
        tempCrossList_hydro[i] = sumCrossSet(plistBody[i].listCrossForce_hydro);
    }
    //Each set now reduced to a single force object, for each body.

    //Create temporary matrices to hold outputs of derivative summation - user forces
    vector<cx_mat> ReactList_usr;
    // No need to sum for active forces.  Already independent of derivative.
    vector< vector<cx_mat> > CrossList_usr;

    //Create temporary matrices to hold outputs ot derivative summation - hydro forces
    vector<cx_mat> ReactList_hydro;
    // No need to sum for active forces.  Already independent of derivative.
    vector< vector<cx_mat> > CrossList_hydro;

    //Sum derivatives within each force.
    for (int i = 0; i < plistBody.size(); i++)
    {
        //Sum for user forces
        ReactList_usr.push_back(sumDerivative(tempReactList_usr[i]));
        CrossList_usr.push_back(sumDerivative(tempCrossList_usr[i]));

        //Sum for hydro forces
        ReactList_hydro.push_back(sumDerivative(tempReactList_hydro[i]));
        CrossList_hydro.push_back(sumDerivative(tempCrossList_hydro[i]));
    }

    //Delete uneeded variables
    delete tempReactList_usr;
    delete tempCrossList_usr;
    delete tempReactList_hydro;
    delete tempCrossList_hydro;

    //Create temporary variables for total of all forces.
    vector<cx_mat> ReactList;
    vector<cx_mat> ActiveList;
    vector< vector<cx_mat> > CrossList;

    //Add different force types for each body object.
    for (int i = 0; i < plistBody.size(); i++)
    {
        ReactList.push_back(ReactList_usr[i] + ReactList_hydro[i]);
        ActiveList.push_back(ActiveList_usr[i] + ActiveList_hydro[i]);
        CrossList.push_back(CrossList_usr[i] + CrossList_hydro[i]);
    }

    //Delete uneeded variables
    delete ReactList_usr;
    delete ActiveList_usr;
    delete CrossList_usr;
    delete ReactList_hydro;
    delete ActiveList_hydro;
    delete CrossList_hydro;

    //"Assemble Global Matrix"
    if(theBodyMassMatrices.size() == 1) //Single Body Matrix
    {
        //Dont include cross body forces if only 1 matrix and just use first index of vector
        globReactiveMat = ReactList[0]; //A Matrix
        globActiveMat = ActiveList[0];     //F Matrix
    }
    else //Multiple Bodies, must resize the matrices
    {
        int newMatrixSize = 0;
        vector<int> matStart;
        vector<int> matEnd;

        for(unsigned int j = 0; j < plistBody.size(); j++)
        {
            //get the size of new matrix by summing all reactiveForceMatrices
            newMatrixSize += ReactList[j].n_rows;

            //Add the sizes to get the starting position of each matrix
            if (j == 0) {
                matStart.pushback(0);
            }
            else
            {
                matStart.pushback(matStart.at(j-1) + ReactiveForceMatrix[j].n_rows + 1);
            }

            //Add the sizes to get the ending positions of each matrix.
            matEnd.pushback(matStart.at(j) + ReactiveForceMatrix[j].n_rows);
        }

        //A Matrix
        //resize matrix to include all bodies reactiveforces & cross Body Forces, matrix must be square (ex. 6x6)
        //At the same time, fill matrix with zero values.
        globReactiveMat.zeros(newMatrixSize, newMatrixSize);
        //F Matrix
        globActiveMat.zeros(newMatrixSize, 1); //column Matrix

        for (j = 0; j < theBodyMassMatrices.size(); j++)
        {
            //Iterate through and insert the reactive force matrices for each body
            globReactiveMat.submat(matStart[j], matStart[j], matEnd[j], matEnd[j]) = ReactiveForceMatrix[j];

            //Iterate through and insert the active force matrices for each body
            globActiveMat.submat(matStart[j], 0, matEnd[j], 0) = activeForce[j];
        }

        //Add in the cross body forces for each body.
        //Iterate through each body.
        for (int i = 0; i < theBodyMassMatrices.size(); i++)
        {
            //Iterate through the cross-body forces listed for each body
            for(unsigned int j = 0; j < theBodyMassMatrices.size(); j++)
            {
                globReactiveMat.submat(matStart[i], matStart[j], matEnd[i], matEnd[j]) = CrossList[i][j];
            }
        }
    }

    //Solve for Unknown Matrix (the X Matrix) --    A*X=B where X is the unknown
    globSolnMat = solve(globReactiveMat, globActiveMat, true); //true arg for more precise calculations

    //Split into vector of solutions, each represents per body
    for(unsigned int i = 0; i < plistBody.size(); i++)
    {
        plistSolution.push_back(globSolnMat.submat(matStart[i], 0, matEnd[i], 0));
    }
}
