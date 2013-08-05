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
#ifndef WAVESPECTRUMMODEL_H
#define WAVESPECTRUMMODEL_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for a wave spectrum model.
 */

class WaveSpectrumModel
{
public:
	WaveSpectrumModel(); /**< The default constructor. */
	~WaveSpectrumModel(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Retrieve the name of this spectrum.
	 * @return The name of this spectrum.
	 */
	string getSpectrumName();

	/**
	 * Set the name of this spectrum.
	 * @param newName The name of this spectrum.
	 */
	void setSpectrumName(string);

	/**
	 * Set the list of wave frequencies.
	 * @param theListIn The list of wave frequencies.
	 */
	void setFrequencies(vector<double>);

	/**
	 * Set the list of wave energy.
	 * @param theListIn The list of wave energy.
	 */
	void setWaveEnergy(vector<double>);

	/**
	 * Retrieve the name of this spectrum.
	 * @return The name of this spectrum.
	 */
	string getName();
	
private:
	string spectrumName; /**< The spectrum name. */
	vector<double> frequencies; /**< The list of wave frequencies. */
	vector<double> waveEnergy; /**< The list of wave energy. */
};
#endif

