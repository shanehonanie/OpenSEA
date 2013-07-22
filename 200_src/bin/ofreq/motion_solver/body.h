#ifndef BODY_H
#define BODY_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <QtGlobal>
#ifdef(Q_OS_WIN)
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

using namespace std;
using namespace arma;

/**
 * This class holds all of the data for the Body Input File.
 */

class Body
{
public:

	Body(); /**< The default constructor */
	~Body(); /**< The default destructor, nothing happens here. */
	void testPrint(); /**< Test print to console the values of all data members. */

	/**
	 * Sets the bodyName.
	 * @param newName The string passed in sets bodyName.
	 */
	void setBodyName(string);

	/**
	 * Sets the hydroBody.
	 * @param newName The string passed in sets the hydroBody.
	 */
	void setHydroBodyName(string);

	/**
	 * Sets the heading.
	 * @param newHeading The double passed in sets the heading.
	 */
	void setHeading(double);

	/**
	 * Sets the motion model.
	 * @param newMotionModel The string passeed in sets the motionModel.
	 */
	void setMotionModel(string);

	/**
	 * Sets the user active forces.
	 * @param newForceList The vector of strings sets userActiveForces.
	 */
	void setUserActiveForces(vector<string>);

	/**
	 * Sets the user reactive forces.
	 * @param newForceList The vector of strings sets userReactiveForces.
	 */
	void setUserReactiveForces(vector<string>);

	/**
	 * Sets the user cross body forces.
	 * @param newCrossBodyList The vector of strings sets userCrossBodyForces.
	 */
	void setUserCrossBodyForces(vector<string>);

	/**
	 * Sets the hydro active forces.
	 * @param newForceList The vector of strings sets hydroActiveForces.
	 */
	void setHydroActiveForces(vector<string>);

	/**
	 * Sets the hydro reactive forces.
	 * @param newForceList The vector of strings sets hydroReactiveForce.
	 */
	void setHydroReactiveForces(vector<string>);

	/**
	 * Sets the hydro active forces.
	 * @param newForceList The vector of strings sets hydroCrossBodyForces.
	 */
	void setHydroCrossBodyForces(vector<string>);

	/**
	 * Adds a linked body.
	 * @param newLinkedBody The string passed in is added to the linkedBody vector.
	 */
	void addLinkedBody(string);

	/**
	 * Sets the mass.
	 * @param newMass The double passed in sets the mass.
	 */
	void setMass(double);

	/**
	 * Sets the Moment of Inertia XX (Ixx)
	 * @param newXX The double passed in sets momentOfInertiaXX.
	 */
	void setMomentXX(double);

	/**
	 * Sets the Moment of Inertia YY (Iyy)
	 * @param newYY The double passed in sets momentOfInertiaYY.
	 */
	void setMomentYY(double);

	/**
	 * Sets the Moment of Inertia ZZ (Izz)
	 * @param newZZ The double passed in sets momentOfInertiaZZ.
	 */
	void setMomentZZ(double);

	/**
	 * Sets the Product of Inertia XY (Ixy)
	 * @param newXY The double passed in sets setCrossMomentXY.
	 */
	void setCrossMomentXY(double);

	/**
	 * Sets the Product of Inertia XZ (Ixz)
	 * @param newXZ The double passed in sets setCrossMomentXZ.
	 */
	void setCrossMomentXZ(double);

	/**
	 * Sets the Product of Inertia YZ (Iyz)
	 * @param newYZ The double passed in sets setCrossMomentYZ.
	 */
	void setCrossMomentYZ(double);

	/**
	 * Sets the Centroid X.
	 * @param newCenX The double passed in sets centroidX.
	 */
	void setCentroidX(double);

	/**
	 * Sets the Centroid Y.
	 * @param newCenY The double passed in sets centroidY.
	 */
	void setCentroidY(double);

	/**
	 * Sets the Centroid Z.
	 * @param newCenZ The double passed in sets centroidZ.
	 */
	void setCentroidZ(double);

	/**
	 * Adds a cross body name.
	 * @param newName The string passed in is added to the vector that holds the list of cross body forces.
	 */
	void setCrossBodyName(string);

	/**
	 * Get the name of the Motion Model.
	 * @return The string returned is the motionModel.
	 */
	string getMotionModel();

	/**
	 * Get the name of the body.
	 * @return The name of the body.
	 */
	string getBodyName();

	//TO DO : Write get methods for these data members, should be private*****************************
	vector<string> userActiveForces; /**< Holds the user active forces. */
	vector<string> userReactiveForces; /**< Holds the user reactive forces. */
	vector<string> userCrossBodyForces; /**< Holds the user cross body forces. */
	vector<string> hydroActiveForces; /**< Holds the hydro active forces. */
	vector<string> hydroReactiveForces; /**< Holds the hydro reactive forces. */
	vector<string> hydroCrossBodyForces; /**< Holds the hydro cross body forces. */
	vector<string> linkedBody; /**< Holds a list of the linked bodies. */
	string bodyName; /**< The name of this body object. */
	string hydroBody; /**< The name of this hydro body object. */
	string motionModel; /**< The name of the motion model used for this body. */
	double mass; /**< The mass. */
	double momentOfInertiaXX; /**< Moment of Inertia XX (Ixx). */
	double momentOfInertiaYY; /**< Moment of Inertia YY (Iyy). */
	double momentOfInertiaZZ; /**< Moment of Inertia ZZ (Izz). */
	double crossMomentOfInertiaXY; /**< Product of Inertia XY (Ixy). */
	double crossMomentOfInertiaXZ; /**< Product of Inertia XZ (Ixz). */
	double crossMomentOfInertiaYZ; /**< Product of Inertia YZ (Iyz). */
	double centroidX; /**< Centroid X. */
	double centroidY; /**< Centroid Y. */
	double centroidZ; /**< Centroid Z. */
	double heading; /**< Heading. */
};
#endif
