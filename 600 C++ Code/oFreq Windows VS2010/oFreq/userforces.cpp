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
		ForceActive newForce;
		newForce.setForceName(newForceName);
		userActiveForces.push_back(newForce);
	}
	else if (curForceType == REACTIVE_FORCE)
	{
		ForceReactive newForce;
		newForce.setForceName(newForceName);
		userReactiveForces.push_back(newForce);
	}
	else //curForceType == CROSSBODY_FORCE
	{
		ForceCrossBody newForce;
		newForce.setForceName(newForceName);
		userCrossBodyForces.push_back(newForce);
	}
}

void UserForces::testPrint()
{
	for(int i = 0; i < userReactiveForces.size(); i++)
	{
		userReactiveForces[i].testPrint();
	}

	for(int i = 0; i < userCrossBodyForces.size(); i++)
	{
		userCrossBodyForces[i].testPrint();
	}

	for(int i = 0; i < userActiveForces.size(); i++)
	{
		userActiveForces[i].testPrint();
	}

}

vector<complexDouble> UserForces::getUserActiveForce(string activeForceName)
{
	vector<complexDouble> coefficientsFound;

	for(int i = 0; i < userActiveForces.size(); i++)
	{
		if(activeForceName == userActiveForces[i].getForceName())
			coefficientsFound = userActiveForces[i].getCoefficients();
	}

	return coefficientsFound;
}

vector<Derivative> UserForces::getUserReactiveForce(string reactiveForceName)
{
	vector<Derivative> derivativeListFound;

	for(int i = 0; i < userReactiveForces.size(); i++)
	{
		if(reactiveForceName == userReactiveForces[i].getForceName())
			derivativeListFound = userReactiveForces[i].getDerivatives();
	}

	return derivativeListFound;
}

vector<Derivative> UserForces::getUserCrossBodyForce(string crossBodyForceName)
{
	vector<Derivative> derivativeListFound;

	for(int i = 0; i < userCrossBodyForces.size(); i++)
	{
		if(crossBodyForceName == userCrossBodyForces[i].getForceName())
			derivativeListFound = userCrossBodyForces[i].getDerivatives();
	}

	return derivativeListFound;
}

