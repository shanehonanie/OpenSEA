#ifndef WAVEDIRECTIONS_H
#define WAVEDIRECTIONS_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class WaveDirections
{
public:
	WaveDirections();
	~WaveDirections();
	void addDirection(int);
	void setDirections(vector<double>);
	void setSpreadModel(string);
	void testPrint();
private:
	vector<double> directions;
	string spreadModel;
};
#endif
