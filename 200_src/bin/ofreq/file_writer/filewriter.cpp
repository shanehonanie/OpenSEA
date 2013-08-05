/*----------------------------------------*- C++ -*------------------------------------------------------------------*\
| O pen         | OpenSea: The Open Source Seakeeping Suite                                                           |
| S eakeeping	| Web:     www.opensea.dmsonline.us                                                                   |
| E valuation   |                                                                                                     |
| A nalysis     |                                                                                                     |
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

#include "filewriter.h"

FileWriter::FileWriter(string fileDirIn, vector<double> theDirectionsListIn, vector<double> theFrequenciesListIn) 
	: oFreq_Directory(fileDirIn), theDirectionsList(theDirectionsListIn), thefrequenciesList(theFrequenciesListIn)
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

FileWriter::~FileWriter()
{}

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

bool FileWriter::writeToFile(int curWaveDirection)
{
	ofstream myFileMotion;
	ofstream myFileVelocity;
	ofstream myFileAcceleration;
	
	string dirNum = boost::lexical_cast<string>(curWaveDirection); //cast int to string for comparison
	string currentDirectory = DIR_NAME + dirNum;

	//Create the current directory
	if (!create_directory(oFreq_Directory + currentDirectory))
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

	for(unsigned int j = 0; j < theOutputsList.theBodyList.size(); j++) //iterate through all of the bodies
	{
		vector<cx_mat> globalMotSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(0);
		vector<cx_mat> globalVelSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(1);
		vector<cx_mat> globalAccSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(2);

		myFileMotion << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << "\"" << theOutputsList.theBodyList[j].bodyName << "\"" << END << "\n";

		myFileVelocity << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << "\"" << theOutputsList.theBodyList[j].bodyName << "\"" << END << "\n";

		myFileAcceleration << BODY << " " << OBJECT_BEGIN2 
				<< "\n  " << NAME << " " << "\"" << theOutputsList.theBodyList[j].bodyName << "\"" << END << "\n";
			
		for(unsigned int k = 0; k < thefrequenciesList.size(); k++) //iterate through all of the frequencies
		{
			//Write Global Motion Files *******************************************************************************************
			setFileInfo(GLOBAL_MOTION_OBJECT);
			myFileMotion << "  " << DATA << " " << OBJECT_BEGIN2 << "\n" << "    " << FREQUENCY << " " << (k+1) << "\n    "<< VALUE << " " << LIST_BEGIN2 << "\n";
				
			for(unsigned int a = 0; a < 6; a++) //print the 6 outputs per each frequency
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
				
			for(unsigned int a = 0; a < 6; a++) //print the 6 outputs per each frequency
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
				
			for(unsigned int a = 0; a < 6; a++) //print the 6 outputs per each frequency
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
    string writeFilename;
    setFileInfo(DIRECTION);

    ofstream myFileAcceleration;
    writeFilename = oFreq_Directory + DIRECTIONS_FILENAME;
    myFileAcceleration.open(writeFilename.c_str());

	myFileAcceleration << header << fileInfo << BREAK_TOP << DIRECTION << " " << LIST_BEGIN2 << "\n";

	for(unsigned int i = 0; i < directionList.size(); i ++)
	{
		myFileAcceleration  << directionList[i] << "\n";
	}

	myFileAcceleration << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFileAcceleration.close();

	return true;
}

bool FileWriter::writeFrequenciesToFile(vector<double> frequencyList)
{
    string writeFilename;
    setFileInfo(FREQUENCY);

	ofstream myFileAcceleration;
    writeFilename = oFreq_Directory + FREQUENCIES_FILENAME;
    myFileAcceleration.open(writeFilename.c_str());

	myFileAcceleration << header << fileInfo << BREAK_TOP << FREQUENCY << " " << LIST_BEGIN2 << "\n";

	for(unsigned int i = 0; i < frequencyList.size(); i ++)
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
	if(exists(oFreq_Directory + DIRECTIONS_FILENAME))
		remove(oFreq_Directory + DIRECTIONS_FILENAME);

	if(exists(oFreq_Directory + FREQUENCIES_FILENAME))
		remove(oFreq_Directory + FREQUENCIES_FILENAME);
	
	while(exists(oFreq_Directory + curDirectoryPath)) //check if current directory exists
	{
		if(!remove_all(oFreq_Directory + curDirectoryPath))
		{
			cerr << "Failed to delete " + oFreq_Directory + curDirectoryPath << endl;
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
