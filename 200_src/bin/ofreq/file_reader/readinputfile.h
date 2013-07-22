#ifndef READINPUTFILE_H
#define READINPUTFILE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int HEADER_LENGTH = 6; /**< Length of header, This is temp needs to be fixed. */
const string COMMENT_LINE = "//"; /**< Line Comment. */
const string COMMENT_BLOCK_BEGIN = "/*"; /**< Block Comment Begin. */
const string COMMENT_BLOCK_END = "*/"; /**< Block comment end. */
const string END_STATEMENT = ";"; /**< End of statement. */
const string OBJECT_BEGIN = "{"; /**< Object scope begin. */
const string OBJECT_END = "}"; /**< Object scope end */
const string LIST_BEGIN = "("; /**< List scope begin. */
const string LIST_END = ");"; /**< List scope end. */
const string KEY_VAL_SEPERATOR= ":"; /**< Key/Val pair seperator. */
const char EOL = '\n'; /**< newline. */
const int MAX_IGNORE = 15000; /**< Max # of chars to ignore. */
const int UNDEFINED_KEYWORD = -1; /**< Invalid/Undefined keyword. */
const string SEAFILE = "seafile"; /**< seafile object name, used to ignore seafile block. */
const string QUOTE = "\"";

/**
 * This absract class parses input from file and has functions that must be implemented to handle the data.
 */

class ReadInput
{
	
public:
	ReadInput(); /**< The default constructor. */
	~ReadInput(); /**< The default destructor, nothing happens here. */

	/**
	 * Parses input files and handles the data.
	 * @param infile The file that is currently being read in by the parser.
	 */
	void setData(istream&);
	
protected:
	virtual void initializeDefaults() = 0; /**< Must be implemented by child class. */
	virtual int legalKeyword(string) = 0; /**< Must be implemented by child class, determine if keyword is legal. */
	virtual bool keywordHandler(int, string, string) = 0;  /**< Must be implemented by child class, handles single key/val pairs. */
	virtual bool keywordHandler(int, vector<string>, bool) = 0; /**< Must be implemented by child class, handles multiple key/val pairs. */

private:
};
#endif
