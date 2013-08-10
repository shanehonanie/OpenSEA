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

#include "body.h"

//------------------------------------------Function Separator --------------------------------------------------------
Body::Body()
{
    //Initialize private variables with zeros
    pmassMat.zeros(6,6);
    pCentroid.zeros(3,1);
    pPosn.zeros(3,1);
}

//------------------------------------------Function Separator --------------------------------------------------------
Body::~Body()
{
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::testPrint()
{
	cout << "bodyName: " << bodyName << endl;
	cout << "hydrobody: " << hydroBody << endl;
	cout << "heading: " << heading << endl;
	cout << "motionModel: " << motionModel << endl;
	cout << "mass: " << mass << endl;
	cout << "ixx: " << momentOfInertiaXX << endl; //Ixx
	cout << "iyy: " << momentOfInertiaYY << endl; //Iyy
	cout << "izz: " << momentOfInertiaZZ << endl; //Izz
	cout << "ixy: " << crossMomentOfInertiaXY << endl;
	cout << "ixz" << crossMomentOfInertiaXZ << endl;
	cout << "iyz: " << crossMomentOfInertiaYZ << endl;
	cout << "centroidX: " << centroidX << endl;
	cout << "centroidY: " << centroidY << endl;
	cout << "centroidZ: " << centroidZ << endl;
	for(unsigned int i = 0 ;i < userActiveForces.size(); i++)
		cout << "activeForce[" << i << "]: " << userActiveForces[i] << endl;
	for(unsigned int i = 0 ;i < userReactiveForces.size(); i++)
		cout << "reactiveForce[" << i << "]: " << userReactiveForces[i] << endl;
	//cout << "linkedBody: " << linkedBody << endl;
	//cout << "crossBodyForceName: " << crossBodyName << endl;
	//for(unsigned int i = 0 ;i < crossBodyForces.size(); i++)
	//	cout << "crossBodyForce[" << i << "]: " << crossBodyForces[i] << endl;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setBodyName(string newName)
{
	bodyName = newName;
}

//------------------------------------------Function Separator --------------------------------------------------------
string &Body::BodyName()
{
    return bodyName;
}

//------------------------------------------Function Separator --------------------------------------------------------
string &Body::HydroBodyName()
{
    return hydroBody;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setHydroBodyName(string newName)
{
	hydroBody = newName;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setHeading(double newHeading)
{
    phead = newHeading;
}

//------------------------------------------Function Separator --------------------------------------------------------
double &Body::Heading()
{
    return phead;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setUserActiveForces(vector<string> newForceList)
{
	userActiveForces = newForceList;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setUserReactiveForces(vector<string> newForceList)
{
	userReactiveForces = newForceList;
}

//------------------------------------------Function Separator --------------------------------------------------------
//Not used REMOVE after verify correct parsing
void Body::setUserCrossBodyForces(vector<string> newCrossBodyList)
{

	if(newCrossBodyList.size() % 2 == 0)
	{
	
		for(unsigned int i = 0; i < newCrossBodyList.size(); i++)
		{
			if(i & 2 == 0) //even index, add to crossBodyForceLisyt
				userCrossBodyForces.push_back(newCrossBodyList[i]);
			else //Odd index, add to linkedBody List
				addLinkedBody(newCrossBodyList[i]);
		}
	}
	else
		cout << "Error, must provide cross body force and linked body name as a pair" << endl;
	
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setHydroActiveForces(vector<string> newForceList)
{
	hydroActiveForces = newForceList;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setHydroReactiveForces(vector<string> newForceList)
{
	hydroReactiveForces = newForceList;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setHydroCrossBodyForces(vector<string> newForceList)
{
	hydroCrossBodyForces = newForceList;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::addLinkedBody(string newLinkedBody)
{
	linkedBody.push_back(newLinkedBody);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMass(double newMass)
{
    pmassMat(0,0) = newMass;   //X position mass.
    pmassMat(1,1) = newMass;   //Y position mass.
    pmassMat(2,2) = newMass;   //Z position mass.
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getMass()
{
    return pMass(0,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIxx(double newXX)
{
    pmassMat(3,3) = newXX;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getMomIxx()
{
    return pmassMat(3,3);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIyy(double newYY)
{
    pmassMat(4,4) = newYY;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getMomIyy()
{
    return pmassMat(4,4);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIzz(double newZZ)
{
    pmassMat(5,5) = newZZ;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getMomIzz()
{
    return pmassMat(5,5);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIxy(double newXY)
{
    pmassMat(3,4) = newXY;
    pmassMat(4,3) = newXY;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::getMomIxy()
{
    return pmassMat(3,4);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIxz(double newXZ)
{
    pmassMat(3,5) = newXZ;
    pmassMat(5,3) = newXZ;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::getMomIxz()
{
    return pmassMat(3,5);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMomIyz(double newYZ)
{
    pmassMat(4,5) = newYZ;
    pmassMat(5,4) = newYZ;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::getMomIyz()
{
    return pmassMat(4,5);
}

//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> Body::getMassMatrix()
{
    return pmassMat;
}

//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> &Body::MassMatrix()
{
    return this->getMassMatrix();
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMassMatrix(Mat<double> MassMatIn)
{
    pmassMat = MassMatIn;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setCenX(double newCenX)
{
    pCentroid(0,0) = newCenX;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getCenX()
{
    return pCentroid(0,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setCenY(double newCenY)
{
    pCentroid(1,0) = newCenY;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getCenY()
{
    return pCentroid(1,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setCenZ(double newCenZ)
{
    pCentroid(2,0) = newCenZ;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getCenZ()
{
    return pCentroid(2,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> Body::getCen()
{
    return pCentroid;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setPosnX(double input)
{
    pPosn(0,0) = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getPosnX()
{
    return pPosn(0,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setPosnY(double input)
{
    pPosn(1,0) = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getPosnY()
{
    return pPosn(1,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setPosnZ(double input)
{
    pPosn(2,0) = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
double Body::getPosnZ()
{
    return pPosn(2,0);
}

//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> Body::getPosn()
{
    return pPosn;
}

//------------------------------------------Function Separator --------------------------------------------------------
Mat<double> &Body::Posn()
{
    return pPosn;
}

//------------------------------------------Function Separator --------------------------------------------------------
string Body::getMotionModel()
{
	return motionModel;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setCrossBodyName(string newName)
{
	userCrossBodyForces.push_back(newName);
}

//------------------------------------------Function Separator --------------------------------------------------------
string Body::getBodyName()
{
	return bodyName;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setSolution(cx_mat input)
{
    pSoln = input;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat Body::getSolution()
{
    return pSoln;
}

//------------------------------------------Function Separator --------------------------------------------------------
cx_mat &Body::Solution()
{
    return pSoln;
}

//------------------------------------------Function Separator --------------------------------------------------------
Body Body::Copy()
{
    return this;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<forceActive *> &Body::listForceActive_user()
{
    return plistForceActive_usr;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<forceActive *> &Body::listForceActive_hydro()
{
    return plistForceActive_hydro;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<forceReact *> &Body::listForceReact_user()
{
    return plistForceReact_usr;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<forceReact *> &Body::listForceReact_hydro()
{
    return plistForceReact_hydro;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<Body *> &Body::listCrossBody_user()
{
    return plistForceCross_usr;
}

//------------------------------------------Function Separator --------------------------------------------------------
vector<Body *> &Body::listCrossBody_hydro()
{
    return plistForceCross_hydro;
}

//------------------------------------------Function Separator --------------------------------------------------------
void Body::setMotionModel(string modelName)
{
    motModel = modelName;
}

//------------------------------------------Function Separator --------------------------------------------------------
string Body::getMotionModel()
{
    return motModel;
}

//------------------------------------------Function Separator --------------------------------------------------------
int Body::getEquationCount()
{
    return eqnCount;
}
