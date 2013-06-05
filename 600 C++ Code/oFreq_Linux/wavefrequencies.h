#ifndef WAVEFREQUENCIES_H
#define WAVEFREQUENCIES_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class WaveFrequencies
{
public:
	WaveFrequencies();
	~WaveFrequencies();
	void addFrequency(double);
	void testPrint();
	void setFrequencies(vector<double>);
	vector<double> getWaveFrequencies();
private:
	vector<double> frequencies;
};
#endif

