#ifndef WAVESPECTRUMMODEL_H
#define WAVESPECTRUMMODEL_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for a wave spectrum model.
 */

class WaveSpectrumModel
{
public:
	WaveSpectrumModel(); /**< The default constructor. */
	~WaveSpectrumModel(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Retrieve the name of this spectrum.
	 * @return The name of this spectrum.
	 */
	string getSpectrumName();

	/**
	 * Set the name of this spectrum.
	 * @param newName The name of this spectrum.
	 */
	void setSpectrumName(string);

	/**
	 * Set the list of wave frequencies.
	 * @param theListIn The list of wave frequencies.
	 */
	void setFrequencies(vector<double>);

	/**
	 * Set the list of wave energy.
	 * @param theListIn The list of wave energy.
	 */
	void setWaveEnergy(vector<double>);

	/**
	 * Retrieve the name of this spectrum.
	 * @return The name of this spectrum.
	 */
	string getName();
	
private:
	string spectrumName; /**< The spectrum name. */
	vector<double> frequencies; /**< The list of wave frequencies. */
	vector<double> waveEnergy; /**< The list of wave energy. */
};
#endif

