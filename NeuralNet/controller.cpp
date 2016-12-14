#include <iostream>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "C2048.h"
#include "NeuralNet.h"
#include "GenAlg.h"
#include "Params.h"

using namespace std;

int main(){
	vector<double> inputs;
	int popSize = Params::pop;
	cout<<"HELP ME"<<endl;

	srand( static_cast<uint>( time( NULL ) ) );

	NeuralNet net;//declares the neural network object
	GenAlg gen(net);//Declares the GenAlg object and fills the population
	vector<double> GWeights;
	while(true){//This will be the start of the main loop for the genalg.
		for(int i = 0; i< popSize; i++){//This is the loop for each genome in the generation
			GWeights = gen.population[i].chromoWeights;//Gets the Weigths for this genome
			g2048 g;
			g.addTile();//This initializes the 2048 board
		  while( true )//This is the 2048 game loop
		  {
		    if( g.moved ) g.addTile();
		    g.drawBoard();
		    if( g.done ) break;
		    //g.waitKey();
				inputs = g.toInput();
				g.netMove(net.Update(inputs));
		  }
		  string s = "Game Over!";
		  if( g.win ) s = "You've made it!";
		  cout << s << endl << endl;
		}
		gen.nextGen();
		//gen.population = gen.selection();//This sets up the next generation

}
	return 0;
}
