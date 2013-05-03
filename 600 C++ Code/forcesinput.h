#ifndef FORCESINPUT_H
#define FORCESINPUT_H
#include "readinputfile.h"
#include "userforces.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class ForcesInput: public ReadInput
{
public:
	ForcesInput();
	~ForcesInput();
	void testPrint();
protected:
	void initializeDefaults();
	int legalKeyword(string);
	bool keywordHandler(int, string, string);
	bool keywordHandler(int, vector<string>, bool);
private:
	UserForces userForces;
	string LEGAL_KEYWORD_00;
	string LEGAL_KEYWORD_01;
	string LEGAL_KEYWORD_02;
	string LEGAL_KEYWORD_03;
	string LEGAL_KEYWORD_04;
	string LEGAL_KEYWORD_05;
	string LEGAL_KEYWORD_06;
	string LEGAL_KEYWORD_07;
	string LEGAL_KEYWORD_08;
	string LEGAL_KEYWORD_09;
	string LEGAL_KEYWORD_10;
	string LEGAL_KEYWORD_11;
	string LEGAL_KEYWORD_12;
	string LEGAL_KEYWORD_13;
	string LEGAL_KEYWORD_14;
	string LEGAL_KEYWORD_15;
	string LEGAL_KEYWORD_16;
	string LEGAL_KEYWORD_17;
	string LEGAL_KEYWORD_18;
	string LEGAL_KEYWORD_19;
	string LEGAL_KEYWORD_20;
	string LEGAL_KEYWORD_21;
	enum LegalKeywords { FORCE_ACTIVE = 0, NAME = 1, FORCE = 2, EQUATION = 3, COEFF = 4, FORCE_REACTIVE = 5, 
		NUMBER = 6, DERIVATIVE = 7, ORDER = 8, FORCE_CROSSBODY = 9};

};
#endif


