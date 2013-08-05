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
#include "./motion_solver/matbody.h"
#include "./derived_outputs/outputslist.h"
#include "./file_writer/filewriter.h"
#include "./derived_outputs/outputsbody.h"
#include <string>
#include <iostream>
#include <fstream>

//############################################# Separator #############################################################
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

	vector<double> waveDirectionList = controlInput.getWaveDirections();
	vector<double> waveFrequencyList = controlInput.getWaveFrequencies();
	

	FileWriter theFileWriter(oFreq_Directory, waveDirectionList, waveFrequencyList);
	//vector<OutputsList> theWaveOutputList; //FIX, change name

	vector<Body> theBodiesList = bodiesInput.getBodyData();
	vector<BodyWithSolution> bodyListWithSolution;

    //Create matrix bodies.
    vector<matBody> listMatBody;

    for(unsigned int i = 0; i < waveDirectionList.size(); i++)
	{
        for(unsigned int j = 0; j < waveFrequencyList.size(); j++)
		{
            //Create motion solver and feed in the body data.
            MotionSolver theMotionSolver(listMatBody);
            //Set the current wave frequency
            theMotionSolver.setWaveFreq(waveFrequencyList[j]);
            //Solve the system of equations.
			vector<cx_mat> theSolutionsPerFrequency = theMotionSolver.CalculateOutputs();

			//asign each solution per frequency to a body
            for(unsigned int k = 0; k < theSolutionsPerFrequency.size(); k++)
			{
                theBodiesList[k].setSolution(theSolutionsPerFrequency[k]);
			}
		}

        OutputsList theOutputsList(theBodiesList,waveDirectionList, waveFrequencyList);
		theOutputsList.calculateOutputs();

		theFileWriter.setOutputs(theOutputsList);

		if(!theFileWriter.writeToFile(i))
		{
			cerr << "Failed to write outputs to file" << endl;
		}
	}

    return a.exec();
}
