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

#include "wavespectrummodel.h"


WaveSpectrumModel::WaveSpectrumModel()
{}


WaveSpectrumModel::~WaveSpectrumModel()
{}

void WaveSpectrumModel::testPrint()
{
	cout << "spectrumName: " << spectrumName << endl;
	for(unsigned int i = 0; i < frequencies.size(); i ++)
	{
		cout << "frequencies[" << i << "]: " << frequencies[i] << endl;
	}

	for(unsigned int i = 0; i < waveEnergy.size(); i ++)
	{
		cout << "waveEnergy[" << i << "]: " << waveEnergy[i] << endl;
	}
}

string WaveSpectrumModel::getSpectrumName()
{
	return spectrumName;
}

void WaveSpectrumModel::setFrequencies(vector<double> theListIn)
{
	for(unsigned int i = 0; i < theListIn.size(); i++)
	{
		frequencies.push_back(theListIn[i]);
	}
}

void WaveSpectrumModel::setWaveEnergy(vector<double> theListIn)
{
	for(unsigned int i = 0; i < theListIn.size(); i++)
	{
		waveEnergy.push_back(theListIn[i]);
	}
}

void WaveSpectrumModel::setSpectrumName(string newName)
{
	spectrumName = newName;
}

string WaveSpectrumModel::getName()
{
	return spectrumName;
}


