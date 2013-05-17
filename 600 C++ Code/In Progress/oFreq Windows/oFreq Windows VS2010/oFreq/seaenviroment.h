#ifndef SEAENVIROMENT_H
#define SEAENVIROMENT_H
#include "wavespectrummodel.h"
#include "wavespreadmodel.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class SeaEnviroment
{
public:
	SeaEnviroment();
	~SeaEnviroment();
	void testPrint();

	void setWaveSpectrumName(string);
	void setWaveSpectrumFrequencies(vector<double>);
	void setWaveSpectrumWaveEnergy(vector<double>);

	void setSpreadModelName(string);
	void setSpreadModelDirectionAngle(double);
	void setSpreadModelWaveSpectrumName(string);
	void setSpreadModelScalingFactor(double);

	void getCurrentIndex(string);

private:
	vector<WaveSpectrumModel> specifiedSpectrum;
	vector<WaveSpreadModel> specifiedSpreadModel;
	int currentSpectrum;
	int currentSpreadModel;
};
#endif
