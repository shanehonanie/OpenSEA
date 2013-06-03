#ifndef FORCEACIVE_H
#define FORCEACTIVE_H
#include "force.h"
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
using namespace std;

typedef complex<double> complexDouble;

/**
 * This class holds data for an active force.
 */

class ForceActive: public Force
{
public:
	ForceActive(); /**< The default constructor. */
	~ForceActive(); /**< The default destructor, nothing happens here. */

	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Converts string in rectanguluar form to a complex number.
	 * @param expression The string in Rectanguluar form.
	 * @return a complex number.
	 */
	complexDouble convertRectangularFormToComplexNumber(string);

	/**
	 * Converts string in polar form to a complex number.
	 * @param expression The string in polar form.
	 * @return a complex number.
	 */
	complexDouble convertPolarFormToComplexNumber(string);

	/**
	 * Set the coefficients.
	 * @param theListIn The list of coefficients.
	 * @param isDirectList Specifies whether list of coefficients is direct list or sequential list.
	 */
	void setCoeff(vector<string>, bool); 

	/**
	 * Retrieve the list of coefficients.
	 * @return The list of coefficients.
	 */
	vector<complexDouble> getCoefficients();
protected:
	complexDouble coefficients[MAX_COEFFICIENTS]; /**< The list of force coeffients. */
};
#endif
