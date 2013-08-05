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

#include "controlinput.h"


ControlInput::ControlInput() : ReadInput()
{
	LEGAL_KEYWORD_00 = "system";
	LEGAL_KEYWORD_01 = "analysis";
	LEGAL_KEYWORD_02 = "frequency";
	LEGAL_KEYWORD_03 = "direction";
	LEGAL_KEYWORD_04 = "wavemodel";
	initializeDefaults();
}


ControlInput::~ControlInput()
{
}

void ControlInput::initializeDefaults()
{
	
}	


int ControlInput::legalKeyword(string stringIn)
{
	if(stringIn == LEGAL_KEYWORD_00)
		return SYSTEM;
	else if(stringIn == LEGAL_KEYWORD_01)
		return ANALYSIS;
	else if (stringIn == LEGAL_KEYWORD_02)
		return FREQUENCY;
	else if(stringIn == LEGAL_KEYWORD_03)
		return DIRECTION;
	else if (stringIn == LEGAL_KEYWORD_04)
		return WAVE_MODEL;
	else
		return -1;
}

//return false if not done, true if done
bool ControlInput::keywordHandler(int keyControl, string identifier, string val)
{
	switch(keyControl)
	{
		case SYSTEM:
			return true;
		case ANALYSIS:
			system.setAnalysisType(val);
			return false;
		case WAVE_MODEL:
			system.setSpreadModel(val);
			return false;
		default:
			return true;
	}
}
bool ControlInput::keywordHandler(int keyControl, vector<string> theListIn, bool isDirect)
{
	//vector<double> theList = convertToDouble(theListIn);
	vector<double> theList;// = theListIn; //Need to write function to convert string to double, this is temp
	for(unsigned int i = 0 ; i < theListIn.size(); i++)
	{
		theList.push_back(atof(theListIn[i].c_str()));
	}
			
	switch(keyControl)
	{
		case FREQUENCY:
			system.setWaveFrequencies(theList);
			return true;
		case DIRECTION: 
			system.setWaveDirections(theList);
			return true;
		default:
			return false;
	}
}

void ControlInput::testPrint()
{
	cout << "System Test Print -- System" << endl;
	cout << "--------------------------------" << endl;
	system.testPrint();
	cout << "--------------------------------" << endl;
}

vector<double> ControlInput::getWaveFrequencies()
{
	return system.getWaveFrequencies();
}

vector<double> ControlInput::getWaveDirections()
{
	return system.getWaveDirections();
}
