#include "filewriter.h"

FileWriter::FileWriter(vector<double> theDirectionsListIn, vector<double> theFrequenciesListIn) 
	: theDirectionsList(theDirectionsListIn), thefrequenciesList(theFrequenciesListIn)
{
	setHeader();

	if(!removeOldDirectories())
	{
		cerr << "Failed to Remove All directories." << endl;
	}

	if(!writeDirectionsToFile(theDirectionsList))
	{
		cerr << "Failed to write direction list to file." << endl;
	}

	if(!writeFrequenciesToFile(thefrequenciesList))
	{
		cerr << "Failed to write frequencies to file." << endl;
	}
}

void FileWriter::setOutputs(OutputsList theOutputsListIn)
{
	theOutputsList = theOutputsListIn;
}

void FileWriter::setHeader()
{
    ifstream header_fileInput(HEADER_FILENAME.c_str());

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

bool FileWriter::writeToFile(int curWaveDirection)
{
	ofstream myFileMotion;
	ofstream myFileVelocity;
	ofstream myFileAcceleration;
	
	string dirNum = boost::lexical_cast<string>(curWaveDirection); //cast int to string for comparison
	string currentDirectory = DIR_NAME + dirNum;

	//Create the current directory
	if (!create_directory(currentDirectory))
	{
		cerr << "Failed to create " + currentDirectory << endl; //This needs to be handled
		return false;
	}
    string filepath;
    filepath = currentDirectory + "/" + GLOBAL_MOTION_FILENAME;
    myFileMotion.open(filepath.c_str()); //Create the Motion file
    filepath = currentDirectory + "/" + GLOBAL_VELOCITY_FILENAME;
    myFileVelocity.open(filepath.c_str()); //Create the Velocity file
    filepath = currentDirectory + "/" + GLOBAL_ACCELERATION_FILENAME;
    myFileAcceleration.open(filepath.c_str()); //Create the Acceleration file

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

	return true;
}

bool FileWriter::writeDirectionsToFile(vector<double> directionList)
{
	setFileInfo(DIRECTION);

	ofstream myFileAcceleration;
    myFileAcceleration.open(DIRECTIONS_FILENAME.c_str());

	myFileAcceleration << header << fileInfo << BREAK_TOP << DIRECTION << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < directionList.size(); i ++)
	{
		myFileAcceleration  << directionList[i] << "\n";
	}

	myFileAcceleration << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFileAcceleration.close();

	return true;
}

bool FileWriter::writeFrequenciesToFile(vector<double> frequencyList)
{
	setFileInfo(FREQUENCY);

	ofstream myFileAcceleration;
    myFileAcceleration.open(FREQUENCIES_FILENAME.c_str());

	myFileAcceleration << header << fileInfo << BREAK_TOP << FREQUENCY << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < frequencyList.size(); i ++)
	{
		myFileAcceleration << frequencyList[i] << "\n";
	}

	myFileAcceleration << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFileAcceleration.close();

	return true;
}

bool FileWriter::removeOldDirectories()
{
	string numToDelete = "0";
	string curDirectoryPath = DIR_NAME + numToDelete; //start at directory "d0"

	//Remove the direcions & frequencies file outputs if they exist
	if(exists(DIRECTIONS_FILENAME))
		remove(DIRECTIONS_FILENAME);

	if(exists(FREQUENCIES_FILENAME))
		remove(FREQUENCIES_FILENAME);
	
	while(exists(curDirectoryPath)) //check if current directory exists
	{
		if(!remove_all(curDirectoryPath))
		{
			cerr << "Failed to delete " + curDirectoryPath << endl;
			return false;
		}
		else //increment to next directory
		{
			int numToDeleteHelper = boost::lexical_cast<int>(numToDelete);
			++numToDeleteHelper;
			numToDelete = boost::lexical_cast<string>(numToDeleteHelper);
			curDirectoryPath = DIR_NAME + numToDelete;
		}
	}
	return true; //all directories deleted successfully
}
