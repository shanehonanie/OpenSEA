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

#include "bodiesinput.h"


Bodiesinput::Bodiesinput() : ReadInput()
{
	//theUserForces = userForcesIn; //<--delete this after make changes for motion solver
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
			theBodyList[currentBody].setHydroBodyName(val);
			return true;
		case MASSPROP:
			return true;
		case MASS:
			theBodyList[currentBody].setMass(doubleVal);
			return false;
		case IXX:
            theBodyList[currentBody].setMomIxx(doubleVal);
			return false;
		case IYY:
            theBodyList[currentBody].setMomIyy(doubleVal);
			return true;
		case IZZ:
            theBodyList[currentBody].setMomIzz(doubleVal);
			return true;
		case IXY:
            theBodyList[currentBody].setMomIxy(doubleVal);
			return false;
		case IXZ:
            theBodyList[currentBody].setMomIxz(doubleVal);
			return false;
		case IYZ:
            theBodyList[currentBody].setMomIyz(doubleVal);
			return false;
		case CENTROID:
			return false;
		case COG_X:
            theBodyList[currentBody].setCenX(doubleVal);
			return false;
		case COG_Y:
            theBodyList[currentBody].setCenY(doubleVal);
			return false;
		case COG_Z:
            theBodyList[currentBody].setCenZ(doubleVal);
			return false;
		case HEADING:
			theBodyList[currentBody].setHeading(doubleVal);
			return false;
		case MOTION:
			theBodyList[currentBody].setMotionModel(val);
			return false;
		case CROSSBODY_NAME:
			theBodyList[currentBody].setCrossBodyName(val);
			return false;
		case LINKED_BODY:
			theBodyList[currentBody].addLinkedBody(val);
			return false;
		default:
			return false;
	}
}
bool Bodiesinput::keywordHandler(int keyControl, vector<string> theListIn, bool isDirect)
{
			
	switch(keyControl)
	{
		case FORCE_ACIVE:
			theBodyList[currentBody].setUserActiveForces(theListIn);
			return true;
		case FORCE_REACTIVE:
			theBodyList[currentBody].setUserReactiveForces(theListIn);
			return true;
		case FORCE_CROSSBODY:
			theBodyList[currentBody].setUserCrossBodyForces(theListIn);
			return true;
		default:
			return false;
	}
}

void Bodiesinput::addNewBody(string newName)
{
	Body newBody;
	newBody.setBodyName(newName);
	theBodyList.push_back(newBody);
	currentBody = theBodyList.size() - 1;
}

void Bodiesinput::testPrint()
{
	cout << "System Test Print -- Body" << endl;
	cout << "--------------------------------" << endl;
	for(unsigned int i = 0; i < theBodyList.size(); i ++)
	{
		cout << "--Body Object " << (i + 1) << "--" << endl;
		theBodyList[i].testPrint();
		cout << endl;
	}
	cout << "--------------------------------" << endl;
}

vector<Body>& Bodiesinput::getBodyData()
{
	return theBodyList;
}

//void Bodiesinput::createNewBodyForceMatrix()
//{
//	matBody temp;
//	bfm.push_back(temp);
//	bfm[0].setData(body[0], theUserForces);
//}
