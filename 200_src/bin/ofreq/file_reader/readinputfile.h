/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date              Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15 2013       Shane Honanie       Initially created
 *
\*-------------------------------------------------------------------------------------------------------------------*/

//License
/*-------------------------------------------------------------------------------------------------------------------*\
 *Copyright Datawave Marine Solutions, 2013.
 *This file is part of OpenSEA.

 *OpenSEA is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *OpenSEA is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with OpenSEA.  If not, see <http://www.gnu.org/licenses/>.
\*-------------------------------------------------------------------------------------------------------------------*/



//######################################### Class Separator ###########################################################
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
