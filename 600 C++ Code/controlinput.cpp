#include "controlinput.h"


ControlInput::ControlInput() : ReadInput()
{
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
		return 0;
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
bool ControlInput::keywordHandler(int keyControl, vector<string> theListIn)
{
	//vector<double> theList = convertToDouble(theListIn);
	vector<double> theList;// = theListIn; //Need to write function to convert string to double, this is temp
	for(int i = 0 ; i < theListIn.size(); i++)
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
	cout << "System Test Print" << endl;
	cout << "--------------------------------" << endl;
	system.testPrint();
	cout << "--------------------------------" << endl;
}

vector<double> convertToDouble(vector<string> strVecIn)
{
	vector<double> newList;

	/*for(int i = 0; i < strVecIn.size(); i++)
	{
		newList.push_back();
	}*/
	return newList;
}