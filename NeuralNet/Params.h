#ifndef PARAMS_H
#define PARAMS_H

#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

class Params
{

public:

//----------- General Parameters -------------\\



//--------------- Neural Net -----------------\\

static double numInputs;
static double numHidden;
static double neuronsPerHiddenLayer;
static double numOutputs;

static double bias;
static double activation;

//------------Genetic Alg Params--------------\\

static double numChromo;
static double pop;

	Params(){
		if(!LoadInParameters("params.ini")){
			MessageBox(NULL, "Cannot find params.ini","Error", 0);
		}
	}

	bool LoadInParameters(char* fileName);

};



#endif
