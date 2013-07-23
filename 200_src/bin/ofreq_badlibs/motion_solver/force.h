#ifndef FORCE_H
#define FORCE_H
#include "../file_reader/readinputfile.h"
#include "forceequation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * This (base) class holds data for a force object.
 */

class Force
{
public:
	Force(); /**< The default constructor. */
	~Force(); /**< The default destructor, nothing happens here. */

	/**
	 * Sets the name of the force.
	 * @param newName The name of the force.
	 */
	void setForceName(string);

	/**
	 * Retrieve the name of the force.
	 * @return newName The name of the force.
	 */
	string getForceName();
protected:
	string forceName; /**< The force name. */
private:
	
};
#endif
