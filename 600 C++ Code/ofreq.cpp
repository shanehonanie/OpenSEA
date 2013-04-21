#include "controlinput.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	/*ifstream data_fileInput("data.in");
	ifstream forces_fileInput("forces.in");
	ifstream bodies_fileInput("bodies.in");
	ifstream seaenv_fileInput("seaenv.in");*/
	ifstream control_fileInput("control.in");

	

	//if (!data_fileInput)
	//{
	//	cerr << "data.in file does not exist." << endl;
	//	return 1;
	//}
	//else if(!forces_fileInput)
	//{
	//	cerr << "forces.in file does not exist." << endl;
	//	return 1;
	//}
	//else if(!bodies_fileInput)
	//{
	//	cerr << "bodies.in file does not exist." << endl;
	//	return 1;
	//}
	//else if(!seaenv_fileInput)
	//{
	//	cerr << "seaenv.in file does not exist." << endl;
	//	return 1;
	//}
	if(!control_fileInput)
	{
		cerr << "control.in file does not exist." << endl;
		return 1;
	}

	ControlInput controlInput;
	controlInput.setData(control_fileInput);
	controlInput.testPrint();
	return 0;
}
