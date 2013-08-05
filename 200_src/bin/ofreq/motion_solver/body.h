/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date          Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15 2013   Shane Honanie       Initially created
 *Aug 01 2013   Nicholas Barczak    Added comments to header file.
 *Aug 03 2013   Nicholas Barczak    Reactored file for shorter property names and put a few public variables as
 *                                  private.
 *
\*-------------------------------------------------------------------------------------------------------------------*/

//License
/*-------------------------------------------------------------------------------------------------------------------*\
 *Copyright Datawave Marine Solutions, 2013.
 *This file is part of OpenSEA.

 *OpenSEA is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *OpenSEA is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with OpenSEA.  If not, see <http://www.gnu.org/licenses/>.
\*-------------------------------------------------------------------------------------------------------------------*/



//######################################### Class Separator ###########################################################
/**
 * This class holds all of the data for the Body Input File.
 */

#ifndef BODY_H
#define BODY_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <QtGlobal>
#ifdef Q_OS_WIN
    #include "armadillo.h"  //References the armadillo library in lib folder.
#elif defined Q_OS_LINUX
    #include <armadillo>    //Armadillo library included with standard system libraries.
#endif

using namespace std;
using namespace arma;

//######################################### Class Separator ###########################################################
/*Create forward declarations of the force objects to include them in this class definition without including the
 *files.
 */
class forceActive;
class forceReact;
class forceCross;

//######################################### Class Separator ###########################################################
class Body
{
//==========================================Section Separator =========================================================
public:
    //------------------------------------------Function Separator ----------------------------------------------------
	Body(); /**< The default constructor */

    //------------------------------------------Function Separator ----------------------------------------------------
	~Body(); /**< The default destructor, nothing happens here. */

    //------------------------------------------Function Separator ----------------------------------------------------
	void testPrint(); /**< Test print to console the values of all data members. */

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the bodyName.
	 * @param newName The string passed in sets bodyName.
	 */
	void setBodyName(string);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Exposes the body name property for operation.
     * @return Pointer to the body name property.
     */
    string &BodyName();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Exposes the hydro body name property for operation.
     * @return Pointer to the hydro body name property.
     */
    string &HydroBodyName();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the hydroBody.
	 * @param newName The string passed in sets the hydroBody.
	 */
	void setHydroBodyName(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the heading.
	 * @param newHeading The double passed in sets the heading.
	 */
	void setHeading(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Exposes the heading property for operations.
     * @return Pointer to the heading property.
     */
    double &Heading();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the motion model.
	 * @param newMotionModel The string passeed in sets the motionModel.
	 */
	void setMotionModel(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the user active forces.
	 * @param newForceList The vector of strings sets userActiveForces.
	 */
	void setUserActiveForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the user reactive forces.
	 * @param newForceList The vector of strings sets userReactiveForces.
	 */
	void setUserReactiveForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the user cross body forces.
	 * @param newCrossBodyList The vector of strings sets userCrossBodyForces.
	 */
	void setUserCrossBodyForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the hydro active forces.
	 * @param newForceList The vector of strings sets hydroActiveForces.
	 */
	void setHydroActiveForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the hydro reactive forces.
	 * @param newForceList The vector of strings sets hydroReactiveForce.
	 */
	void setHydroReactiveForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the hydro active forces.
	 * @param newForceList The vector of strings sets hydroCrossBodyForces.
	 */
	void setHydroCrossBodyForces(vector<string>);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Adds a linked body.
	 * @param newLinkedBody The string passed in is added to the linkedBody vector.
	 */
	void addLinkedBody(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the mass.
	 * @param newMass The double passed in sets the mass.
	 */
	void setMass(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the mass of the body.
     * @return Returns the mass of the body.  Output is in units of kilograms.
     */
    double getMass();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Moment of Inertia XX (Ixx)
	 * @param newXX The double passed in sets momentOfInertiaXX.
	 */
    void setMomIxx(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the mass moment of inertia on the XX axis for the body.
     * @return Returns the mass moment of inertia on the XX axis for the body.  Output is in units of kilogram-m^2.
     */
    double getMomIxx();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Moment of Inertia YY (Iyy)
	 * @param newYY The double passed in sets momentOfInertiaYY.
	 */
    void setMomIyy(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the mass moment of inertia on the YY axis for the body.
     * @return Returns the mass moment of inertia on the YY axis for the body.  Output is in units of kilogram-m^2.
     */
    double getMomIyy();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Moment of Inertia ZZ (Izz)
	 * @param newZZ The double passed in sets momentOfInertiaZZ.
	 */
    void setMomIzz(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the mass moment of inertia on the ZZ axis for the body.
     * @return Returns the mass moment of inertia on the ZZ axis for the body.  Output is in units of kilogram-m^2.
     */
    double getMomIzz();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Product of Inertia XY (Ixy)
	 * @param newXY The double passed in sets setCrossMomentXY.
	 */
    void setMomIxy(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the cross product of intertia on the XY axis for the body.
     * @return Returns the cross product of intertia on the XY axis for the body. OUtput is in units of kilogram-m^2.
     */
    double getMomIxy();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Product of Inertia XZ (Ixz)
	 * @param newXZ The double passed in sets setCrossMomentXZ.
	 */
    void setMomIxz(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the cross product of intertia on the XZ axis for the body.
     * @return Returns the cross product of intertia on the XZ axis for the body. OUtput is in units of kilogram-m^2.
     */
    double getMomIxz();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Product of Inertia YZ (Iyz)
	 * @param newYZ The double passed in sets setCrossMomentYZ.
	 */
    void setMomIyz(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the cross product of intertia on the YZ axis for the body.
     * @return Returns the cross product of intertia on the YZ axis for the body. OUtput is in units of kilogram-m^2.
     */
    double getMomIyz();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Centroid X.
	 * @param newCenX The double passed in sets centroidX.
	 */
    void setCenX(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the mass matrix for the body.
     * @return Returns the mass matrix for the body, as a single matrix.
     */
    Mat<double> &getMassMatrix();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Implements the method getMassMatrix(), just under a different name.
     * @return Returns the mass matrix for the body, as a single matrix.
     */
    Mat<double> &MassMatrix();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Set the mass matrix for the body.
     * @param MassMatIn The input mass matrix for the body.  A 6x6 matrix.
     */
    void setMassMatrix(Mat<double> MassMatIn);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the centroid of the body mass, X-axis.
     *
     * Returns the centroid of the body mass, X-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     * @return Returns the centroid of the body mass, X-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     */
    double getCenX();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Centroid Y.
	 * @param newCenY The double passed in sets centroidY.
	 */
    void setCenY(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the centroid of the body mass, Y-axis.
     *
     * Returns the centroid of the body mass, Y-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     * @return Returns the centroid of the body mass, Y-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     */
    double getCenY();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Sets the Centroid Z.
	 * @param newCenZ The double passed in sets centroidZ.
	 */
    void setCenZ(double);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the centroid of the body mass, Z-axis.
     *
     * Returns the centroid of the body mass, Z-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     * @return Returns the centroid of the body mass, Z-axis.  Centroid is relative to body coordinates.  This includes
     * body rotation and translation.
     */
    double getCenZ();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the entire mass centroid matrix.
     * @return Returns the entire mass centroid matrix.  Output is a 3x1 matrix of the body centroid, relative to
     * body coordinate system.
     */
    Mat<double> getCen();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the body position in the X-axis.
     *
     * Sets the body position in the X-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @param input Double input specifying the position on the X-axis, units of meters.
     */
    void setPosnX(double input);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the body position in the X-axis.
     *
     * Gets the body position in the X-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @return Double precision floating number specifying the position on the X-axis, units of meters.
     */
    double getPosnX();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the body position in the Y-axis.
     *
     * Sets the body position in the Y-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @param input Double input specifying the position on the Y-axis, units of meters.
     */
    void setPosnY(double input);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the body position in the Y-axis.
     *
     * Gets the body position in the Y-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @return Double precision floating number specifying the position on the Y-axis, units of meters.
     */
    double getPosnY();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the body position in the Z-axis.
     *
     * Sets the body position in the Z-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @param input Double input specifying the position on the Z-axis, units of meters.
     */
    void setPosnZ(double input);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the body position in the Z-axis.
     *
     * Gets the body position in the Z-axis.  Position is set relative to the world coordinate system.  Units are in
     * meters.
     * @return Double precision floating number specifying the position on the Z-axis, units of meters.
     */
    double getPosnZ();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Returns the entire matrix for position of the body.
     *
     * Returns the entire matrix for the position of the body.  Output is a 3x1 matrix with double point precision.
     * First entry (1,1) = Position in X-axis.  Second entry (2,1) = Position in Y-axis.  Third entry (3,1) = Position
     * in Z-axis.  Units are in meters.  Position is relative to the orientation of the world coordinate system.
     * @return Returns the entire matrix for the position of the body.  Output is a 3x1 matrix with double point precision.
     * First entry (1,1) = Position in X-axis.  Second entry (2,1) = Position in Y-axis.  Third entry (3,1) = Position
     * in Z-axis.  Units are in meters.  Position is relative to the orientation of the world coordinate system.
     */
    Mat<double> getPosn();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Exposes the position property for operation.  The entire matrix for position of the body.
     *
     * Returns the entire matrix for the position of the body.  Output is a 3x1 matrix with double point precision.
     * First entry (1,1) = Position in X-axis.  Second entry (2,1) = Position in Y-axis.  Third entry (3,1) = Position
     * in Z-axis.  Units are in meters.  Position is relative to the orientation of the world coordinate system.
     * @return Returns a pointer to the the entire matrix for the position of the body.
     * Output is a 3x1 matrix with double point precision.
     * First entry (1,1) = Position in X-axis.  Second entry (2,1) = Position in Y-axis.  Third entry (3,1) = Position
     * in Z-axis.  Units are in meters.  Position is relative to the orientation of the world coordinate system.
     */
    Mat<double> &Posn();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Adds a cross body name.
	 * @param newName The string passed in is added to the vector that holds the list of cross body forces.
	 */
	void setCrossBodyName(string);

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Get the name of the Motion Model.
	 * @return The string returned is the motionModel.
	 */
	string getMotionModel();

    //------------------------------------------Function Separator ----------------------------------------------------
	/**
	 * Get the name of the body.
	 * @return The name of the body.
	 */    
	string getBodyName();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Set the solution matrix for the body.
     *
     * Sets the solution matrix for the body.  Used to store the solution from the motion solver.  This variable is
     * initially empty on body creation.  It gets filled with the output from the motion solver.  Output is a column
     * matrix (n by 1) of complex numbers.  Output is in units of meters.
     * @param input Column matrix of complex numbers.  Matrix size is not hard coded.  Number of rows in matrix must match
     * number of equations for body property.
     */
    void setSolution(cx_mat input);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Get the solution matrix for the body.
     *
     * Gets the solution matrix for the body.  Used to store the solution from the motion solver.  This variable is
     * initially empty on body creation.  It gets filled with the output from the motion solver.  Output is a column
     * matrix (n by 1) of complex numbers.  Output is in units of meters.
     * @return Column matrix of complex numbers.  Matrix size is not hard coded.  Number of rows in matrix must match
     * number of equations for body property.
     */
    cx_mat getSolution();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Copies the body object, complete with all current data.
     * @return Returns a copy of the body object, complete with all current data.  Passed by value, not reference.
     */
    Body Copy();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of active user forces.
     *
     * The list of active user forces.  A vector of pointers directing to the active user forces.  Warning that
     * these forces may be linked to other bodies as well and should not be changed.
     * @return A vector of pointers to various user active forces.
     */
    vector<forceActive* > &listForceActive_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of active hydrodynamic forces.
     *
     * The list of active hydrodynamic forces.  A vector of pointers directing to the active hydrodynamic forces.
     * Warning that these forces may be linked to other bodies as well and should not be changed.
     * @return A vector of pointes to various hydrodynamic active forces.
     */
    vector<forceActive* > &listForceActive_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of reactive user forces.
     *
     * The list of reactive user forces.  A vector of pointers directing to the reactive user forces.  Warning that
     * these forces may be linked to other bodies as well and should not be changed.
     * @return A vector of pointers to various user reactive forces.
     */
    vector<forceReact* > &listForceReact_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of reactive hydrodynamic forces.
     *
     * The list of reactive hydrodynamic forces.  A vector of pointers directing to the reactive hydrodynamic
     * forces.  Warning that these forces may be linked to other bodies as well and should not be changed.
     * @return A vector of pointers to various hydrodynamic reactive forces.
     */
    vector<forceReact* > &listForceReact_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of user cross-body forces.
     *
     * The list of user cross-body forces.  A vector of pointers directing to the user cross-body forces.  Warning
     * that these forces may be linked to other bodies as well and should not be changed.  There is another vector:
     * the listLinkedBody_usr.  That determines which body each cross-body force links to.  The indices of the two
     * lists should match.  So that when a force gets added at index 5 in the listForceCross_usr, it should have a
     * matching entry at index 5 in the listLinkedBody_usr.
     * @return A list of pointers to various user cross-body forces.
     */
    vector<forceCross* > &listForceCross_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of hydrodynamic cross-body forces.
     *
     * The list of hydrodynamic cross-body forces.  A vector of pointers directing to the hydrodynamic cross-body
     * forces.  Warning that these forces may be linked to other bodies as well and should not be changed.  There is
     * another vector: the listLinkedBody_usr.  That determines which body each cross-body force links to.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_hydro, it should
     * have a matching entry at index 5 in the listLinkedBody_hydro.
     * @return A list of pointers to various hydrodynamic cross-body forces.
     */
    vector<forceCross* > &listForceCross_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of linked bodies for user cross-body forces.
     *
     * The list of linked bodies for user cross-body forces.  This is a list of pointers to the other bodies. This
     * corresponds with the vector listForceCross_usr.  The indices of the two vectors should match.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_usr, it should
     * have a matching entry at index 5 in the listLinkedBody_usr.
     * @return A list of pointers to various linked bodies for user cross-body forces.
     */
    vector<Body* > &listCrossBody_user();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of linked bodies for hydrodynamic cross-body forces.
     *
     * The list of linked bodies for hydrodynamic cross-body forces.  This is a list of pointers to the other bodies.
     * This corresponds with the vector listForceCross_usr.  The indices of the two vectors should match.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_hydro, it should
     * have a matching entry at index 5 in the listLinkedBody_hydro.
     * @return A list of pointers to various linked bodies for hydro cross-body forces.
     */
    vector<Body* > &listCrossBody_hydro();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Sets the name of the motion model for lookup later.
     *
     * Sets the name of the motion model for lookup later.
     * @param modelName String input that is the name of the motion model.  This must match exactly one of the entries
     * in the list of motion models avaiable at run time.
     */
    void setMotionModel(string modelName);

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the name of the motion model.
     *
     * Gets string output that is the name of the motion model assigned to this body.
     * @return String output that is the name of the motion model assigned to this body.
     */
    string getMotionModel();

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Gets the number of equations used in the body.
     *
     * Gets the number of equations used in the body.
     * @return Integer number representing the number of equations used in the body.
     */
    int getEquationCount();

//==========================================Section Separator =========================================================
protected:

//==========================================Section Separator =========================================================
private:
    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of active user forces.
     *
     * The list of active user forces.  A vector of pointers directing to the active user forces.  Warning that
     * these forces may be linked to other bodies as well and should not be changed.
     */
    vector<forceActive*> plistForceActive_usr;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of active hydrodynamic forces.
     *
     * The list of active hydrodynamic forces.  A vector of pointers directing to the active hydrodynamic forces.
     * Warning that these forces may be linked to other bodies as well and should not be changed.
     */
    vector<forceActive*> plistForceActive_hydro;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of reactive user forces.
     *
     * The list of reactive user forces.  A vector of pointers directing to the reactive user forces.  Warning that
     * these forces may be linked to other bodies as well and should not be changed.
     */
    vector<forceReact*> plistForceReact_usr;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of reactive hydrodynamic forces.
     *
     * The list of reactive hydrodynamic forces.  A vector of pointers directing to the reactive hydrodynamic
     * forces.  Warning that these forces may be linked to other bodies as well and should not be changed.
     */
    vector<forceReact*> plistForceReact_hydro;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of user cross-body forces.
     *
     * The list of user cross-body forces.  A vector of pointers directing to the user cross-body forces.  Warning
     * that these forces may be linked to other bodies as well and should not be changed.  There is another vector:
     * the listLinkedBody_usr.  That determines which body each cross-body force links to.  The indices of the two
     * lists should match.  So that when a force gets added at index 5 in the listForceCross_usr, it should have a
     * matching entry at index 5 in the listLinkedBody_usr.
     */
    vector<forceCross*> plistForceCross_usr;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of hydrodynamic cross-body forces.
     *
     * The list of hydrodynamic cross-body forces.  A vector of pointers directing to the hydrodynamic cross-body
     * forces.  Warning that these forces may be linked to other bodies as well and should not be changed.  There is
     * another vector: the listLinkedBody_usr.  That determines which body each cross-body force links to.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_hydro, it should
     * have a matching entry at index 5 in the listLinkedBody_hydro.
     */
    vector<forceCross*> plistForceCross_hydro;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of linked bodies for user cross-body forces.
     *
     * The list of linked bodies for user cross-body forces.  This is a list of pointers to the other bodies. This
     * corresponds with the vector listForceCross_usr.  The indices of the two vectors should match.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_usr, it should
     * have a matching entry at index 5 in the listLinkedBody_usr.
     */
    vector<Body*> plistLinkedBody_usr;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The list of linked bodies for hydrodynamic cross-body forces.
     *
     * The list of linked bodies for hydrodynamic cross-body forces.  This is a list of pointers to the other bodies.
     * This corresponds with the vector listForceCross_usr.  The indices of the two vectors should match.  The indices
     * of the two lists should match.  So that when a force gets added at index 5 in the listForceCross_hydro, it should
     * have a matching entry at index 5 in the listLinkedBody_hydro.
     */
    vector<Body*> plistLinkedBody_hydro;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Private variable for the mass matrix.
     *
     * Private variable for the mass matrix.  This configuration assumes a standard 6dof motion model.
     * However, this is acceptable because the transition to the motion model object decides which elements
     * to pick out and put into equations.  Mass is units of kilograms.  Moments of inertia are in kg-m^2.
     */
    Mat<double> pmassMat;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The name for this body object.
     *
     * The name for this body object.  An identifier that the user creates.  Also used to locate the body in a list.
     */
    string bodyName;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Private variable for the centroid matrix.
     *
     * Private variable for the centroid matrix.  Used to store the centroid matrix.  This configuration assumes
     * a standard 6dof motion model.  However, this is acceptable because the transition to the motion model object
     * decides which elements to pick out and put into equations.  Centroid is measured in units of meters.
     */
    Mat<double> pCentroid;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Private variable for the solution matrix.
     *
     * Private variable for the solution matrix.  Used to store the solution from the motion solver.  This variable is
     * initially empty on body creation.  It gets filled with the output from the motion solver.  Output is a column
     * matrix (n by 1) of complex numbers.  Output is in units of meters.
     */
    cx_mat pSoln;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Private variable for the position of the body relative to the world coordinate system.
     *
     * Private variable for the position of the body relative to the world coordinate system origin.  The body may
     * be at a position relative to the world coordinate system.  Any coordintes entered for the body are relative to
     * this body position value.  Position is measured in units of meters.
     */
    Mat<double> pPosn;

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief Private variable for the heading of the body relative to the world coordinate system.
     *
     * Private variable for the heading of the body relative to the world coordinate system.  All wave angles are
     * specified in the world coordinate system and then motions are translated relative to the body heading.  Angle
     * is measured in units of radians.
     */
    double phead;

    //------------------------------------------Function Separator ----------------------------------------------------
    string hydroBody; /**< The name of this hydro body object. */

    //------------------------------------------Function Separator ----------------------------------------------------
    /**
     * @brief The number of equations used by the body.  This sets the size of the matrices.
     *
     * The number of equations used by the body.  This sets the size of the matrices.
     */
    int eqnCount;

    //------------------------------------------Function Separator ----------------------------------------------------
    string motModel; /**< The name of the motion model object to use */
};
#endif
