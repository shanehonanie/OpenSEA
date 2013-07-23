#ifndef SEAENVIROMENT_H
#define SEAENVIROMENT_H
#include "wavespectrummodel.h"
#include "wavespreadmodel.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for the sea enviroment.
 */

class SeaEnviroment
{
public:
	SeaEnviroment(); /**< The default constructor. */
	~SeaEnviroment(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Sets the wave spectrum.
	 * @param newName The name of the wave spectrum.
	 */
	void setWaveSpectrumName(string);

	/**
	 * Sets the wave frequencies.
	 * @param vecIn The list of wave frequencies.
	 */
	void setWaveSpectrumFrequencies(vector<double>);

	/**
	 * Sets the wave energy.
	 * @param vecIn The list of wave energy.
	 */
	void setWaveSpectrumWaveEnergy(vector<double>);

	/**
	 * Sets the spread model name.
	 * @param newName The name of the spread model to be used.
	 */
	void setSpreadModelName(string);

	/**
	 * Sets spread model direction angle.
	 * @param val The direction angle.
	 */
	void setSpreadModelDirectionAngle(double);

	/**
	 * Sets spread model direction angle.
	 * @param newName The name of the wave spectrum.
	 */
	void setSpreadModelWaveSpectrumName(string);

	/**
	 * Sets scaling factor.
	 * @param val The scaling factor.
	 */
	void setSpreadModelScalingFactor(double);

private:
	vector<WaveSpectrumModel> specifiedSpectrum; /**< The List of wave spectrums. */
	vector<WaveSpreadModel> specifiedSpreadModel; /**< The List of spread models. */
	int currentSpectrum; /**< The current spectrum being used. */
	int currentSpreadModel; /**< The current spread model being used. */
};
#endif
