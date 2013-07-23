#ifndef ACTIVEEFORCEMATRIX_H
#define ACTIVEEFORCEMATRIX_H
#include <complex>
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

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

