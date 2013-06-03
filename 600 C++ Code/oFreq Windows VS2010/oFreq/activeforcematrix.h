#ifndef ACTIVEEFORCEMATRIX_H
#define ACTIVEEFORCEMATRIX_H
#include <complex>
#include "armadillo"

using namespace arma;
using namespace std;

/**
 * This class holds all data for an active force matrix.
 */

class ActiveForceMatrix
{
public:
	ActiveForceMatrix(); /**< The default constructor. */
	~ActiveForceMatrix(); /**< The default destructor, nothing happens here. */
	cx_mat coefficients; /**< Matrix of force coefficients. */
};
#endif

