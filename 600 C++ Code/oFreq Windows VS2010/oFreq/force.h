#ifndef FORCE_H
#define FORCE_H
#include "readinputfile.h"
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Force
{
public:
	Force();
	~Force();
	void setForceName(string);
	string getForceName();
protected:
	string forceName;
private:
	
};
#endif
