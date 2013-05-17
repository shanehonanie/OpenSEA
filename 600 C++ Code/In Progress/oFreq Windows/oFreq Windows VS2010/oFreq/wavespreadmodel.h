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
	void testPrint();
	void setSpreadModelName(string);
	void setSelectedpectrumName(string);
	void setSelectedSpreadModelAngle(double);
	void setSpectrumScalingFactor(double);
private:
	string spreadModelName;
	int currentSpreadEntry;

	struct SpreadEntry;
	vector<SpreadEntry> spreadEntries;

	struct SpreadEntry
	{
		double directionAngle;
		string waveSpectrumName;
		double scalingFactor;
	};
};
#endif
