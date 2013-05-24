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
	void testPrint();

protected:
	void initializeDefaults();
	int legalKeyword(string);
	bool keywordHandler(int, string, string);
	bool keywordHandler(int, vector<string>, bool);
private:
	vector<string> fileLocation;
	enum LegalKeywords {HYDRO_FILES = 0, FILE_LOCATION = 1 };
	string LEGAL_KEYWORD_00;
	string LEGAL_KEYWORD_01;
};
#endif
