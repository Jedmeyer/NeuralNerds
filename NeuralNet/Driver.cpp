#include <iostream>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "C2048.h"
#include "Params.h"

using namespace std;

int main(){
	cout<<"HELP ME"<<endl;
	/*
	srand( static_cast<uint>( time( NULL ) ) );
	g2048 g;
	g.loop();
	*/
	cout<<"Param Test Bias: "<<Params::bias<<endl;
	cout<<"Param Test Inputs: "<<Params::numInputs<<endl;
	cout<<"Param Test Hidden: "<<Params::numHidden<<endl;
	cout<<"Param Test Activation: "<<Params::activation<<endl;


	return 0;
}
