#ifndef FORCECROSSBODY_H
#define FORCECROSSBODY_H
#include "force.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ForceCrossBody: public Force
{
public:
	ForceCrossBody();
	~ForceCrossBody();
};
#endif

