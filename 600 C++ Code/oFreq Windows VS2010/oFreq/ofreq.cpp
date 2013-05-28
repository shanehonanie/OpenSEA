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
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const string CONST_DIR = "constant";
const string SYS_DIR = "system";
string seperator = "/";

int main()
{
	ifstream forces_fileInput(CONST_DIR + seperator + "forces.in");
	ifstream bodies_fileInput(CONST_DIR + seperator + "bodies.in");
	ifstream data_fileInput(CONST_DIR + seperator + "data.in");
	ifstream seaenv_fileInput(CONST_DIR + seperator + "seaenv.in");
	ifstream control_fileInput(SYS_DIR + seperator + "control.in");

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

	MotionSolver theMotionSolver(bodiesInput.getBodyData(),forcesInput.getUserForces(), controlInput.getWaveFrequencies());
	vector<Body> bodyListWithSolution = theMotionSolver.CalculateOutputs();

	OutputsList theOutputsList(bodyListWithSolution,controlInput.getWaveFrequencies(), controlInput.getWaveDirections());
	theOutputsList.calculateOutputs();

	FileWriter theFileWriter(theOutputsList);
	theFileWriter.writeToFile(0); //FIX< <----This will be a loop wih all wave directions, not just 0

	return 0;
}
