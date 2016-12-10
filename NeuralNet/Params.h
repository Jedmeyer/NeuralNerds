#ifndef PARAMS_H
#define PARAMS_H

#include <fstream>
#include <windows.h>

using namespace std;

class Params
{

public:

//----------- General Parameters -------------\\
	


//--------------- Neural Net -----------------\\

static int numInputs;
static int numHidden;
static int neuronsPerHiddenLayer;
static int numOutputs;

static double bias;
static double activation;

//------------Genetic Alg Params--------------\\

static int numChromo;
static int pop;

	Params(){
		if(!LoadInParams("params.ini")){
			MessageBox(NULL, "Cannot find params.ini","Error", 0);
		}
	}

	bool LoadInParameters(char* fileName);

};



#endif