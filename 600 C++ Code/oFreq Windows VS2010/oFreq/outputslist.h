#ifndef OUTPUTSLIST_H
#define OUTPUTSLIST_H
#include <vector>
#include "bodywithsolution.h"
#include "outputsbody.h"
using namespace std;

/**
 * This class holds the global solutions for all frequncies for all body object(s).
 */

class OutputsList
{
public:
	OutputsList(); /**< This default constructor creates a OutputsList object. */

	/**
	 * Overloaded constructor
	 * @param theBodyListIn All bodies with calculated solutions.
	 * @param directionIn List of all wave directions.
	 * @param frequenciesIn List of all frequencies.
	 */
	OutputsList(vector<BodyWithSolution>, vector<double>, vector<double>);
	~OutputsList(); /**< The default destructor, nothing happens here. */

	vector<OutputsBody> theOutputsBodyList; /**< List of each body with computed globlal matrices */
	vector<BodyWithSolution> theBodyList; /**< List of all bodies with soluions computed by motion solver */
	vector<double> theFrequencyList; /**< List of frequencies used. */
	vector<double> theDirectionList; /**< List of directions used. */
	void calculateOutputs(); /**< Calculate the Global Solutions for each body */
};
#endif
