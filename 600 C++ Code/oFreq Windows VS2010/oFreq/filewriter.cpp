#include "filewriter.h"


FileWriter::FileWriter(OutputsList outputListIn) 
	: theOutputsList(outputListIn), theWaveDirectionsList(outputListIn.theDirectionList), thefrequenciesList(outputListIn.theFrequencyList)
{
	setHeader();	
	writeDirectionsToFile(thefrequenciesList);
	writeFrequenciesToFile(thefrequenciesList);
}

void FileWriter::setHeader()
{
	ifstream header_fileInput(HEADER_FILENAME);

	if (!header_fileInput)
	{
		cerr << HEADER_FILENAME + " file does not exist." << endl;
	}
	else
	{
		header.assign((std::istreambuf_iterator<char>(header_fileInput)),
			(std::istreambuf_iterator<char>()));
	}
}

void FileWriter::setFileInfo(string objectIn)
{
	fileInfo = SEAFILE2 + "\n" + OBJECT_BEGIN2 + "\n    " + VERSION + "   " + VERSION_INFO + END + "\n    " + FORMAT + "    " 
		+ FORMAT_INFO + END + "\n    " + OBJECT + "    " + objectIn + END + "\n" + OBJECT_END2 + "\n";
}

FileWriter::~FileWriter()
{
}

int FileWriter::writeToFile(int curWaveDirection)
{
	ofstream myFileMotion;
	ofstream myFileVelocity;
	ofstream myFileAcceleration;
	
	//Convert int to string
	stringstream ss;
	ss << curWaveDirection;
	string dirNum = ss.str();

	string directory = "d" + dirNum;

	myFileMotion.open(directory + GLOBAL_MOTION_FILENAME); //Create the Motion file
	myFileVelocity.open(directory + GLOBAL_VELOCITY_FILENAME); //Create the Velocity file
	myFileAcceleration.open(directory + GLOBAL_ACCELERATION_FILENAME); //Create the Acceleration file

	setFileInfo(GLOBAL_ACCELERATION_OBJECT);
	myFileMotion << header << fileInfo << BREAK_TOP;
	setFileInfo(GLOBAL_VELOCITY_OBJECT);
	myFileVelocity << header << fileInfo << BREAK_TOP;
	setFileInfo(GLOBAL_ACCELERATION_OBJECT);
	myFileAcceleration << header << fileInfo << BREAK_TOP;

	for(int j = 0; j < theOutputsList.theBodyList.size(); j++) //iterate through all of the bodies
	{
		vector<cx_mat> globalMotSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(0);
		vector<cx_mat> globalVelSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(1);
		vector<cx_mat> globalAccSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(2);

		myFileMotion << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << theOutputsList.theBodyList[j].bodyName << END << "\n";

		myFileVelocity << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << theOutputsList.theBodyList[j].bodyName << END << "\n";

		myFileAcceleration << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << theOutputsList.theBodyList[j].bodyName << END << "\n";
			
		for(int k = 0; k < thefrequenciesList.size(); k++) //iterate through all of the frequencies
		{
			//Write Global Motion Files *******************************************************************************************
			setFileInfo(GLOBAL_MOTION_OBJECT);
			myFileMotion << "  " << DATA << " " << OBJECT_BEGIN2 << "\n" << "    " << FREQUENCY << " " << (k+1) << "\n    "<< VALUE << " " << LIST_BEGIN2 << "\n";
				
			for(int a = 0; a < 6; a++) //print the 6 outputs per each frequency
			{
				myFileMotion.precision(15);
				myFileMotion <<  "    " << globalMotSolutionList[k].at(a,0).real(); 

				if(globalMotSolutionList[j].at(a,0).imag() < 0.0)
					myFileMotion <<   globalMotSolutionList[j].at(a,0).imag()<< "i\n";
				else
					myFileMotion <<  "+" << globalMotSolutionList[j].at(a,0).imag()<< "i\n";
			}
			myFileMotion << "    " << LIST_END2 << "\n  " << OBJECT_END2 << "\n";

			//Write Global Velocity Files *****************************************************************************************
			setFileInfo(GLOBAL_VELOCITY_OBJECT);
			myFileVelocity << "  " << DATA << " " << OBJECT_BEGIN2 << "\n" << "    " << FREQUENCY << " " << (k+1) << "\n    "<< VALUE << " " << LIST_BEGIN2 << "\n";
				
			for(int a = 0; a < 6; a++) //print the 6 outputs per each frequency
			{
				myFileVelocity.precision(15);
				myFileVelocity <<  "    " << globalVelSolutionList[k].at(a,0).real(); 

				if(globalVelSolutionList[j].at(a,0).imag() < 0.0)
					myFileVelocity <<   globalVelSolutionList[j].at(a,0).imag()<< "i\n";
				else
					myFileVelocity <<  "+" << globalVelSolutionList[j].at(a,0).imag()<< "i\n";
			}
			myFileVelocity << "    " << LIST_END2 << "\n  " << OBJECT_END2 << "\n";

			//Write Global Acceleration Files *************************************************************************************
			setFileInfo(GLOBAL_ACCELERATION_OBJECT);
			myFileAcceleration << "  " << DATA << " " << OBJECT_BEGIN2 << "\n" << "    " << FREQUENCY << " " << (k+1) << "\n    "<< VALUE << " " << LIST_BEGIN2 << "\n";
				
			for(int a = 0; a < 6; a++) //print the 6 outputs per each frequency
			{
				myFileAcceleration.precision(15);
				myFileAcceleration <<  "    " << globalAccSolutionList[k].at(a,0).real(); 

				if(globalAccSolutionList[j].at(a,0).imag() < 0.0)
					myFileAcceleration <<   globalAccSolutionList[j].at(a,0).imag()<< "i\n";
				else
					myFileAcceleration <<  "+" << globalAccSolutionList[j].at(a,0).imag()<< "i\n";
			}
			myFileAcceleration << "    " << LIST_END2 << "\n  " << OBJECT_END2 << "\n";
		}

		myFileMotion << OBJECT_END2 << "\n";
		myFileVelocity << OBJECT_END2 << "\n";
		myFileAcceleration << OBJECT_END2 << "\n";
	}
	myFileMotion << BREAK_BOTTOM;
	myFileVelocity << BREAK_BOTTOM;
	myFileAcceleration << BREAK_BOTTOM;

	myFileMotion.close();
	myFileVelocity.close();
	myFileAcceleration.close();

	return 0;
}

int FileWriter::writeDirectionsToFile(vector<double> directionList)
{
	setFileInfo(DIRECTION);

	ofstream myFileAcceleration;
	myFileAcceleration.open(DIRECTIONS_FILENAME);

	myFileAcceleration << header << fileInfo << BREAK_TOP << DIRECTION << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < directionList.size(); i ++)
	{
		myFileAcceleration  << directionList[i] << "\n";
	}

	myFileAcceleration << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFileAcceleration.close();

	return 0;
}

int FileWriter::writeFrequenciesToFile(vector<double> frequencyList)
{
	setFileInfo(FREQUENCY);

	ofstream myFileAcceleration;
	myFileAcceleration.open(FREQUENCIES_FILENAME);

	myFileAcceleration << header << fileInfo << BREAK_TOP << FREQUENCY << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < frequencyList.size(); i ++)
	{
		myFileAcceleration << frequencyList[i] << "\n";
	}

	myFileAcceleration << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFileAcceleration.close();

	return 0;
}
