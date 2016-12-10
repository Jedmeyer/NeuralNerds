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


bool Params::LoadInParameters(char* fileName){
	ifstream fin(fileName);

	if(!fin){
		return false;
	}

	char paramDescription[30];

	grab >> numInputs;
	grab >> paramDescription;
	grab >> numHidden;
	grab >> paramDescription;
	grab >> neuronsPerHiddenLayer;
	grab >> paramDescription;
	grab >> numOutputs;
	grab >> paramDescription;
	grab >> bias;
	grab >> paramDescription;
	grab >> activation;
	grab >> paramDescription;
	grab >> numChromo;
	grab >> paramDescription;
	grab >> pop;
	grab >> paramDescription;
	grab >> activation;
}

/*
Format ini file as:

"Parameter Name" with only a space inbetween, then "Parameter value"

*/