#ifndef SEAENVINPUT_H
#define SEAENVINPU_H
#include "readinputfile.h"
#include "seaenviroment.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class SeaenvInput : ReadInput
{
public:
	SeaenvInput();
	~SeaenvInput();

protected:
	void initializeDefaults();
	void setData(istream& infile);
	int legalKeyword(string);

private:
	SeaEnviroment seaEnviroment;
};
#endif
