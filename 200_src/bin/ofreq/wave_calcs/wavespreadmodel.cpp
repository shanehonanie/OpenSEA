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

#include "wavespreadmodel.h"


WaveSpreadModel::WaveSpreadModel()
{
}


WaveSpreadModel::~WaveSpreadModel()
{
}

void WaveSpreadModel::testPrint()
{
	cout << "SpreadModelName: " << spreadModelName << endl;
	for(unsigned int i = 0; i < spreadEntries.size(); i++)
	{
		cout << "--Entry 1--" << endl;
		cout << "Direction Angle: " << spreadEntries[i].directionAngle << endl;
		cout << "Selected Wave Spectrum: " << spreadEntries[i].waveSpectrumName << endl;
		cout << "Scaling Factor: " << spreadEntries[i].scalingFactor << endl;
	}
}
void WaveSpreadModel::setSpreadModelName(string newName)
{
	spreadModelName = newName;
}

void WaveSpreadModel::setSelectedpectrumName(string newName)
{
	SpreadEntry newSpreadEntry;
	newSpreadEntry.waveSpectrumName = newName;
	spreadEntries.push_back(newSpreadEntry);
	currentSpreadEntry = spreadEntries.size()-1;
}

void WaveSpreadModel::setSelectedSpreadModelAngle(double val)
{
	spreadEntries[currentSpreadEntry].directionAngle = val;
}

void WaveSpreadModel::setSpectrumScalingFactor(double val)
{
	spreadEntries[currentSpreadEntry].scalingFactor = val;
}
