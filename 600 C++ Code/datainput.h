#ifndef DATAINPUT_H
#define DATAINPUT_H
#include "readinputfile.h"
#include "hydrodynamicinput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class DataInput : public ReadInput
{
public:
	DataInput();
	~DataInput();

protected:
	void initializeDefaults();
	void setData(istream& infile);
	int legalKeyword(string);
private:
	vector<string> fileLocation;

};
#endif
