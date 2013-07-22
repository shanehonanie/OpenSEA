#ifndef WAVEDIRECTIONS_H
#define WAVEDIRECTIONS_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This class holds data for the wave directions.
 */

class WaveDirections
{
public:
	WaveDirections(); /**< The default constructor. */
	~WaveDirections(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	//void addDirection(int);

	/**
	 * Sets the list of wave directions.
	 * @param theListIn The list of wave directions.
	 */
	void setDirections(vector<double>);

	/**
	 * Sets the spread model.
	 * @param spreadModelIn The name of the spread model.
	 */
	void setSpreadModel(string);

	/**
	 * Retrieve the list of wave directions.
	 * @return The list of wave directions.
	 */
	vector<double> getWaveDirections();
private:
	vector<double> directions; /**< The list of wave directions. */
	string spreadModel; /**< The spread model. */
};
#endif
