/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date              Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15 2013       Shane Honanie       Initially created
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
#ifndef WAVESPREADMODEL_H
#define WAVESPREADMODEL_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for a wave spread model.
 */

class WaveSpreadModel
{
public:
	WaveSpreadModel(); /**< The default constructor. */
	~WaveSpreadModel(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Set the name of this spread model.
	 * @param newName The name of this spread model.
	 */
	void setSpreadModelName(string);

	/**
	 * Set the name of this spectrum.
	 * @param newName The name of this spectrum.
	 */
	void setSelectedpectrumName(string);

	/**
	 * Set the name of this spectrum.
	 * @param val The spread model angle.
	 */
	void setSelectedSpreadModelAngle(double);

	/**
	 * Set the name of scaling factor.
	 * @param val The scaling factor.
	 */
	void setSpectrumScalingFactor(double);
private:
	string spreadModelName; /**< The spread model name. */
	int currentSpreadEntry; /**< The current spread entry. */

	struct SpreadEntry; /**< Forward Declaration. */
	vector<SpreadEntry> spreadEntries; /**< List of spread entries. */

	struct SpreadEntry
	{
		double directionAngle;  /**< The direction angle. */
		string waveSpectrumName; /**< The wave spectrum name. */
		double scalingFactor; /**< The scaling factor. */
	};
};
#endif
