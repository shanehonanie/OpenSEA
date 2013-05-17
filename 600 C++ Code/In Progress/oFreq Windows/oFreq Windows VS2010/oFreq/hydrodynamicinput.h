#ifndef HYDRODYNAMICINPUT_H
#define HYDRODYNAMICINPUT_H
#include "readinputfile.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class HydrodynamicInput : public ReadInput
{
public:
	HydrodynamicInput();
	~HydrodynamicInput();
protected:
	void initializeDefaults();
	void setData(istream&);
	int legalKeyword(string);
private:
	vector<string> fileLocation;
};
#endif

