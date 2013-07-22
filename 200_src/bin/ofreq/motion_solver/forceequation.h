#ifndef FORCEEQUATION_H
#define FORCEEQUATION_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_COEFFICIENTS = 6;

/**
 * This class holds data for an equation.
 */

class Equation
{
public:
	Equation(); /**< This default constructor. */
	~Equation(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */
	double coefficients[MAX_COEFFICIENTS]; /**< The list of coeffieints. */

	/**
	 * Retrieve the size of the coefficient list.
	 * @return The size of the coefficient list.
	 */
	int getCoefficientListSize();
private:
	void initCoeff(); /**< Initialize all coefficients to default values. */
};
#endif