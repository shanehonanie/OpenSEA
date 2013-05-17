#include "force.h"


Force::Force()
{
}


Force::~Force()
{
}

void Force::setForceName(string newName)
{
	forceName = newName;
}

string Force::getForceName()
{
	return forceName;
}

