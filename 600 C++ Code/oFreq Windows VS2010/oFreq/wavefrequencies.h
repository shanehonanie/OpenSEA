#ifndef WAVEFREQUENCIES_H
#define WAVEFREQUENCIES_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds data for the wave frequencies.
 */

class WaveFrequencies
{
public:
	WaveFrequencies(); /**< The default constructor. */
	~WaveFrequencies(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */
	//void addFrequency(double);

	/**
	 * Sets the list of wave frequencies..
	 * @param theListIn The list of wave frequencies.
	 */
	void setFrequencies(vector<double>);

	/**
	 * Retrieve the list of wave frequencies.
	 * @return The list of wave frequencies.
	 */
	vector<double> getWaveFrequencies();
private:
	vector<double> frequencies; /**< The list of wave frequencies. */
};
#endif

