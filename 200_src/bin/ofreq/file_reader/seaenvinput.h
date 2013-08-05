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
#ifndef SEAENVINPUT_H
#define SEAENVINPU_H
#include "readinputfile.h"
#include "../wave_calcs/seaenviroment.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class parses input from file and stores the data appropriately in the SeaEnviroment object.
 */

class SeaenvInput : public ReadInput
{
public:
	SeaenvInput(); /**< The default constructor. */
	~SeaenvInput(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Print to console all data members. */
protected:
	void initializeDefaults(); /**< For future use, does nothing as of now. */

	/**
	 * Returns int greater than 0 if the keyword is legal, the int returned specifies how to handle data in keywordHandler.
	 * @param stringIn Check if a valid keyword.
	 * @return int value which tells keywordHandler how to handle the data.
	 */
	int legalKeyword(string);

	/**
	 * Stores the data if valid keyword according to the legealKeyword function.
	 * @param keyControl Indicated which case in switch function to use.
	 * @param identifier The keyword.
	 * @param val The value associated with the keyword.
	 * @return false if not done reading data, true to move onto next keyword in parser.
	 */
	bool keywordHandler(int, string, string);

	/**
	 * Stores the list data if valid keyword according to the legealKeyword function.
	 * @param keyControl Indicated which case in switch function to use.
	 * @param theListIn List of Values.
	 * @param isDirect True if Direct Access List, False if Sequenctial List.
	 * @return false if not done reading data, true to move onto next keyword in parser.
	 */
	bool keywordHandler(int, vector<string>, bool);

private:
	SeaEnviroment seaEnviroment; /**< Sea ENviroment Object. */
	string LEGAL_KEYWORD_00; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_01; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_02; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_03; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_04; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_05; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_06; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_07; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_08; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_09; /**< Legal Keyword in data File. */

	/**
	 * enum is used to assign legal keywords an int value so they can be handled appropriately.
	 */
	enum LegalKeywords { WAVE_CUSTOM = 0, NAME = 1, FREQUENCIES = 2, WAVE_ENERGY = 3, SEA_CUSTOM = 4, SPREADPOINT = 5, ANGLE = 6, SPECTRUM = 7, SCALE = 8, SPREADNAME = 9};
};
#endif
