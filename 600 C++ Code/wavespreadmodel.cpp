#include "wavespreadmodel.h"


WaveSpreadModel::WaveSpreadModel()
{
}


WaveSpreadModel::~WaveSpreadModel()
{
}

void WaveSpreadModel::testPrint()
{
	cout << "SpreadModelName: " << spreadModelName << endl;
	for(int i = 0; i < spreadEntries.size(); i++)
	{
		cout << "--Entry 1--" << endl;
		cout << "Direction Angle: " << spreadEntries[i].directionAngle << endl;
		cout << "Selected Wave Spectrum: " << spreadEntries[i].waveSpectrumName << endl;
		cout << "Scaling Factor: " << spreadEntries[i].scalingFactor << endl;
	}
}
void WaveSpreadModel::setSpreadModelName(string newName)
{
	spreadModelName = newName;
}

void WaveSpreadModel::setSelectedpectrumName(string newName)
{
	SpreadEntry newSpreadEntry;
	newSpreadEntry.waveSpectrumName = newName;
	spreadEntries.push_back(newSpreadEntry);
	currentSpreadEntry = spreadEntries.size()-1;
}

void WaveSpreadModel::setSelectedSpreadModelAngle(double val)
{
	spreadEntries[currentSpreadEntry].directionAngle = val;
}

void WaveSpreadModel::setSpectrumScalingFactor(double val)
{
	spreadEntries[currentSpreadEntry].scalingFactor = val;
}
