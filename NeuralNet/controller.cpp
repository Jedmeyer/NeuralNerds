#include <iostream>
#include "NeuralNet.h"
#include "GenAlg.h"
#include "2048.h"

using namespace std;

int main(){
	cout<<"HELP ME"<<endl;

	srand( static_cast<uint>( time( NULL ) ) );
	g2048 g;


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

	return 0;
}
