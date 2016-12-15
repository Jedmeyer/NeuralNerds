#include <iostream>
#include <fstream>
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

int count;

vector<double> redirect(vector<double> output){
	bool a = output[0];
	bool b = output[1];
	cout<<"A: "<<a<<endl;
	cout<<"B: "<<b<<endl;
	switch(count){
		case 0: a=!a; break;
		case 1: b=!b; break;
		case 2: a=!a; break;
	}
	if(a) output[0] = 1;
	else output[0] = 0;
	if(b) output[1] = 1;
	else output[1] = 0;

	output[0] = a;
	output[1] = b;
	return output;
}


int main(){
	ofstream fout;
	fout.open("data.txt");
	count = 0;
	Params p;
	int illegalMoves = 0;
	vector<double> inputs;
	vector<double> outputs;
	int popSize = Params::pop;
	int maxIllegalMoves = Params::illegalMoves;
	cout<<"HELP ME"<<endl;

	cout<<popSize<<endl;
	srand( static_cast<uint>( time( NULL ) ) );

	NeuralNet net;//declares the neural network object
	GenAlg gen(net);//Declares the GenAlg object and fills the population

	vector<double> GWeights;
	int genNum = 0;
	int maxFit = 0;
	int totalFit = 0;
	int aveFit = 0;
	while(true){//This will be the start of the main loop for the genalg.

		genNum++;
		for(int i = 0; i< popSize; i++){//This is the loop for each genome in the generation

			GWeights = gen.population[i].chromoWeights;//Gets the Weigths for this genome
			g2048 g;
			g.addTile();//This initializes the 2048 board

		  while( true )//This is the 2048 game loop
		  {
		    if( g.moved ){
					g.addTile();
					//illegalMoves=0;
					count = 0;
				}
				else{
					if(outputs.size() == 2){
						outputs = redirect(outputs);
						count ++;
						cout<<"HERE"<<endl;
					}

					//illegalMoves++;
					//cout<<illegalMoves<<endl;
					//if(illegalMoves >= maxIllegalMoves){illegalMoves = 0; break;}
				}


		    //g.drawBoard();
				cout<<"Genome Number: "<<i+1<<endl;

		    if( g.done ) break;
		    //g.waitKey();

				if(count <= 0){
					inputs = g.toInput();
					outputs = net.Update(inputs);
				}
				/// Changes outputs into two bit binary format
				for(int i = 0; i < outputs.size(); ++i){
					//cout<<"Output pre Binary: "<<outputs[1]<<endl;
					if(outputs[i] > 0){outputs[i] = 1;}
					else if(outputs[i] <= 0){outputs[i] = 0;}
					else{cout<<"Those Number are UNREAL Man"<<endl; break;}
				}

				for(int j = 0; j < outputs.size(); ++j) cout<<outputs[j]<<endl;
				//for(int i = 0; i < 100000000; ++i);
				g.netMove(outputs);
		  }
			gen.population[i].setfitness(g.score);
			totalFit += g.score;
			if(g.score>maxFit){
				maxFit = g.score;
			}
		  string s = "Game Over!";
		  if( g.win ) s = "You've made it!";
		  cout << s << endl << endl;
		}
		aveFit = totalFit/popSize;

		fout<<endl<<endl<<endl<<genNum<<endl<<maxFit<<endl<<aveFit<<endl;
		maxFit=0;
		aveFit = 0;
		totalFit = 0;
		gen.nextGen();
		//gen.population = gen.selection();//This sets up the next generation

	}
	fout.close();
	return 0;
}
