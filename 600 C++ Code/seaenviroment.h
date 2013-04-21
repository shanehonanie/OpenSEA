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
private:
	vector<WaveSpectrumModel> specifiedSpectrum;
	vector<WaveSpreadModel> specifiedSpreadModel;
};
#endif
