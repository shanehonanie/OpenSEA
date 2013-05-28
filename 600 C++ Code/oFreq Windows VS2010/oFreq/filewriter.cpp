#include "filewriter.h"


FileWriter::FileWriter(OutputsList outputListIn) 
	: theOutputsList(outputListIn), theWaveDirectionsList(outputListIn.theDirectionList), thefrequenciesList(outputListIn.theFrequencyList)
{
	setHeader();	
	writeDirectionsToFile(thefrequenciesList);
	writeFrequenciesToFile(thefrequenciesList);
	writeToFile();
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
	fileInfo = SEAFILE2 + "\n" + OBJECT_BEGIN2 + "\n    " + VERSION + "   " + VERSION_INFO + END + "\n    " + FORMAT + "    " + FORMAT_INFO + END + "\n    " + OBJECT + "    " + objectIn + END + "\n" + OBJECT_END2 + "\n";
}

FileWriter::~FileWriter()
{
}

int FileWriter::writeToFile()
{
	int curWaveDirection;
	int curFrequency;

	vector<double> temp;
	temp.push_back(1.00);

	for(int i = 0; i < temp.size(); i++)//iterate through all of the wave directions
	//for(int i = 0; i < theWaveDirectionsList.size(); i++)//iterate through all of the wave directions
	{
		curWaveDirection = i;
		ofstream myFile;
		string directory = "d" + curWaveDirection + '/';
		myFile.open(directory + GLOBAL_ACCELERATION_FILENAME); //Create the file

		for(int j = 0; theOutputsList.theBodyList.size(); j++) //iterate through all of the bodies
		{
			for(int k = 0; k < thefrequenciesList.size(); k++) //iterate through all of the frequencies
			{
				curFrequency = k+1;
				vector<cx_mat> globalAccSolutionList = theOutputsList.theOutputsBodyList[j].getOutputType(2);

				//Write Global Acceleration Files
				setFileInfo("accglobal");

				
				myFile << header << fileInfo << BREAK_TOP << BODY << " " << OBJECT_BEGIN2 
					<< "\n  " << NAME << " " << theOutputsList.theBodyList[i].bodyName << END << "\n  "
					<< FREQUENCY << " " << curFrequency << "\n  "
					<< VALUE << " " << LIST_BEGIN2 << "\n  ";

				for(int a = 0; a < 6; a++) //print the 6 outputs per each frequency
				{
					myFile << globalAccSolutionList[j].at(a,1) << "\n";
				}

				myFile << LIST_END2 << "\n" << OBJECT_END2 << "\n";



				//Write GLobal Motion Files



				//Write Global Velocity Files



			}
		}
		myFile << BREAK_BOTTOM;
		myFile.close();
	}

	return 0;
}

int FileWriter::writeDirectionsToFile(vector<double> directionList)
{
	setFileInfo(DIRECTION);

	ofstream myFile;
	myFile.open(DIRECTIONS_FILENAME);

	myFile << header << fileInfo << BREAK_TOP << DIRECTION << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < directionList.size(); i ++)
	{
		myFile  << directionList[i] << "\n";
	}

	myFile << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFile.close();

	return 0;
}

int FileWriter::writeFrequenciesToFile(vector<double> frequencyList)
{
	setFileInfo(FREQUENCY);

	ofstream myFile;
	myFile.open(FREQUENCIES_FILENAME);

	myFile << header << fileInfo << BREAK_TOP << FREQUENCY << " " << LIST_BEGIN2 << "\n";

	for(int i = 0; i < frequencyList.size(); i ++)
	{
		myFile << frequencyList[i] << "\n";
	}

	myFile << LIST_END2  << "\n\n" << BREAK_BOTTOM;
	myFile.close();

	return 0;
}
