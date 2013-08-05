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
#ifndef SEAENVIROMENT_H
#define SEAENVIROMENT_H
#include "wavespectrummodel.h"
#include "wavespreadmodel.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for the sea enviroment.
 */

class SeaEnviroment
{
public:
	SeaEnviroment(); /**< The default constructor. */
	~SeaEnviroment(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Sets the wave spectrum.
	 * @param newName The name of the wave spectrum.
	 */
	void setWaveSpectrumName(string);

	/**
	 * Sets the wave frequencies.
	 * @param vecIn The list of wave frequencies.
	 */
	void setWaveSpectrumFrequencies(vector<double>);

	/**
	 * Sets the wave energy.
	 * @param vecIn The list of wave energy.
	 */
	void setWaveSpectrumWaveEnergy(vector<double>);

	/**
	 * Sets the spread model name.
	 * @param newName The name of the spread model to be used.
	 */
	void setSpreadModelName(string);

	/**
	 * Sets spread model direction angle.
	 * @param val The direction angle.
	 */
	void setSpreadModelDirectionAngle(double);

	/**
	 * Sets spread model direction angle.
	 * @param newName The name of the wave spectrum.
	 */
	void setSpreadModelWaveSpectrumName(string);

	/**
	 * Sets scaling factor.
	 * @param val The scaling factor.
	 */
	void setSpreadModelScalingFactor(double);

private:
	vector<WaveSpectrumModel> specifiedSpectrum; /**< The List of wave spectrums. */
	vector<WaveSpreadModel> specifiedSpreadModel; /**< The List of spread models. */
	int currentSpectrum; /**< The current spectrum being used. */
	int currentSpreadModel; /**< The current spread model being used. */
};
#endif
