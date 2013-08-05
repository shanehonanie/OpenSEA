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

#include "userforces.h"


UserForces::UserForces() : curForceType(-1)
{
	ACTIVE_FORCE = 0;
	REACTIVE_FORCE = 1;
	CROSSBODY_FORCE = 2;
}


UserForces::~UserForces()
{
}

void UserForces::setCurForceAsActive()
{
	curForceType = ACTIVE_FORCE;
}

void UserForces::setCurForceAsReactive()
{
	curForceType = REACTIVE_FORCE;
}

void UserForces::setCurForceAsCrossBody()
{
	curForceType = CROSSBODY_FORCE;
}

void UserForces::setOrderDerivative(int newOrder)
{
	if(curForceType == ACTIVE_FORCE)
	{
		return; //active force dosent have a derivative
	}
	else if(curForceType == REACTIVE_FORCE)
	{
		int curIndex = userReactiveForces.size() - 1;
		userReactiveForces[curIndex].setCurDerivative(newOrder);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = userCrossBodyForces.size() - 1;
		userCrossBodyForces[curIndex].setCurDerivative(newOrder);
	}
}

void UserForces::setEquationNumber(int newEquationNum)
{
	if(curForceType == ACTIVE_FORCE)
	{
		return; //active force equattion number is implied by the order in input file
	}
	else if(curForceType == REACTIVE_FORCE)
	{
		int curIndex = userReactiveForces.size() - 1;
		userReactiveForces[curIndex].setCurEquationNum(newEquationNum);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = userCrossBodyForces.size() - 1;
		userCrossBodyForces[curIndex].setCurEquationNum(newEquationNum);
	}
}

void UserForces::setCoeff(vector<string> newList, bool isDirectList)
{

	if(curForceType == ACTIVE_FORCE)
	{
		int curIndex = userActiveForces.size() - 1;
		userActiveForces[curIndex].setCoeff(newList, isDirectList);
	}
	else if(curForceType == REACTIVE_FORCE)
	{
		int curIndex = userReactiveForces.size() - 1;
		userReactiveForces[curIndex].setCoeff(newList, isDirectList);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = userCrossBodyForces.size() - 1;
		userCrossBodyForces[curIndex].setCoeff(newList, isDirectList);
	}
}

void UserForces::addNewForce(string newForceName)
{
	if (curForceType == ACTIVE_FORCE)
	{
		forceActive newForce;
		newForce.setForceName(newForceName);
		userActiveForces.push_back(newForce);
	}
	else if (curForceType == REACTIVE_FORCE)
	{
		forceReact newForce;
		newForce.setForceName(newForceName);
		userReactiveForces.push_back(newForce);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		forceCross newForce;
		newForce.setForceName(newForceName);
		userCrossBodyForces.push_back(newForce);
	}
}

void UserForces::testPrint()
{
	for(unsigned int i = 0; i < userReactiveForces.size(); i++)
	{
		userReactiveForces[i].testPrint();
	}

	for(unsigned int i = 0; i < userCrossBodyForces.size(); i++)
	{
		userCrossBodyForces[i].testPrint();
	}

	for(unsigned int i = 0; i < userActiveForces.size(); i++)
	{
		userActiveForces[i].testPrint();
	}

}

vector<complexDouble> UserForces::getUserActiveForce(string activeForceName)
{
	vector<complexDouble> coefficientsFound;

	for(unsigned int i = 0; i < userActiveForces.size(); i++)
	{
		if(activeForceName == userActiveForces[i].getForceName())
			coefficientsFound = userActiveForces[i].getCoefficients();
	}

	return coefficientsFound;
}

vector<Derivative> UserForces::getUserReactiveForce(string reactiveForceName)
{
	vector<Derivative> derivativeListFound;

	for(unsigned int i = 0; i < userReactiveForces.size(); i++)
	{
		if(reactiveForceName == userReactiveForces[i].getForceName())
			derivativeListFound = userReactiveForces[i].getDerivatives();
	}

	return derivativeListFound;
}

vector<Derivative> UserForces::getUserCrossBodyForce(string crossBodyForceName)
{
	vector<Derivative> derivativeListFound;

	for(unsigned int i = 0; i < userCrossBodyForces.size(); i++)
	{
		if(crossBodyForceName == userCrossBodyForces[i].getForceName())
			derivativeListFound = userCrossBodyForces[i].getDerivatives();
	}

	return derivativeListFound;
}

