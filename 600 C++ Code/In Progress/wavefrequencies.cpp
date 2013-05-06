#include "wavefrequencies.h"


WaveFrequencies::WaveFrequencies()
{
}


WaveFrequencies::~WaveFrequencies()
{
}

void WaveFrequencies::testPrint()
{
	for(int i = 0; i < frequencies.size(); i++)
	{
		cout << "frequency[" << i << "]: " << frequencies[i] << endl;
	}
}

void WaveFrequencies::setFrequencies(vector<double> theListIn)
{
	for(int i = 0; i < theListIn.size(); i++)
	{
		frequencies.push_back(theListIn[i]);
	}
}