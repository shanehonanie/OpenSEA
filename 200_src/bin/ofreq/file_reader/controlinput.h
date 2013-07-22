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

/**
 * This class parses input from file and stores the data appropriately in the System object.
 */

class ControlInput : public ReadInput
{
public:
	ControlInput(); /**< The default constructor. */
	~ControlInput();/**< The default destructor, nothing happens here. */
	void testPrint(); /**< Print to console all data members. */

	/**
	 * Get function to retrieve wave frequencies.
	 * @return the list of wave frequencies.
	 */
	vector<double> getWaveFrequencies();

	/**
	 * Get function to retrieve wave directions.
	 * @return the list of wave directions.
	 */
	vector<double> getWaveDirections();
	
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
	System system; /**< The system object. */

	/**
	 * enum is used to assign legal keywords an int value so they can be handled appropriately.
	 */
	enum LegalKeywords { SYSTEM = 0, ANALYSIS = 1, FREQUENCY = 2, DIRECTION = 3, WAVE_MODEL = 4 };


	string LEGAL_KEYWORD_00; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_01; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_02; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_03; /**< Legal Keyword in data File. */
	string LEGAL_KEYWORD_04; /**< Legal Keyword in data File. */
	
};
#endif

