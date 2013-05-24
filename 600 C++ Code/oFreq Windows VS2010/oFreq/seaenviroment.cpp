#include "seaenviroment.h"


SeaEnviroment::SeaEnviroment() 
{
}


SeaEnviroment::~SeaEnviroment()
{
	/*if( curSpectrum != NULL)
	{
		curSpectrum = NULL;
		delete curSpectrum;
	}*/

	//for(int i = 0; i < specifiedSpectrum.size(); i++)
	//	delete &specifiedSpectrum[i];

	//for(int i = 0; i < specifiedSpreadModel.size(); i++)
	//	delete &specifiedSpreadModel[i];
}

void SeaEnviroment::testPrint()
{
	for(int i = 0; i < specifiedSpectrum.size(); i++)
	{
		cout << "---Spectrum Object " << i+1 << " ---" << endl;
		specifiedSpectrum[i].testPrint();
	}

	for(int i = 0; i < specifiedSpreadModel.size(); i++)
	{
		cout << "---Spread Model Object " << i << " ---" << endl;
		specifiedSpreadModel[i].testPrint();
	}
	cout << endl;
}

void SeaEnviroment::setWaveSpectrumName(string newName)
{
	WaveSpectrumModel newSpectrumModel;
	newSpectrumModel.setSpectrumName(newName);
	specifiedSpectrum.push_back(newSpectrumModel);
	currentSpectrum = specifiedSpectrum.size() - 1;
}

void SeaEnviroment::setWaveSpectrumFrequencies(vector<double> vecIn)
{
	specifiedSpectrum[currentSpectrum].setFrequencies(vecIn);
}

void SeaEnviroment::setWaveSpectrumWaveEnergy(vector<double> vecIn)
{
	specifiedSpectrum[currentSpectrum].setWaveEnergy(vecIn);
}

//int SeaEnviroment::getCurrentIndex(string searchKey)
//{
//	for(int i = 0; i < specifiedSpectrum.size() ; i++)
//	{
//		if (searchKey == specifiedSpectrum.getName();
//			return i;
//	}
//}

void SeaEnviroment::setSpreadModelName(string newName)
{
	WaveSpreadModel newSpreadModel;
	newSpreadModel.setSpreadModelName(newName);
	specifiedSpreadModel.push_back(newSpreadModel);
	currentSpreadModel = specifiedSpreadModel.size() - 1;
}

//this is the wave spectrum contained inside "spread entry"
void SeaEnviroment::setSpreadModelWaveSpectrumName(string newName)
{
	specifiedSpreadModel[currentSpreadModel].setSelectedpectrumName(newName);
}

void SeaEnviroment::setSpreadModelDirectionAngle(double val)
{
	specifiedSpreadModel[currentSpreadModel].setSelectedSpreadModelAngle(val);
}



void SeaEnviroment::setSpreadModelScalingFactor(double val)
{
	specifiedSpreadModel[currentSpreadModel].setSpectrumScalingFactor(val);
}

//private:
//	vector<WaveSpectrumModel> specifiedSpectrum;
//	vector<WaveSpreadModel> specifiedSpreadModel;
//	int currentSpectrum;
//	int currentSpreadModel;


