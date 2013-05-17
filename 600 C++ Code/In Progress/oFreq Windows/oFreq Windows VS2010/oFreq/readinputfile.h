#ifndef READINPUTFILE_H
#define READINPUTFILE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int HEADER_LENGTH = 6;
const string COMMENT_LINE = "//";
const string COMMENT_BLOCK_BEGIN = "/*";
const string COMMENT_BLOCK_END = "*/";
const string END_STATEMENT = ";";
const string OBJECT_BEGIN = "{";
const string OBJECT_END = "}";
const string LIST_BEGIN = "(";
const string LIST_END = ");";
const string KEY_VAL_SEPERATOR= ":";
const char EOL = '\n';
const int MAX_IGNORE = 5000;
const int UNDEFINED_KEYWORD = -1;
const string SEAFILE = "seafile";

class ReadInput
{
	
public:
	ReadInput();
	~ReadInput();
	void setData(istream&);
	
protected:
	virtual void initializeDefaults() = 0;
	virtual int legalKeyword(string) = 0;
	virtual bool keywordHandler(int, string, string) = 0;  //single args
	virtual bool keywordHandler(int, vector<string>, bool) = 0; //sequential list

private:
};
#endif
