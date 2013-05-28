#ifndef SYSTEM_H
#define SYSTEM_H
#include "wavedirections.h"
#include "wavefrequencies.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class System
{
public:
	System();
	~System();
	void testPrint();
	void setAnalysisType(string);
	void setWaveFrequencies(vector<double>);
	void setWaveDirections(vector<double>);
	void setSpreadModel(string);
	vector<double> getWaveFrequencies();
	vector<double> getWaveDirections();
private:
	string analysisType;
	WaveDirections waveDirections;
	WaveFrequencies waveFrequencies;
};
#endif

