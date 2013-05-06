#include "system.h"


System::System() : waveDirections(), waveFrequencies()
{
	/*waveDirections = new WaveDirections();
	waveFrequencies = new WaveFrequencies();*/
}


System::~System()
{
}

void System::testPrint()
{
	cout << "Analysis Type: " << analysisType << endl;
	waveDirections.testPrint();
	waveFrequencies.testPrint();
	cout << endl;
}

void System::setAnalysisType(string analysisTypeIn)
{
	analysisType = analysisTypeIn;
}

void System::setWaveFrequencies(vector<double> vecIn)
{
	waveFrequencies.setFrequencies(vecIn);
}

void System::setWaveDirections(vector<double> vecIn)
{
	waveDirections.setDirections(vecIn);
}

void System::setSpreadModel(string spreadIn)
{
	waveDirections.setSpreadModel(spreadIn);
}