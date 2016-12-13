#include <iostream>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "C2048.h"
#include "Params.h"
#include <vector>
#include <cmath>
#include <random>

using namespace std;

int main(){
	cout<<"HELP ME"<<endl;

	/*
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-1,1); //doubles from -1 to 1

	for(int i = 0; i < 100; ++i){
		cout<<distribution(generator)<<endl;
	}
	*/

	/*
	srand( static_cast<uint>( time( NULL ) ) );
	g2048 g;
	g.loop();
	*/

	/*
	Params p;
	cout<<"Param Test Bias: "<<Params::bias<<endl;
	cout<<"Param Test Inputs: "<<Params::numInputs<<endl;
	cout<<"Param Test Hidden: "<<Params::numHidden<<endl;
	cout<<"Param Test Activation: "<<Params::activation<<endl;
	*/

	g2048 g;
	vector<double> boardInputTest;
	//g.loop();
	while(true){
		g.addTile();
	  while( true )
	  {
	    if( g.moved ) g.addTile();
	    g.drawBoard();
	    if( g.done ) break;

			boardInputTest = g.toInput();
			for(int i = 0; i < boardInputTest.size(); ++i){
				if(i%4 == 0){
					cout<<"---"<<endl;
				}
				cout << boardInputTest[i] << endl;
			}

	    //g.waitKey();
			g.randMove();
	  }
	  string s = "Game Over!";
	  if( g.win ) s = "You've made it!";
	  cout << s << endl << endl;
	  }



	return 0;
}
