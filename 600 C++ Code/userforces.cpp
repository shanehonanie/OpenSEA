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
		int curIndex = reactiveForces.size() - 1;
		reactiveForces[curIndex].setCurDerivative(newOrder);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = crossBodyForces.size() - 1;
		crossBodyForces[curIndex].setCurDerivative(newOrder);
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
		int curIndex = reactiveForces.size() - 1;
		reactiveForces[curIndex].setCurEquationNum(newEquationNum);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = crossBodyForces.size() - 1;
		crossBodyForces[curIndex].setCurEquationNum(newEquationNum);
	}
}

void UserForces::setCoeff(vector<string> newList, bool isDirectList)
{

	if(curForceType == ACTIVE_FORCE)
	{
		int curIndex = activeForces.size() - 1;
		activeForces[curIndex].setCoeff(newList, isDirectList);
	}
	else if(curForceType == REACTIVE_FORCE)
	{
		int curIndex = reactiveForces.size() - 1;
		reactiveForces[curIndex].setCoeff(newList, isDirectList);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		int curIndex = crossBodyForces.size() - 1;
		crossBodyForces[curIndex].setCoeff(newList, isDirectList);
	}
}

void UserForces::addNewForce(string newForceName)
{
	if (curForceType == ACTIVE_FORCE)
	{
		ForceActive newForce;
		newForce.setForceName(newForceName);
		activeForces.push_back(newForce);
	}
	else if (curForceType == REACTIVE_FORCE)
	{
		ForceReactive newForce;
		newForce.setForceName(newForceName);
		reactiveForces.push_back(newForce);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		ForceCrossBody newForce;
		newForce.setForceName(newForceName);
		crossBodyForces.push_back(newForce);
	}
}

void UserForces::testPrint()
{
	for(int i = 0; i < reactiveForces.size(); i++)
	{
		reactiveForces[i].testPrint();
	}

	for(int i = 0; i < crossBodyForces.size(); i++)
	{
		crossBodyForces[i].testPrint();
	}

	for(int i = 0; i < activeForces.size(); i++)
	{
		activeForces[i].testPrint();
	}

}

