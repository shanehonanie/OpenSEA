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

#include "listsolution.h"

//------------------------------------------Function Separator --------------------------------------------------------
listSolution::listSolution()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
listSolution::listSolution(int dir, int freq)
{
    //Constructor with wave directions and frequencies specified.
    resize(dir, freq);
}

//------------------------------------------Function Separator --------------------------------------------------------
listSolution::~listSolution()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
Solution &listSolution::refSolution(int dir, int freq)
{
    //Return reference to specified solution object.
    return plist[dir][freq];
}

//------------------------------------------Function Separator --------------------------------------------------------
void listSolution::setSolution(int dir, int freq, Solution soln)
{
    //Set the Solution object with the new value.

    //Check that the specified index is the correct size.  If not, resize.
    if ((dir > n_dirs()) || (freq > n_freqs()))
        this->resize(dir, freq);

    //Set the solution
    plist[dir][freq] = soln;
}

//------------------------------------------Function Separator --------------------------------------------------------
Solution listSolution::getSolution(int dir, int freq)
{
    //Return the solution
    return plist[dir][freq];
}

//------------------------------------------Function Separator --------------------------------------------------------
void listSolution::resize(int dir, int freq)
{
    //Resize the vector
    plist.resize(dir);
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i].reize(freq);
    }
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<int> listSolution::size()
{
    vector<int> output(2);

    output[0] = plist.size();
    output[1] = plist[0].size();

    return output;
}

//------------------------------------------Function Separator --------------------------------------------------------
int listSolution::n_dirs()
{
    return size()[0];
}

//------------------------------------------Function Separator --------------------------------------------------------
int listSolution::n_dirs()
{
    return size()[1];
}
