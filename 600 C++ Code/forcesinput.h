#ifndef FORCESINPUT_H
#define FORCESINPUT_H
#include "readinputfile.h"
#include "userforces.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ForcesInput: public ReadInput
{
public:
	ForcesInput();
	~ForcesInput();
protected:
	void initializeDefaults();
	void setData(istream&);
	int legalKeyword(string);
private:
	UserForces userForces;

};
#endif


