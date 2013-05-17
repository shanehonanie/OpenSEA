#include "wavespectrummodel.h"


WaveSpectrumModel::WaveSpectrumModel()
{}


WaveSpectrumModel::~WaveSpectrumModel()
{}

void WaveSpectrumModel::testPrint()
{
	cout << "spectrumName: " << spectrumName << endl;
	for(int i = 0; i < frequencies.size(); i ++)
	{
		cout << "frequencies[" << i << "]: " << frequencies[i] << endl;
	}

	for(int i = 0; i < waveEnergy.size(); i ++)
	{
		cout << "waveEnergy[" << i << "]: " << waveEnergy[i] << endl;
	}
}

string WaveSpectrumModel::getSpectrumName()
{
	return spectrumName;
}

void WaveSpectrumModel::setFrequencies(vector<double> theListIn)
{
	for(int i = 0; i < theListIn.size(); i++)
	{
		frequencies.push_back(theListIn[i]);
	}
}

void WaveSpectrumModel::setWaveEnergy(vector<double> theListIn)
{
	for(int i = 0; i < theListIn.size(); i++)
	{
		waveEnergy.push_back(theListIn[i]);
	}
}

void WaveSpectrumModel::setSpectrumName(string newName)
{
	spectrumName = newName;
}

string WaveSpectrumModel::getName()
{
	return spectrumName;
}


