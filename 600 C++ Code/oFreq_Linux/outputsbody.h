#ifndef OUTPUTSBODY_H
#define OUTPUTSBODY_H
#include <vector>
#include "armadillo"
#include "bodywithsolution.h"
#include "globalacceleration.h"
#include "globalmotion.h"
#include "globalvelocity.h"

using namespace std;
using namespace arma;

const int GLOBAL_MOTION = 0; /**< Used for referencing Global Motion*/
const int GLOBAL_VELOCITY = 1; /**< Used for referencing Global Velocity*/
const int GLOBAL_ACCELERATION = 2; /**< Used for referencing Global Acceleraion*/
const int GLOBAL_SIZE = 3; /**< The number of Global Solution Types to be included in calculations*/

/**
 * This class holds the global solutions for all frequncies for a single body object.
 */

class OutputsBody
{
public:

	/**
	 * Constructor Creates a new OutputsBodyObject and sets the BodyWithSolution and waveFrequencies.
	 * @param bodyIn Sets BodyWithSolutionObject.
	 * @param Sets the List of wave frequencies.
	 */
	OutputsBody(BodyWithSolution, vector<double>);
	~OutputsBody(); /**< The default destructor, nothing happens here. */

	BodyWithSolution theBody; /**< Holds object that has body name and solutions. */
	vector<double> frequencies; /**< The list of wave frequencies to be used. */

	/**
	 * Retrieve a matrix of only one type of Global Solution.
	 * @param classype This specifies the index used to retrieve one of the Global Solutions.
	 * @return Matrix of one type Global Solutions, each index represents different frquency.
	 */
	vector<cx_mat> getOutputType(int);

	/**
	 * Retrieve a matrix of all types of Global Solution types.
	 * @return Matrix that has all Global solution types, each column is seperate class type, each index seperate frequency.
	 */
	vector<cx_mat> getOutputList();

	void calculateOutputs(); /**< Calculate SOlutions for eahc class type and frequency */

private:
	vector<cx_mat> outputList; /**< Each index is a cx_mat, each column matrix is a different global type, 0- Mot, 1 - acc, 2 - vel */
};
#endif
