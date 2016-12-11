#include "GenAlg.h"



using namespace std;

genome::genome(){fitness = 0;}

genome::genome(double f1){
	fitness = f1;};

genome::genome(vector <double> w1, double f1){
	chromoWeights = w1;
	fitness = f1;
};









