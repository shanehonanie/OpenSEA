#include "seaenvinput.h"


SeaenvInput::SeaenvInput() : ReadInput()
{
	LEGAL_KEYWORD_00 = "wave_custom";
	LEGAL_KEYWORD_01 = "name";
	LEGAL_KEYWORD_02 = "frequencies";
	LEGAL_KEYWORD_03 = "waveenergy";
	LEGAL_KEYWORD_04 = "sea_custom";
	LEGAL_KEYWORD_05 = "spreadpoint";
	LEGAL_KEYWORD_06 = "angle";
	LEGAL_KEYWORD_07 = "spectrum";
	LEGAL_KEYWORD_08 = "scale";
	LEGAL_KEYWORD_09 = "spreadname";
	initializeDefaults();
}


SeaenvInput::~SeaenvInput()
{
}


void SeaenvInput::initializeDefaults()
{

}

int SeaenvInput::legalKeyword(string stringIn)
{
	if (stringIn == LEGAL_KEYWORD_00)
		return WAVE_CUSTOM;
	else if (stringIn == LEGAL_KEYWORD_01)
		return NAME;
	else if (stringIn == LEGAL_KEYWORD_02)
		return FREQUENCIES;
	else if (stringIn == LEGAL_KEYWORD_03)
		return WAVE_ENERGY;
	else if (stringIn == LEGAL_KEYWORD_04)
		return SEA_CUSTOM;
	else if (stringIn == LEGAL_KEYWORD_05)
		return SPREADPOINT;
	else if (stringIn == LEGAL_KEYWORD_06)
		return ANGLE;
	else if (stringIn == LEGAL_KEYWORD_07)
		return SPECTRUM;
	else if (stringIn == LEGAL_KEYWORD_08)
		return SCALE;
	else if (stringIn == LEGAL_KEYWORD_09)
		return SPREADNAME;
	else
		return -1;
}

//return false if not done, true if done
bool SeaenvInput::keywordHandler(int keyControl, string identifier, string val)
{
	double doubleVal = atof(val.c_str());
	switch(keyControl)
	{
		case WAVE_CUSTOM:
			return true;
		case NAME:
			seaEnviroment.setWaveSpectrumName(val);
			return false;
		case SEA_CUSTOM:
			return true;
		case SPREADPOINT:
			return true;
		case ANGLE:
			seaEnviroment.setSpreadModelDirectionAngle(doubleVal);
			return false;
		case SPECTRUM:
			seaEnviroment.setSpreadModelWaveSpectrumName(val);
			return false;
		case SCALE:
			seaEnviroment.setSpreadModelScalingFactor(doubleVal);
			return false;
		case SPREADNAME:
			seaEnviroment.setSpreadModelName(val);
			return false;
		default:
			return true;
	}
}

//enum LegalKeywords { WAVE_CUSTOM = 0, NAME = 1, FREQUENCIES = 2, WAVE_ENERGY = 3, SEA_CUSTOM = 4, SPREADPOINT = 5, ANGLE = 6, SPECTRUM = 7, SCALE = 8, SPREADNAME = 9};

bool SeaenvInput::keywordHandler(int keyControl, vector<string> theListIn, bool isDirect)
{
	//vector<double> theList = convertToDouble(theListIn);
	vector<double> theList;// = theListIn; //Need to write function to convert string to double, this is temp
	for(int i = 0 ; i < theListIn.size(); i++)
	{
		theList.push_back(atof(theListIn[i].c_str()));
	}
			
	switch(keyControl)
	{
		case FREQUENCIES:
			seaEnviroment.setWaveSpectrumFrequencies(theList);
			return false;
		case WAVE_ENERGY: 
			seaEnviroment.setWaveSpectrumWaveEnergy(theList);
			return false;
		default:
			return true;
	}
}

//const string LEGAL_KEYWORD_00 = "wave_custom";
//const string LEGAL_KEYWORD_01 = "name";
//const string LEGAL_KEYWORD_02 = "frequencies";
//const string LEGAL_KEYWORD_03 = "waveenergy";
//const string LEGAL_KEYWORD_04 = "sea_custom";
//const string LEGAL_KEYWORD_05 = "spreadpoint";
//const string LEGAL_KEYWORD_06 = "angle";
//const string LEGAL_KEYWORD_07 = "spectrum";
//const string LEGAL_KEYWORD_08 = "scale";
//enum LegalKeywords { WAVE_CUSTOM = 0, NAME = 1, FREQUENCIES = 2, WAVE_ENERGY = 3, SEA_CUSTOM = 4, SPREADPOINT = 5, ANGLE = 6, SPECTRUM = 7, SCALE = 8};

void SeaenvInput::testPrint()
{
	cout << "System Test Print -- SeaEnviroment" << endl;
	cout << "--------------------------------" << endl;
	seaEnviroment.testPrint();
	cout << "--------------------------------" << endl;
}

