#ifndef BODYWITHSOLUTION_H
#define BODYWITHSOLUTION_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

/**
* This class holds data to identify a body by name and its solutions.
*/

class BodyWithSolution
{
public:
	/**
	 * This constructor creates a BodyWithSolution object and sets its name to the body it holds data for.
	 * @param nameIn The string passed in sets the bodyName of this object.
	 */
	BodyWithSolution(string);

	/**
	 * The destructor.
	 * Nothing happens here.
	 */
	~BodyWithSolution();

	string bodyName; /**< The name of the body this object represents. */
	vector<cx_mat> solutionMatrix; /**< Each entry in this vector holds a matrix of complex<double> which represents a solution for each frequency */
};
#endif
