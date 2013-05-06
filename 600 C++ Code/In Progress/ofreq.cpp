#include "controlinput.h"
#include "seaenvinput.h"
#include "datainput.h"
#include "bodiesinput.h"
#include "forcesinput.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream forces_fileInput("forces.in");
	ifstream bodies_fileInput("bodies.in");
	ifstream data_fileInput("data.in");
	ifstream seaenv_fileInput("seaenv.in");
	ifstream control_fileInput("control.in");

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

	Bodiesinput bodiesInput(forcesInput.getUserForces());
	bodiesInput.setData(bodies_fileInput);
	//bodiesInput.testPrint();
	bodiesInput.createNewBodyForceMatrix();

	return 0;
}
