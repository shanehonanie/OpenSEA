#ifndef SYSTEM_H
#define SYSTEM_H
#include "wavedirections.h"
#include "wavefrequencies.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/**
 * This class holds data for the system object.
 */

class System
{
public:
	System(); /**< The default constructor. */
	~System(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Sets the analysis ype.
	 * @param analysisTypeIn The analysis type.
	 */
	void setAnalysisType(string);

	/**
	 * Sets the wave frequencies.
	 * @param vecIn The list of wave frequencies.
	 */
	void setWaveFrequencies(vector<double>);

	/**
	 * Sets the wave directions.
	 * @param vecIn The list of wave directions.
	 */
	void setWaveDirections(vector<double>);

	/**
	 * Sets the spread model.
	 * @param spreadIn The spread model.
	 */
	void setSpreadModel(string);

	/**
	 * Retrieve the list of wave frequencies.
	 * @return The list of wave frequencies.
	 */
	vector<double> getWaveFrequencies();

	/**
	 * Retrieve the list of wave directions.
	 * @return The list of wave directions.
	 */
	vector<double> getWaveDirections();

private:
	string analysisType; /**< The analysis type. */
	WaveDirections waveDirections; /**< The wave directions object. */
	WaveFrequencies waveFrequencies; /**< The wave frequencies object. */
};
#endif

