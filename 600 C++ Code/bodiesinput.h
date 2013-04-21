#ifndef BODIESINPUT_H
#define BODIESINPUT_H
#include "readinputfile.h"
#include "body.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Bodiesinput : public ReadInput
{
public:
	Bodiesinput();
	~Bodiesinput();
	
protected:
	void initializeDefaults();
	void setData(istream& infile);
	int legalKeyword(string);
private:
	vector<Body> body;

};
#endif

