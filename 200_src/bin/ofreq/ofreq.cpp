/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
\*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*\
 *Revision History
 *---------------------------------------------------------------------------------------------------------------------
 *Date              Author				Description
 *---------------------------------------------------------------------------------------------------------------------
 *May 15, 2013      Shane Honanie       Initially created.
 *Aug 03, 2013      Nicholas Barczak    Added comments and changed behavior of motion solver.
 *                                      Motion model now called in the main ofreq function.  Output passed to the
 *                                      motion solver.
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

//######################################### Include Statements ########################################################
#include <QCoreApplication>
#include "./file_reader/controlinput.h"
#include "./file_reader/seaenvinput.h"
#include "./file_reader/datainput.h"
#include "./file_reader/bodiesinput.h"
#include "./file_reader/forcesinput.h"
#include "./motion_solver/motionsolver.h"
#include "./motion_model/motionmodel.h"
#include "./motion_solver/matbody.h"
#include "./motion_solver/matactiveforce.h"
#include "./motion_solver/matcrossforce.h"
#include "./motion_solver/matreactforce.h"
#include "./derived_outputs/outputslist.h"
#include "./file_writer/filewriter.h"
#include "./derived_outputs/outputsbody.h"
#include "./global_objects/listsolution.h"
#include "./global_objects/solution.h"
#include <string>
#include <iostream>
#include <fstream>

//########################################## Global Variables #########################################################
//Create bodies
vector<Body> listBody;

//Create matrix bodies.
vector<matBody> listMatBody;

//Vector containing various motion models available
vector<motionModel> listModel;

//List of solutions from the motion model.  Each solution object is the list of solutions for one body.
vector<listSolution> listSolutions;

//######################################### Function Prototypes #######################################################
/**
 * @brief Builds a matrix body object for the body specified by the integer.
 *
 * Builds a matrix body object for the body specified by the integer.  Uses the motion model identified by the body
 * object.
 * @param bod Which body to use for building the matix body.
 * @return Returns a matBody object, fully provisioned with all necessary data.
 */
void buildMatBody(int bod, bool useCoeff=true);


//############################################ Class Prototypes #######################################################



//########################################### Main Function ###########################################################
/**
 * @brief The main function that runs ofreq program.
 *
 * The main function that runs ofreq program.  It proceeds through in several stages.  This briefly outlines them.
 * 0.  Initialize a few variables.
 * 1.  Read in input files.
 * 2.  Interpret / parse input files and use them to build the program objects.
 * 3.  Use the motion model to convert input objects into matrix force objects.  The particular motion model used
 *     changes with each Body object.
 * 4.  Setup the motion solver.  Feed all the data in.
 * 5.  Set the operating frequency and use the motion solver to solve equations of motion.
 * 6.  Store results in Solution object.
 * 7.  Repeat steps 4 through 6 for each wave direction and wave frequency.
 * 8.  Use the results to calculate derived outputs.
 * 9.  Write the calculated outputs to output files.
 */
using namespace std;

const string CONST_DIR = "constant";
const string SYS_DIR = "system";
string seperator = "/";
string oFreq_Directory = "";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string mypath;
    string filename;

	//if command line arg supplied, use that directory
	//or assume the current working directory
	if(argc == 2)
		oFreq_Directory = argv[1];

    //Set mypath for main inputs
    mypath = oFreq_Directory + CONST_DIR + seperator;

    //Set filename
    filename = mypath + "forces.in";
    ifstream forces_fileInput(filename.c_str());
    filename = mypath + "bodies.in";
    ifstream bodies_fileInput(filename.c_str());
    filename = mypath + "data.in";
    ifstream data_fileInput(filename.c_str());
    filename = mypath + "seaenv.in";
    ifstream seaenv_fileInput(filename.c_str());

    //Set mypath for system inputs
    mypath = oFreq_Directory + SYS_DIR + seperator;
    filename = mypath + "control.in";
    ifstream control_fileInput(filename.c_str());
	
    //Open input files
    //---------------------------------------------------------------------------
    if (!data_fileInput)
	{
		cerr << "data.in file does not exist." << endl;
		return 1;
	}

	if(!forces_fileInput)
	{
		cerr << "forces.in file does not exist." << endl;
		return 1;
	}

	if(!bodies_fileInput)
	{
		cerr << "bodies.in file does not exist." << endl;
		return 1;
	}

	if(!seaenv_fileInput)
	{
		cerr << "seaenv.in file does not exist." << endl;
		return 1;
	}

	if(!control_fileInput)
	{
		cerr << "control.in file does not exist." << endl;
		return 1;
	}

    //Read input files and interpret data.
    //---------------------------------------------------------------------------
	ControlInput controlInput;
	controlInput.setData(control_fileInput);
	//controlInput.testPrint();

	SeaenvInput seaInput;
	seaInput.setData(seaenv_fileInput);
	//seaInput.testPrint();

	DataInput dataInput;
	dataInput.setData(data_fileInput);
	//dataInput.testPrint();

	ForcesInput forcesInput;
	forcesInput.setData(forces_fileInput);
	//forcesInput.testPrint();

	Bodiesinput bodiesInput;
	bodiesInput.setData(bodies_fileInput);
	//bodiesInput.testPrint();

    //Setup basic outputs
    //---------------------------------------------------------------------------
	vector<double> waveDirectionList = controlInput.getWaveDirections();
	vector<double> waveFrequencyList = controlInput.getWaveFrequencies();
	
    //Setup filewriter for outputs
    //---------------------------------------------------------------------------
	FileWriter theFileWriter(oFreq_Directory, waveDirectionList, waveFrequencyList);
	//vector<OutputsList> theWaveOutputList; //FIX, change name

    //Start creating main objects
    //---------------------------------------------------------------------------
    //Resize matrix bodies vector.
    listMatBody.resize(listBody.size());
    //Resize the solution object.
    for (int i = 0; i < listBody.size(); i++)
        listSolutions.push_back(listSolution(waveDirectionList.size(), waveFrequencyList.size()));

    //Iterate through each wave direction and wave frequency to solve
    //---------------------------------------------------------------------------
    for(unsigned int i = 0; i < waveDirectionList.size(); i++)
	{
        for(unsigned int j = 0; j < waveFrequencyList.size(); j++)
		{
            //Build the matrix bodies
            //---------------------------------------------------------------------------
            //Build operation stuck inside the wave iteration loop because the forces may change with
            //wave direction.  Also inside the wave frequency loop because the forces may change
            //with wave frequency.
            bool coeffonly = true;              //Boolean to tell the motion model to only use coefficients.
            //Iterate through each body and build.
            for (unsigned int i = 0; i < listBody.size(); i++)
            {
                //Build the body.
                //Will automatically use the correct bodies.
                buildMatBody(i, coeffonly);
            }

            //Create motion solver and feed in the body data.
            MotionSolver theMotionSolver(listMatBody);
            //Set the current wave frequency
            theMotionSolver.setWaveFreq(waveFrequencyList[j]);
            //Solve the system of equations.
            theMotionSolver.CalculateOutputs();

			//asign each solution per frequency to a body
            for(unsigned int k = 0; k < listBody.size(); k++)
			{
                Solution soln(listBody[k]);
                soln.setSolution(theMotionSolver.getSolution(k));
                listSolutions[k].setSolution(i, j, soln);
			}
		}

        //Write outputs
        OutputsList theOutputsList(listBody,waveDirectionList, waveFrequencyList);
		theOutputsList.calculateOutputs();

		theFileWriter.setOutputs(theOutputsList);

		if(!theFileWriter.writeToFile(i))
		{
			cerr << "Failed to write outputs to file" << endl;
		}
	}

    return a.exec();
}

//####################################### buildMatBody Function #######################################################
void buildMatBody(int bod, bool useCoeff)
{
    //First assign the basic properties for the matbody.
    listMatBody[bod].setId(bod);
    int modelnum;       //Tracks which model to use

    //Search through the set of motion models to find the matching name.
    for (unsigned int i = 0; i < listModel.size(); i++)
    {
        if (listModel[i].getName() == listBody[bod].getMotionModel())
        {
            listMatBody[bod].setModelId(i);
            modelnum = i;
            break;
        }
    }

    //Now know the correct motion model to use.
    //Create initial setup.
    listModel[modelnum].setListBodies(listBody);        //Feed the list of bodies
    listModel[modelnum].setBody(bod);                   //Set which body to use as the current body
    listModel[modelnum].calcCoefficient(useCoeff);      //Let it know to only calculate coefficients.
    listModel[modelnum].Reset();                        //Give it a reset just for good measure.

    //Iterate through all the active forces, user
    //------------------------------------------
    for (unsigned int i = 0; i < listBody[bod].listForceActive_user().size(); i++)
    {
        listMatBody[bod].listActiveForce_user().push_back(matActiveForce());
        listMatBody[bod].listActiveForce_user()[i].Coefficients() = listModel[modelnum].getMatForceActive_user(i);
        //Create force ID.
        listMatBody[bod].listActiveForce_user()[i].setId(i);
    }

    //Iterate through all the active forces, hydro
    //------------------------------------------
    for(unsigned int i = 0; i < listBody[bod].listForceActive_hydro().size(); i++)
    {
        listMatBody[bod].listActiveForce_hydro().push_back(matActiveForce());
        listMatBody[bod].listActiveForce_hydro()[i].Coefficients() = listModel[modelnum].getMatForceActive_hydro(i);
        //Create force ID.
        listMatBody[bod].listActiveForce_hydro()[i].setId(i);
    }

    //Use this pointer for referencing the forces
    matReactForce* ptForce;
    forceReact* ptReact;

    //Iterate through all the reactive forces, user
    //------------------------------------------
    for (unsigned int i = 0; i < listBody[bod].listForceReact_user().size(); i++)
    {
        listMatBody[bod].listReactForce_user().push_back(matReactForce());
        //Create pointer
        ptForce = &listMatBody[bod].listReactForce_user()[i];

        //Assign id for force.
        ptForce->setId(i);

        ptReact = listBody[bod].listForceReact_user()[i];

        //Iterate through each derivative.
        for (int j = 0; j <= ptReact->getMaxOrd(); j++)
        {
            //Assign matrices
            ptForce->Derivatives().push_back(listModel[modelnum].getMatForceReact_user(i,j));
        }
    }

    //Iterate through all the reactive forces, hydro
    //------------------------------------------
    for (unsigned int i = 0; i < listBody[bod].listForceReact_hydro().size(); i++)
    {
        listMatBody[bod].listReactForce_hydro().push_back(matReactForce());
        //Create pointer
        ptForce = & listMatBody[bod].listReactForce_hydro()[i];

        //Assign id for force.
        ptForce->setId(i);

        ptReact = listBody[bod].listForceReact_user()[i];

        //Iterate through each derivative.
        for (int j = 0; j <= ptReact->getMaxOrd(); j++)
        {
            //Assign matrices
            ptForce->Derivatives().push_back(listModel[modelnum].getMatForceReact_hydro(i,j));
        }
    }

    delete ptForce;
    delete ptReact;
    matCrossForce* ptForce2;
    forceCross* ptCross;

    //Iterate through all the cross body forces, user
    //------------------------------------------
    for (unsigned int i = 0; i < listBody[bod].listForceCross_user().size(); i++)
    {
        listMatBody[bod].listCrossForce_user().push_back(matCrossForce());
        //Create pointer
        ptForce2 = &listMatBody[bod].listCrossForce_user()[i];

        //Assign id for force.
        ptForce2->setId(i);

        //Assign cross body
        for (unsigned int k = 0; k < listBody.size(); k++)
        {
            if (&listBody[k] == listBody[k].listCrossBody_user()[bod])
            {
                //Assign cross body
                ptForce2->setLinkedBody(listMatBody[k]);
                //Linked ID is automatically set.
                break;
            }
        }

        //Assign pointer
        ptCross = listBody[bod].listForceCross_user()[i];

        //Iterate through each derivative.
        for (int j = 0; j <= ptCross->getMaxOrd(); j++)
        {
            //Assign matrices
            ptForce2->Derivatives().push_back(listModel[modelnum].getMatForceCross_user(i,j));
        }
    }

    //Iterate through all the cross body forces, hydro
    //------------------------------------------
    for (unsigned int i = 0; i < listBody[bod].listForceCross_hydro().size(); i++)
    {
        listMatBody[bod].listCrossForce_hydro().push_back(matCrossForce());
        //Create pointer
        ptForce2 = &listMatBody[bod].listCrossForce_hydro()[i];

        //Assign id for force.
        ptForce2->setId(i);

        //Assign cross body
        for (unsigned int k = 0; k < listBody.size(); k++)
        {
            if (&listBody[k] == listBody[k].listCrossBody_hydro()[bod])
            {
                //Assign cross body
                ptForce2->setLinkedBody(listMatBody[k]);
                //Linked Id is automatically set
                break;
            }
        }

        //Assign pointer
        ptCross = listBody[bod].listForceCross_user()[i];

        //Iterate through each derivative.
        for (int j = 0; j <= ptCross->getMaxOrd(); j++)
        {
            //Assign matrices
            ptForce2->Derivatives().push_back(listModel[modelnum].getMatForceCross_hydro(i,j));
        }
    }

    //Get the mass matrix
    //------------------------------------------
    listMatBody[bod].Mass() = listModel[modelnum].getMatForceMass();
}
