#include <iostream>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "C2048.h"
#include "Params.h"
#include <vector>

using namespace std;

int main(){
	cout<<"HELP ME"<<endl;
	/*
	srand( static_cast<uint>( time( NULL ) ) );
	g2048 g;
	g.loop();
	*/


	Params p;
	cout<<"Param Test Bias: "<<Params::bias<<endl;
	cout<<"Param Test Inputs: "<<Params::numInputs<<endl;
	cout<<"Param Test Hidden: "<<Params::numHidden<<endl;
	cout<<"Param Test Activation: "<<Params::activation<<endl;
	
	/*
	//g.loop();
	while(true){
		g.addTile();
	  while( true )
	  {
	    if( g.moved ) g.addTile();
	    g.drawBoard();
	    if( g.done ) break;
	    g.waitKey();
	  }
	  string s = "Game Over!";
	  if( g.win ) s = "You've made it!";
	  cout << s << endl << endl;
	  }
	}
	*/




	return 0;
}
