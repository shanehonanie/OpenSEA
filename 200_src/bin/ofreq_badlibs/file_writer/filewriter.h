#ifndef FILEWRITER_H
#define FILEWRITER_H
#include "../derived_outputs/outputslist.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>  
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem; //for using boost file system

const string HEADER_FILENAME = "OpenSeaHeader.txt";
const string DIRECTIONS_FILENAME = "directions.out";
const string FREQUENCIES_FILENAME = "frequencies.out";
const string GLOBAL_ACCELERATION_FILENAME = "accglobal.out";
const string GLOBAL_MOTION_FILENAME = "motglobal.out";
const string GLOBAL_VELOCITY_FILENAME = "velglobal.out";
const string GLOBAL_ACCELERATION_OBJECT = "accglobal";
const string GLOBAL_MOTION_OBJECT = "motglobal";
const string GLOBAL_VELOCITY_OBJECT = "velglobal";
const string LIST_BEGIN2 = "(";
const string LIST_END2 = ");";
const string OBJECT_BEGIN2 = "{";
const string OBJECT_END2 = "}";
const string END = ";";
const string NAME = "name";
const string DATA = "data";
const string VALUE = "value";
const string FREQUENCY = "frequency";
const string DIRECTION = "direction";
const string VERSION = "version";
const string FORMAT = "format";
const string OBJECT = "object";
const string VERSION_INFO = "1.0";
const string FORMAT_INFO = "ascii";
const string SEAFILE2 = "seafile";
const string BODY = "body";
const string DIR_NAME = "d";
const string BREAK_TOP = "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n";
const string BREAK_BOTTOM = "// ************************************************************************* //";

/**
 * This class write all outputs to files.
 */

class FileWriter
{
public:
	/**
	 * Constructor on creation sets header, write wave directions & frequencies to file, and removes old directories
	 * @param fileDirIn The directory to write outputs.
	 * @param theDirectionsListIn The list of wave directions.
	 * @param theFrequenciesListIn The list of wave frequncies
	 */
	FileWriter(string, vector<double>, vector<double>);
	~FileWriter(); /**< The default destructor, nothing happens here. */

	/**
	 * Sets the outputs that will be written to file later.
	 * @param theOutputsListIn The list of outputs.
	 */
	void setOutputs(OutputsList);

	/**
	 * Writes the outputs list to file.
	 * @param curWaveDirection The current wave direction.
	 * @return true if write successful.
	 */
	bool writeToFile(int);

	/**
	 * Writes the directions list to file.
	 * @param directionList The list of directions.
	 * @return true if write successful.
	 */
	bool writeDirectionsToFile(vector<double>);

	/**
	 * Writes the frequencies list to file.
	 * @param frequencyList The list of frequencies.
	 * @return true if write successful.
	 */
	bool writeFrequenciesToFile(vector<double>);
	void setHeader(); /**< Reads in from input file the header to be used in all files. */

	/**
	 * Set information about the file to be written after header and above data, included in the seafile block.
	 * @param objectIn The name of the object.
	 */
	void setFileInfo(string); 

	/**
	 * Remove all old directiories & files written by oFreq previous run.
	 * @return Return true if all files & directories were successfully deleted.
	 */
	bool removeOldDirectories();

private:
	string oFreq_Directory; /**< The oFreq directory */
	string header; /**< The header to be included in all files */
	string fileInfo; /**< The seafile block information. */
	OutputsList theOutputsList; /**< List of outputs to be written to files. */
	vector<double> thefrequenciesList; /**< List of all wave frequencies. */
	vector<double> theDirectionsList; /**< List of of wave directions. */
};
#endif
