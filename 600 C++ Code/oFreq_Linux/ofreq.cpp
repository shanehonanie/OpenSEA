//#ifdef _WIN32
//#define OS_TYPE "WINDOWS"
//#else
//#define OS_TYPE "LINUX"
//#endif

#include "controlinput.h"
#include "seaenvinput.h"
#include "datainput.h"
#include "bodiesinput.h"
#include "forcesinput.h"
#include "motionsolver.h"
#include "outputslist.h"
#include "filewriter.h"
#include "outputsbody.h"
#include "bodywithsolution.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const string CONST_DIR = "constant";
const string SYS_DIR = "system";
string seperator = "/";
string mypath;
string filename;

int main()
{
    //Set mypath for main inputs
    mypath = CONST_DIR + seperator;
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
    mypath = SYS_DIR + seperator;
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

	//MotionSolver theMotionSolver(bodiesInput.getBodyData(),forcesInput.getUserForces(), controlInput.getWaveFrequencies());
	//vector<Body> bodyListWithSolution = theMotionSolver.CalculateOutputs();

	//OutputsList theOutputsList(bodyListWithSolution,controlInput.getWaveFrequencies());
	//theOutputsList.calculateOutputs();

	//FileWriter theFileWriter(theOutputsList);
	//theFileWriter.writeToFile(0); //FIX< <----This will be a loop wih all wave directions, not just 0

	vector<double> waveDirectionList = controlInput.getWaveDirections();
	vector<double> waveFrequencyList = controlInput.getWaveFrequencies();
	

	FileWriter theFileWriter(waveDirectionList, waveFrequencyList);
	//vector<OutputsList> theWaveOutputList; //FIX, change name

	vector<Body> theBodiesList = bodiesInput.getBodyData();
	vector<BodyWithSolution> bodyListWithSolution;

	//Create BodyWithSolution Object for each Body Object
	for(int i = 0; i < theBodiesList.size(); i++)
	{
		BodyWithSolution newBodySolution(theBodiesList[i].getBodyName());
		bodyListWithSolution.push_back(newBodySolution);
	}

	for(int i = 0; i < waveDirectionList.size(); i++)
	{
		for(int j = 0; j < waveFrequencyList.size(); j++)
		{
			MotionSolver theMotionSolver(theBodiesList,forcesInput.getUserForces(), waveFrequencyList[j]);
			vector<cx_mat> theSolutionsPerFrequency = theMotionSolver.CalculateOutputs();

			//asign each solution per frequency to a body
			for(int k = 0; k < theSolutionsPerFrequency.size(); k++)
			{
				bodyListWithSolution[k].solutionMatrix.push_back(theSolutionsPerFrequency[k]);
			}
		}

		OutputsList theOutputsList(bodyListWithSolution,waveDirectionList, waveFrequencyList);
		theOutputsList.calculateOutputs();

		theFileWriter.setOutputs(theOutputsList);

		if(!theFileWriter.writeToFile(i))
		{
			cerr << "Failed to write outputs to file" << endl;
		}
	}

	return 0;
}
