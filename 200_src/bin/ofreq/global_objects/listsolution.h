/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date          Author                  Description
 *---------------------------------------------------------------------------------------------------------------------
 *Mar 09 2013	Nicholas Barczak		Initially Created
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
 * This class records the list of solutions obtained for a single Body object.  It is essentially a 2D version of the
 * vector<object> class.  But since vector can't handle 2-d storage solutions, this class was created.
 */
#ifndef LISTSOLUTION_H
#define LISTSOLUTION_H
#include "solution.h"
#include <new>
#include <vector>
#include <QtGlobal>
#ifdef Q_OS_WIN
    //References for windows go in here.
#elif defined Q_OS_LINUX
    //References for linux go in here.
#endif

using namespace std;

class listSolution
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Default constructor.
     */
    listSolution();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Constructor with number of wave directions and wave frequencies specified.  Automatically allocates
     * dynamic memory for the specified number of wave directions and wave frequencies.
     * @param dir The new number of wave directions to resize the array to.
     * @param freq The new number of wave frequencies to resize the array to.
     */
    listSolution(int dir, int freq);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * Default destructor.  Frees any memory dynamically assigned.
     */
    ~listSolution();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns a pointer to the solution object at the specified wave direction and frequency.
     * @param dir Integer.  Index of the wave direction desired.
     * @param freq Integer.  Index of the wave frequency desired.
     * @return Returns a pointer to the Solution object at the specified wave direction and wave frequency.  Returned
     * variable is passed by reference.
     */
    Solution &refSolution(int dir, int freq);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the solution object at the specified wave direction and frequency.
     * @param dir Integer.  Index of the wave direction desired.
     * @param freq Integer.  Index of the wave frequency desired.
     * @param soln The solution object to pass in.
     */
    void setSolution(int dir, int freq, Solution soln);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the solution object at the specified wave direction and frequency.
     * @param dir Integer.  Index of the wave direction desired.
     * @param freq Integer.  Index of the wave frequency desired.
     * @return Returns the Solution object at the specified wave direction and wave frequency.  Returned variable is
     * passed by value.
     */
    Solution getSolution(int dir, int freq);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Resizes the 2-D array of Solution objects.  Any existing objects in the array are preserved.  If the
     * array is sized smaller than the existing number of Solution objects, any object beyond the new index range
     * are deleted.
     * @param dir The new number of wave directions to resize the array to.
     * @param freq The new number of wave frequencies to resize the array to.
     */
    void resize(int dir, int freq);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the size of the matrix as a vector of two elements.
     * @return Integer.  Returns the size of the matrix as a vector of two elements.
     */
    vector<int> size();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the number of rows as an integer.  This is the number of wave directions.
     * @return Integer.  Returns the number of rows as an integer.  This is the number of wave directions.
     */
    int n_dirs();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the number of columns as an integer.  This is the number of wave frequencies.
     * @return Integer.  Returns the number of columns as an integer.  This is the number of wave frequencies.
     */
    int n_freqs();

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Array of Solution objects.  Dynamically  allocated.  The first index is the wave direction. (The rows
     * direction.)  The second index is the wave frequency (The columns direction.)
     */
    vector< vector<Solution> > plist;

};
#endif // LISTSOLUTION_H
