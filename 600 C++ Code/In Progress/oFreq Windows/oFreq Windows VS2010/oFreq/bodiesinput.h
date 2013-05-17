#ifndef BODIESINPUT_H
#define BODIESINPUT_H
#include "readinputfile.h"
#include "body.h"
#include "bodywithforcematrix.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "userforces.h"
using namespace std;

class Bodiesinput : public ReadInput
{
public:
	Bodiesinput();
	~Bodiesinput();
	void testPrint();
	vector<Body> getBodyData();
	//void createNewBodyForceMatrix();
	
protected:
	void initializeDefaults();
	int legalKeyword(string);
	bool keywordHandler(int, string, string);
	bool keywordHandler(int, vector<string>, bool);
	void addNewBody(string);
	
private:
	vector<Body> body;
	//vector<BodyWithForceMatrix> bfm;
	//UserForces theUserForces;
	int currentBody;
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
	enum LegalKeywords { BODY = 0, NAME = 1, HYDRO_BODY = 2, MASSPROP = 3, MASS = 4, IXX = 5, 
		IYY = 6, IZZ = 7, IXY = 8, IXZ = 9, IYZ = 10, CENTROID = 11, COG_X = 12, COG_Y = 13, 
		COG_Z = 14, HEADING = 15, MOTION = 16, FORCE_ACIVE = 17, FORCE_REACTIVE = 18,
		FORCE_CROSSBODY = 19, CROSSBODY_NAME = 20, LINKED_BODY = 21};
};
#endif

