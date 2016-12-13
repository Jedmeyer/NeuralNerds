#include "Params.h"

//List of settings with data types and initializer
/*
Example:

double Params::Pi		=3.1415926535;

*/
double Params::numInputs   = 0;
double Params::numHidden   = 0;
double Params::neuronsPerHiddenLayer = 0;
double Params::numOutputs = 0;
double Params::bias = 0;
double Params::activation = 0;
double Params::numChromo = 0;
double Params::pop = 0;
double Params::mute = 0;
double Params::cross = 0;


bool Params::LoadInParameters(char* fileName){
	ifstream fin(fileName);

	if(!fin){
		return false;
	}

	char paramDescription[30];

	fin >> paramDescription;
	fin >> numInputs;
	fin >> paramDescription;
	fin >> numHidden;
	fin >> paramDescription;
	fin >> neuronsPerHiddenLayer;
	fin >> paramDescription;
	fin >> numOutputs;
	fin >> paramDescription;
	fin >> bias;
	fin >> paramDescription;
	fin >> activation;
	fin >> paramDescription;
	fin >> numChromo;
	fin >> paramDescription;
	fin >> pop;
	fin >> paramDescription;
	fin >> mute;
	fin >> paramDescription;
	fin >> cross;

	return true;
}

/*
Format ini file as:

"Parameter Name" with only a space inbetween, then "Parameter value"

*/
