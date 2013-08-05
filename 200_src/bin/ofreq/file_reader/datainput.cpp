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

#include "datainput.h"


DataInput::DataInput() : ReadInput()
{
	LEGAL_KEYWORD_00 = "hydrofiles";
	LEGAL_KEYWORD_01 = "filelocation";
}


DataInput::~DataInput()
{
}

void DataInput::initializeDefaults()
{

}
int DataInput::legalKeyword(string stringIn)
{
	if(stringIn == LEGAL_KEYWORD_00)
		return HYDRO_FILES;
	else if(stringIn == LEGAL_KEYWORD_01)
		return FILE_LOCATION;
	else
		return -1;
}

bool DataInput::keywordHandler(int keyControl, string identifier, string val)
{
	switch(keyControl)
	{
		case HYDRO_FILES:
			return true;
		default:
			return true;
	}
}

bool DataInput::keywordHandler(int keyControl, vector<string> theListIn, bool isDirect)
{
	switch(keyControl)
	{
		case FILE_LOCATION:
			fileLocation = theListIn;
			return false;
		default:
			return true;
	}
}

void DataInput::testPrint()
{
	cout << "System Test Print -- HYDRODYNAMIC DB Locations" << endl;
	cout << "--------------------------------" << endl;
	for(unsigned int i = 0; i < fileLocation.size(); i++)
		cout << "fileLocation[" << i << "]: " << fileLocation[i] << endl;
	cout << "--------------------------------" << endl;
}
