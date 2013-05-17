#include "wavedirections.h"


WaveDirections::WaveDirections()
{
}


WaveDirections::~WaveDirections()
{
}

void WaveDirections::testPrint()
{
	cout << "spreadModel: " << spreadModel << endl;
	for(int i = 0; i < directions.size(); i++)
	{
		cout << "waveDir[" << i << "]: " << directions[i] << endl;
	}
}

void WaveDirections::setDirections(vector<double> theListIn)
{
	for(int i = 0; i < theListIn.size(); i++)
	{
		directions.push_back(theListIn[i]);
	}
}

void WaveDirections::setSpreadModel(string spreadModelIn)
{
	spreadModel = spreadModelIn;
}