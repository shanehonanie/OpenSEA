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

bool DataInput::keywordHandler(int keyControl, vector<string> theListIn)
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
	for(int i = 0; i < fileLocation.size(); i++)
		cout << "fileLocation[" << i << "]: " << fileLocation[i] << endl;
	cout << "--------------------------------" << endl;
}