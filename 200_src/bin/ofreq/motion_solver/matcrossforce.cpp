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

#include "matcrossforce.h"

//------------------------------------------Function Separator --------------------------------------------------------
matCrossForce::matCrossForce()
{
    //Add 3 matrices to derivative matrix
    for(unsigned int i = 0; i < 3; i++) //<---Fix, change to const
    {
        cx_mat temp(6,6);
        derivativeMatrix.push_back(temp);
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
matCrossForce::matCrossForce(vector<Derivative> forceIn)
{
    for (int i; i <= forceIn.size(); i++)
    {
        this->pderiv.push_back(forceIn[i]);
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
matCrossForce::~matCrossForce()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
matCrossForce matCrossForce::operator+(const matCrossForce& forceOther)
{
    //define the output vector
    matCrossForce output;
    //Check that the lnkedbody parameter is the same for both objects.
    if (this->plinkid == forceOther.plinkid)
    {
         //find the max order of the derivatives.
        int maxOrdTwo;
        if (this->maxOrder() > forceOther.maxOrder())
            maxOrdTwo = this->maxOrder();
        else
            maxOrdTwo = forceOther.maxOrder();

        //Expand the size of the vector
        output.pderiv.resize(maxOrdTwo);

        //Get size of matrices.
        maxSizeTwo;
        if (this->matDims() > forceOther.matDims())
            maxSizeTwo = this-> matDims();
        else
            maxSizeTwo = forceOther.matDims();

        //Check that the maximum size is correct with the matrix size.
        if (this->pderiv[0].n_rows > maxSizeTwo)
            maxSizeTwo = this->pderiv[0].n_rows;
        if (forceOther.pderiv[0].n_rows > maxSizeTwo)
            maxSizeTwo = forceOther.pderiv[0].n_rows;

        //Resize Matrices, initialize with zeros.
        for (int i = 0; i <= maxOrdTwo; i++)
        {
            output.pderiv[i].zeros(maxSizeTwo);

            //Iterate through the matrix and add values.
            for (int j = 0; j < maxSizeTwo; j++)
            {
                for (int k = 0; k < maxSizeTwo; k++)
                {
                    output.pderiv[i](k,j) = this->pderiv[i](k,j) + forceOther.pderiv[i](k,j);
                }
            }
        }
    }
    else
    {
        //linked body parameters did not match.  Return only this object.
        output = this;
    }

    //return output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
matCrossForce matCrossForce::operator-(const matCrossForce& forceOther)
{
    //define the output vector
    matCrossForce output;
    //Check that the lnkedbody parameter is the same for both objects.
    if (this->plinkid == forceOther.plinkid)
    {
         //find the max order of the derivatives.
        int maxOrdTwo;
        if (this->maxOrder() > forceOther.maxOrder())
            maxOrdTwo = this->maxOrder();
        else
            maxOrdTwo = forceOther.maxOrder();

        //Expand the size of the vector
        output.pderiv.resize(maxOrdTwo);

        //Get size of matrices.
        maxSizeTwo;
        if (this->matDims() > forceOther.matDims())
            maxSizeTwo = this-> matDims();
        else
            maxSizeTwo = forceOther.matDims();

        //Check that the maximum size is correct with the matrix size.
        if (this->pderiv[0].n_rows > maxSizeTwo)
            maxSizeTwo = this->pderiv[0].n_rows;
        if (forceOther.pderiv[0].n_rows > maxSizeTwo)
            maxSizeTwo = forceOther.pderiv[0].n_rows;

        //Resize Matrices, initialize with zeros.
        for (int i = 0; i <= maxOrdTwo; i++)
        {
            output.pderiv[i].zeros(maxSizeTwo);

            //Iterate through the matrix and add values.
            for (int j = 0; j < maxSizeTwo; j++)
            {
                for (int k = 0; k < maxSizeTwo; k++)
                {
                    output.pderiv[i](k,j) = this->pderiv[i](k,j) - forceOther.pderiv[i](k,j);
                }
            }
        }
    }
    else
    {
        //linked body parameters did not match.  Return only this object.
        output = this;
    }

    //return output
    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
void matCrossForce::setLinkedBody(matBody &BodIn)
{
    this->plinkbody = BodIn;

    //Also set the linkedId to the same thing.  Ensure the two are always in sync.
    this->plinkid = BodIn.Id();
}

//------------------------------------------Function Separator --------------------------------------------------------
matReactForce matBody::getlinkedbody()
{
    return this->plinkbody;
}

//------------------------------------------Function Separator --------------------------------------------------------
void matCrossForce::setLinkedId(int bodId)
{
    this->plinkbody = bodId;
}

//------------------------------------------Function Separator --------------------------------------------------------
int matCrossForce::getLinkedId()
{
    return this->plinkbody;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<int> matCrossForce::getmatDims()
{
    vector<int> output(2);

    //Get number of rows and number of columns
    output[0] = this->pderiv[0].n_rows;
    output[1] = this->pderiv[0].n_cols;

    return output;
}
