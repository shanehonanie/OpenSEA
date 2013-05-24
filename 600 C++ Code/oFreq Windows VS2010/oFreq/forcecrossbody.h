#ifndef FORCECROSSBODY_H
#define FORCECROSSBODY_H
#include "forcereactive.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ForceCrossBody: public ForceReactive
{
public:
	ForceCrossBody();
	~ForceCrossBody();
	void testPrint();
};
#endif

