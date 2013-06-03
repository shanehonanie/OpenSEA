#ifndef WAVESPREADMODEL_H
#define WAVESPREADMODEL_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds all data for a wave spread model.
 */

class WaveSpreadModel
{
public:
	WaveSpreadModel(); /**< The default constructor. */
	~WaveSpreadModel(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Set the name of this spread model.
	 * @param newName The name of this spread model.
	 */
	void setSpreadModelName(string);

	/**
	 * Set the name of this spectrum.
	 * @param newName The name of this spectrum.
	 */
	void setSelectedpectrumName(string);

	/**
	 * Set the name of this spectrum.
	 * @param val The spread model angle.
	 */
	void setSelectedSpreadModelAngle(double);

	/**
	 * Set the name of scaling factor.
	 * @param val The scaling factor.
	 */
	void setSpectrumScalingFactor(double);
private:
	string spreadModelName; /**< The spread model name. */
	int currentSpreadEntry; /**< The current spread entry. */

	struct SpreadEntry; /**< Forward Declaration. */
	vector<SpreadEntry> spreadEntries; /**< List of spread entries. */

	struct SpreadEntry
	{
		double directionAngle;  /**< The direction angle. */
		string waveSpectrumName; /**< The wave spectrum name. */
		double scalingFactor; /**< The scaling factor. */
	};
};
#endif
