#include "bodiesinput.h"


Bodiesinput::Bodiesinput() : ReadInput()
{
	LEGAL_KEYWORD_00 = "body";
	LEGAL_KEYWORD_01 = "name";
	LEGAL_KEYWORD_02 = "hydrobody";
	LEGAL_KEYWORD_03 = "massprop";
	LEGAL_KEYWORD_04 = "mass";
	LEGAL_KEYWORD_05 = "ixx";
	LEGAL_KEYWORD_06 = "iyy";
	LEGAL_KEYWORD_07 = "izz";
	LEGAL_KEYWORD_08 = "ixy";
	LEGAL_KEYWORD_09 = "ixz";
	LEGAL_KEYWORD_10 = "iyz";
	LEGAL_KEYWORD_11 = "centroid";
	LEGAL_KEYWORD_12 = "cogx";
	LEGAL_KEYWORD_13 = "cogy";
	LEGAL_KEYWORD_14 = "cogz";
	LEGAL_KEYWORD_15 = "heading";
	LEGAL_KEYWORD_16 = "motion";
	LEGAL_KEYWORD_17 = "force_active";
	LEGAL_KEYWORD_18 = "force_reactive";
	LEGAL_KEYWORD_19 = "force_crossbody";
	LEGAL_KEYWORD_20 = "cross_body_name";
	LEGAL_KEYWORD_21 = "linkedbody";
}


Bodiesinput::~Bodiesinput()
{
}

void Bodiesinput::initializeDefaults()
{

}

int Bodiesinput::legalKeyword(string stringIn)
{
	if(stringIn == LEGAL_KEYWORD_00)
		return BODY;
	else if(stringIn == LEGAL_KEYWORD_01)
		return NAME;
	else if (stringIn == LEGAL_KEYWORD_02)
		return HYDRO_BODY;
	else if(stringIn == LEGAL_KEYWORD_03)
		return MASSPROP;
	else if (stringIn == LEGAL_KEYWORD_04)
		return MASS;
	else if(stringIn == LEGAL_KEYWORD_05)
		return IXX;
	else if (stringIn == LEGAL_KEYWORD_06)
		return IYY;
	else if(stringIn == LEGAL_KEYWORD_07)
		return IZZ;
	else if (stringIn == LEGAL_KEYWORD_08)
		return IXY;
	else if(stringIn == LEGAL_KEYWORD_09)
		return IXZ;
	else if (stringIn == LEGAL_KEYWORD_10)
		return IYZ;
	else if(stringIn == LEGAL_KEYWORD_11)
		return CENTROID;
	else if (stringIn == LEGAL_KEYWORD_12)
		return COG_X;
	else if(stringIn == LEGAL_KEYWORD_13)
		return COG_Y;
	else if (stringIn == LEGAL_KEYWORD_14)
		return COG_Z;
	else if(stringIn == LEGAL_KEYWORD_15)
		return HEADING;
	else if (stringIn == LEGAL_KEYWORD_16)
		return MOTION;
	else if(stringIn == LEGAL_KEYWORD_17)
		return FORCE_ACIVE;
	else if (stringIn == LEGAL_KEYWORD_18)
		return FORCE_REACTIVE;
	else if(stringIn == LEGAL_KEYWORD_19)
		return FORCE_CROSSBODY;
	else if (stringIn == LEGAL_KEYWORD_20)
		return CROSSBODY_NAME;
	else if (stringIn == LEGAL_KEYWORD_21)
		return LINKED_BODY;
	else
		return -1;
}

//return false if not done, true if done
bool Bodiesinput::keywordHandler(int keyControl, string identifier, string val)
{
	double doubleVal = atof(val.c_str());
	enum LegalKeywords { BODY = 0, NAME = 1, HYDRO_BODY = 2, MASSPROP = 3, MASS = 4, IXX = 5, 
		IYY = 6, IZZ = 7, IXY = 8, IXZ = 9, IYZ = 10, CENTROID = 11, COG_X = 12, COG_Y = 13, 
		COG_Z = 14, HEADING = 15, MOTION = 16, FORCE_ACIVE = 17, FORCE_REACTIVE = 18,
		FORCE_CROSSBODY = 19, CROSSBODY_NAME = 20, LINKED_BODY = 21};
	switch(keyControl)
	{
		case BODY:
			return true;
		case NAME:
			addNewBody(val);
			return true;
		case HYDRO_BODY:
			body[currentBody].setHydroBodyName(val);
			return true;
		case MASSPROP:
			return true;
		case MASS:
			body[currentBody].setMass(doubleVal);
			return false;
		case IXX:
			body[currentBody].setMomentXX(doubleVal);
			return false;
		case IYY:
			body[currentBody].setMomentYY(doubleVal);
			return true;
		case IZZ:
			body[currentBody].setMomentZZ(doubleVal);
			return true;
		case IXY:
			body[currentBody].setCrossMomentXY(doubleVal);
			return false;
		case IXZ:
			body[currentBody].setCrossMomentXZ(doubleVal);
			return false;
		case IYZ:
			body[currentBody].setCrossMomentYZ(doubleVal);
			return false;
		case CENTROID:
			return false;
		case COG_X:
			body[currentBody].setCentroidX(doubleVal);
			return false;
		case COG_Y:
			body[currentBody].setCentroidY(doubleVal);
			return false;
		case COG_Z:
			body[currentBody].setCentroidZ(doubleVal);
			return false;
		case HEADING:
			body[currentBody].setHeading(doubleVal);
			return false;
		case MOTION:
			body[currentBody].setMotionModel(val);
			return false;
		case CROSSBODY_NAME:
			body[currentBody].setCrossBodyName(val);
			return false;
		case LINKED_BODY:
			body[currentBody].setLinkedBody(val);
			return false;
		default:
			return false;
	}
}
bool Bodiesinput::keywordHandler(int keyControl, vector<string> theListIn)
{
			
	switch(keyControl)
	{
		case FORCE_ACIVE:
			body[currentBody].setUserActiveForces(theListIn);
			return true;
		case FORCE_REACTIVE:
			body[currentBody].setUserReactiveForces(theListIn);
			return true;
		case FORCE_CROSSBODY:
			body[currentBody].setUserCrossBodyForces(theListIn);
			return true;
		default:
			return false;
	}
}

void Bodiesinput::addNewBody(string newName)
{
	Body newBody;
	newBody.setBodyName(newName);
	body.push_back(newBody);
	currentBody = body.size() - 1;
}

void Bodiesinput::testPrint()
{
	cout << "System Test Print -- Body" << endl;
	cout << "--------------------------------" << endl;
	for(int i = 0; i < body.size(); i ++)
	{
		cout << "--Body Object " << (i + 1) << "--" << endl;
		body[i].testPrint();
		cout << endl;
	}
	cout << "--------------------------------" << endl;
}

