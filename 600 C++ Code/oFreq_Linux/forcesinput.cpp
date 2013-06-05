#include "forcesinput.h"


ForcesInput::ForcesInput() : ReadInput()
{
	LEGAL_KEYWORD_00 = "force_active";
	LEGAL_KEYWORD_01 = "name";
	LEGAL_KEYWORD_02 = "force";
	LEGAL_KEYWORD_03 = "equation";
	LEGAL_KEYWORD_04 = "coeff";
	LEGAL_KEYWORD_05 = "force_reactive";
	LEGAL_KEYWORD_06 = "number";
	LEGAL_KEYWORD_07 = "derivative";
	LEGAL_KEYWORD_08 = "order";
	LEGAL_KEYWORD_09 = "force_crossbody";
}


ForcesInput::~ForcesInput()
{
}

void ForcesInput::initializeDefaults()
{}

int ForcesInput::legalKeyword(string stringIn)
{
	if(stringIn == LEGAL_KEYWORD_00)
		return FORCE_ACTIVE;
	else if(stringIn == LEGAL_KEYWORD_01)
		return NAME;
	else if(stringIn == LEGAL_KEYWORD_02)
		return FORCE;
	else if(stringIn == LEGAL_KEYWORD_03)
		return EQUATION;
	else if(stringIn == LEGAL_KEYWORD_04)
		return COEFF;
	else if(stringIn == LEGAL_KEYWORD_05)
		return FORCE_REACTIVE;
	else if(stringIn == LEGAL_KEYWORD_06)
		return NUMBER;
	else if(stringIn == LEGAL_KEYWORD_07)
		return DERIVATIVE;
	else if(stringIn == LEGAL_KEYWORD_08)
		return ORDER;
	else if(stringIn == LEGAL_KEYWORD_09)
		return FORCE_CROSSBODY;
	else
		return -1;
}

//return false if not done, true if done
bool ForcesInput::keywordHandler(int keyControl, string identifier, string val)
{
	//double doubleVal = atof(val.c_str());
	int intVal = atoi(val.c_str());
	switch(keyControl)
	{
		case FORCE_ACTIVE:
			userForces.setCurForceAsActive();
			return true;
		case NAME:
			userForces.addNewForce(val);
			return false;
		case FORCE:
			return false;
		case EQUATION:
			return true;
		case COEFF:
			return true; //might eliminate this keyword and have to fix
		case FORCE_REACTIVE:
			userForces.setCurForceAsReactive();
			return true;
		case NUMBER:
			userForces.setEquationNumber(intVal);
			return false;
		case DERIVATIVE:
			return true;
		case ORDER:
			userForces.setOrderDerivative(intVal);
			return false;
		case FORCE_CROSSBODY:
			userForces.setCurForceAsCrossBody();
			return true;
		default:
			return true;
	}
}

bool ForcesInput::keywordHandler(int keyControl, vector<string> theListIn, bool isDirect)
{
	//vector<double> theList = convertToDouble(theListIn);
	vector<double> theList;// = theListIn; //Need to write function to convert string to double, this is temp
	for(int i = 0 ; i < theListIn.size(); i++)
	{
		theList.push_back(atof(theListIn[i].c_str()));
	}
			
	switch(keyControl)
	{
		case FORCE:
			userForces.setCoeff(theListIn, isDirect);
			return false;
		default:
			return true;
	}
}

void ForcesInput::testPrint()
{
	userForces.testPrint();
}

UserForces ForcesInput::getUserForces()
{
	return userForces;
}

