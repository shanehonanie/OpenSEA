#ifndef USERFORCES_H
#define USERFORCES_H
#include "forceactive.h"
#include "forcereactive.h"
#include "forcecrossbody.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class UserForces
{
public:
	UserForces();
	~UserForces();
private:
	vector<ForceActive> activeForce;
	vector<ForceReactive> reactiveForces;
	vector<ForceCrossBody> crossBodyForces;
};
#endif
