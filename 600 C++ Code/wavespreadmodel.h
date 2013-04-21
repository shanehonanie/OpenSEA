#ifndef WAVESPREADMODEL_H
#define WAVESPREADMODEL_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class WaveSpreadModel
{
public:
	WaveSpreadModel();
	~WaveSpreadModel();
private:
	string name;
	struct SpreadEntry;
	vector<SpreadEntry> spreadEntries;

	struct SpreadEntry
	{
		vector<double> directionAngle;
		string selectedWaveSpectrum;
		double scalingFactor;
	};
};
#endif
