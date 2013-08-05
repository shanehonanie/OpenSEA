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

#include "seaenviroment.h"


SeaEnviroment::SeaEnviroment() 
{
}


SeaEnviroment::~SeaEnviroment()
{
	/*if( curSpectrum != NULL)
	{
		curSpectrum = NULL;
		delete curSpectrum;
	}*/

	//for(unsigned int i = 0; i < specifiedSpectrum.size(); i++)
	//	delete &specifiedSpectrum[i];

	//for(unsigned int i = 0; i < specifiedSpreadModel.size(); i++)
	//	delete &specifiedSpreadModel[i];
}

void SeaEnviroment::testPrint()
{
	for(unsigned int i = 0; i < specifiedSpectrum.size(); i++)
	{
		cout << "---Spectrum Object " << i+1 << " ---" << endl;
		specifiedSpectrum[i].testPrint();
	}

	for(unsigned int i = 0; i < specifiedSpreadModel.size(); i++)
	{
		cout << "---Spread Model Object " << i << " ---" << endl;
		specifiedSpreadModel[i].testPrint();
	}
	cout << endl;
}

void SeaEnviroment::setWaveSpectrumName(string newName)
{
	WaveSpectrumModel newSpectrumModel;
	newSpectrumModel.setSpectrumName(newName);
	specifiedSpectrum.push_back(newSpectrumModel);
	currentSpectrum = specifiedSpectrum.size() - 1;
}

void SeaEnviroment::setWaveSpectrumFrequencies(vector<double> vecIn)
{
	specifiedSpectrum[currentSpectrum].setFrequencies(vecIn);
}

void SeaEnviroment::setWaveSpectrumWaveEnergy(vector<double> vecIn)
{
	specifiedSpectrum[currentSpectrum].setWaveEnergy(vecIn);
}

//int SeaEnviroment::getCurrentIndex(string searchKey)
//{
//	for(unsigned int i = 0; i < specifiedSpectrum.size() ; i++)
//	{
//		if (searchKey == specifiedSpectrum.getName();
//			return i;
//	}
//}

void SeaEnviroment::setSpreadModelName(string newName)
{
	WaveSpreadModel newSpreadModel;
	newSpreadModel.setSpreadModelName(newName);
	specifiedSpreadModel.push_back(newSpreadModel);
	currentSpreadModel = specifiedSpreadModel.size() - 1;
}

//this is the wave spectrum contained inside "spread entry"
void SeaEnviroment::setSpreadModelWaveSpectrumName(string newName)
{
	specifiedSpreadModel[currentSpreadModel].setSelectedpectrumName(newName);
}

void SeaEnviroment::setSpreadModelDirectionAngle(double val)
{
	specifiedSpreadModel[currentSpreadModel].setSelectedSpreadModelAngle(val);
}


void SeaEnviroment::setSpreadModelScalingFactor(double val)
{
	specifiedSpreadModel[currentSpreadModel].setSpectrumScalingFactor(val);
}
