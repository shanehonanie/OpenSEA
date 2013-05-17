#ifndef SEAENVINPUT_H
#define SEAENVINPU_H
#include "readinputfile.h"
#include "seaenviroment.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



class SeaenvInput : public ReadInput
{
public:
	SeaenvInput();
	~SeaenvInput();
	void testPrint();
protected:
	void initializeDefaults();
	int legalKeyword(string);
	bool keywordHandler(int, string, string);
	bool keywordHandler(int, vector<string>, bool);

private:
	SeaEnviroment seaEnviroment;
	enum LegalKeywords { WAVE_CUSTOM = 0, NAME = 1, FREQUENCIES = 2, WAVE_ENERGY = 3, SEA_CUSTOM = 4, SPREADPOINT = 5, ANGLE = 6, SPECTRUM = 7, SCALE = 8, SPREADNAME = 9};
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
};
#endif
