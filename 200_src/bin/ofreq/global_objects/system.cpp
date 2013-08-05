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

#include "system.h"


System::System() : waveDirections(), waveFrequencies()
{
	/*waveDirections = new WaveDirections();
	waveFrequencies = new WaveFrequencies();*/
}


System::~System()
{
}

void System::testPrint()
{
	cout << "Analysis Type: " << analysisType << endl;
	waveDirections.testPrint();
	waveFrequencies.testPrint();
	cout << endl;
}

void System::setAnalysisType(string analysisTypeIn)
{
	analysisType = analysisTypeIn;
}

void System::setWaveFrequencies(vector<double> vecIn)
{
	waveFrequencies.setFrequencies(vecIn);
}

void System::setWaveDirections(vector<double> vecIn)
{
	waveDirections.setDirections(vecIn);
}

void System::setSpreadModel(string spreadIn)
{
	waveDirections.setSpreadModel(spreadIn);
}

vector<double> System::getWaveFrequencies()
{
	return waveFrequencies.getWaveFrequencies();
}

vector<double> System::getWaveDirections()
{
	return waveDirections.getWaveDirections();
}
