#ifndef READCONTROLFILE_H
#define READCONTROLFILE_H
#include "readinputfile.h"
#include "system.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

class ControlInput : public ReadInput
{
public:
	ControlInput();
	~ControlInput();
	void testPrint();
	
protected:
	void initializeDefaults();
	int legalKeyword(string);
	bool keywordHandler(int, string, string);
	bool keywordHandler(int, vector<string>);

private:
	System system;
	enum LegalKeywords { SYSTEM = 0, ANALYSIS = 1, FREQUENCY = 2, DIRECTION = 3, WAVE_MODEL = 4 };
	string LEGAL_KEYWORD_00;
	string LEGAL_KEYWORD_01;
	string LEGAL_KEYWORD_02;
	string LEGAL_KEYWORD_03;
	string LEGAL_KEYWORD_04;
	
};
#endif

