#ifndef OUTPUTSBODY_H
#define OUTPUTSBODY_H
#include <vector>
#include "armadillo"
#include "body.h"
#include "globalacceleration.h"
#include "globalmotion.h"
#include "globalvelocity.h"

using namespace std;
using namespace arma;

const int GLOBAL_MOTION = 0;
const int GLOBAL_VELOCITY = 1;
const int GLOBAL_ACCELERATION = 2;
const int GLOBAL_SIZE = 3; //# of global types to include in vector

class OutputsBody
{
public:
	OutputsBody(Body, vector<double>);
	~OutputsBody();

	Body theBody;
	vector<double> frequencies;
	vector<cx_mat> outputType; //Each index is a cx_mat which reps, 0- Mot, 1 - acc, 2 - vel
	cx_mat outputList; //FIX< need to implement, this holds a single cx_mat from the outputType

	//void calculateOutputs(int);
	void calculateOutputs();
	OutputsBody getOutputsBody();//FIX, probably dont need this
	//outputs here
};
#endif
