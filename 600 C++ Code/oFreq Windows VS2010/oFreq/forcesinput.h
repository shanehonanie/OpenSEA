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

/**
 * This class parses input from file and stores the data appropriately in the UserForces object.
 */

class ForcesInput: public ReadInput
{
public:
	ForcesInput(); /**< The default constructor. */
	~ForcesInput(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Print to console all data members. */
	UserForces getUserForces(); /**< Returns user forces. */
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
	UserForces userForces; /**< User Forces Object. */
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
	string LEGAL_KEYWORD_10; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_11; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_12; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_13; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_14; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_15; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_16; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_17; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_18; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_19; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_20; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_21; /**< Legal Keyword in data File. */

	/**
	 * enum is used to assign legal keywords an int value so they can be handled appropriately.
	 */
	enum LegalKeywords { FORCE_ACTIVE = 0, NAME = 1, FORCE = 2, EQUATION = 3, COEFF = 4, FORCE_REACTIVE = 5, 
		NUMBER = 6, DERIVATIVE = 7, ORDER = 8, FORCE_CROSSBODY = 9};
};
#endif


