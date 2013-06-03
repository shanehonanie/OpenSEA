#ifndef MOTIONMODEL_H
#define MOTIONMODEL_H
#include <complex>
#include "armadillo"
#include "userforces.h"
#include "body.h"
#include "bodywithforcematrix.h"
#include "equationofmotion_01.h"

using namespace arma;
using namespace std;

const string EQUATION_01 = "6dof"; //Equation Of Motion 01
const int EQUATION_01_SIZE = 6;

/**
 * This class holds data for the motion model and calculates the specified equation of motion.
 */

class MotionModel
{
public:
	MotionModel(); /**< The default constructor. */
	~MotionModel(); /**< The default destructor, nothing happens here. */

	/**
	 * Retrieve and calculate the equation of motion body with force matrix object.
	 * @param bodyDataIn The body.
	 * @param userForcesIn The User Forces.
	 * @return The Body with Force Matrix after specified equation of motion is calculated.
	 */
	BodyWithForceMatrix setBodyData(Body, UserForces);

	/**
	 * Set the wave frequencies list.
	 * @param newWaveFreq The list of wave frequencies.
	 */
	void setWaveFrequencies(double); 

	/**
	 * Get the matrix size which depends on which equation of motion is used.
	 * @param motionType The motion model.
	 */
	static int getMatrixSize(string);
	double curWaveFreq;	/**< The current wave frequency. */
};
#endif
