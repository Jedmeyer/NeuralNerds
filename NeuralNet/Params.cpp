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
double bias = 0;
double numChromo = 0;
double pop = 0;


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
	grab >> numChromo;
	grab >> paramDescription;
	grab >> pop;
}

/*
Format ini file as:

"Parameter Name" with only a space inbetween, then "Parameter value"

*/