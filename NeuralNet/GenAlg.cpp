#include "GenAlg.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <vector>
#include "NeuralNet.h"
#include "Params.h"
using namespace std;

genome::genome(){
	fitness = 0;
	mutationChance = Params::mute;
	crossChance = Params::cross;
}

genome::genome(double f1){
	fitness = f1;
	mutationChance = Params::mute;
	crossChance = Params::cross;
};

genome::genome(vector<double> w1, double f1){
	chromoWeights = w1;
	fitness = f1;
	mutationChance = Params::mute;
	crossChance = Params::cross;
};

bool genome::operator <(const genome &g2){
	return this->fitness < g2.fitness;
};

double genome::fRand(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void genome::setfitness(double ft){
	fitness = ft;
}

void genome::mutate(){
	int p = this->chromoWeights.size();
	int r;
	double muteVal;
	double willmute;
	for (int i=0; i < p; i++){
		willmute = fRand(0,1);
		if (willmute < mutationChance){
			muteVal = fRand(-1,1);
			this->chromoWeights[i] = muteVal;
			cout << "\nDebug: Mutation Occurred";
		}

	}
}

GenAlg::GenAlg(NeuralNet &nn){

	mutationChance = Params::mute;
	crossChance = Params::cross;

	population.reserve(populationSize);

	for (int i=0; i<populationSize; i++){
		population.push_back(genome());
		nn.CreateNet();
		population[i].chromoWeights = nn.GetWeights();
	}
}

double GenAlg::fRand(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

vector<genome> GenAlg::cross(genome &g1, genome &g2){
		genome g3;
		genome g4;
		//srand(time(NULL));
		int r,p;
		r = rand()%g1.chromoWeights.size();
		p = g2.chromoWeights.size();
		p = p-1;
		int i;
		for ( i = 0; i < r; i++){
			g3.chromoWeights.push_back(g1.chromoWeights[i]);
			g4.chromoWeights.push_back(g2.chromoWeights[i]);
		}
		for (i = r ; i < p; i++){
			g3.chromoWeights.push_back(g2.chromoWeights[i]);
			g4.chromoWeights.push_back(g1.chromoWeights[i]);
		}
		for (int rs = 0; rs < p; rs++){
			g1.chromoWeights[rs] = g3.chromoWeights[rs];
			g2.chromoWeights[rs] = g4.chromoWeights[rs];
		}
}

genome GenAlg::Choosen(){
	double h = fRand(0,1)*popfitness;
	double cumulativeFit=0;
	for(int index = 0; index<populationSize; index++){
		cumulativeFit += population[index].fitness;

		if(cumulativeFit >= h){return population[index];}

	}

return NULL;
}


vector<genome> GenAlg::selection(){
	vector<genome> pop2;
	popfitness = 0;
	topfit =0;
	// Loop calculates all important fitness related things...
	for (int i =0; i<populationSize; i++){
		popfitness += population[i].fitness;
		if (population[i].fitness > topfit){topfit=population[i].fitness;}
	}
	// for (int i=0; i<populationSize; i++){
	// 	int selection;
	// 	int backup=0;
	// 	r = 0;
	// 	//cout<<"Pop Fit: "<<popfitness<<endl;
	// 	if (popfitness == 0){
	// 		cout<<"PopFitness = 0"<<endl;
	// 		for(selection = 0; backup > 0; selection++){
	// 			backup = rand() % populationSize;
	// 			backup = backup - 1;
	// 		}
	// 	}

	// 	else{
	// 	r = fRand(0,popfitness);
	// 	int counter = 0;
	// 		for (selection=0; r>0; selection++){
	// 			counter++;
	// 			cout<<counter<<endl;
	// 			cout<<"ENTERED LOOP"<<endl;
	// 			r = r - population[selection].fitness;

			//	if (selection>populationSize-1){cout << "\nSelection Error!"; int test; cin>>test; break;}

		//	if (selection>populationSize-1){cout << "\nSelection Error!"; int test; cin>>test;}

		/*
		cout<<"HERE"<<endl;
		cout<<pop2.size()<<endl;
		cout<<i<<endl;
		cout<<population.size()<<endl;
		cout<<selection<<endl;
		cout<<populationSize<<endl;
		*/
		// if(selection-1 == -1 || selection == 10){
		// 	cout<<"Selection = "<<selection<<endl;
		// 	int fuck;
		// 	cin>>fuck;
		// }
		for(int x = 0; x<populationSize; x++){
			pop2.push_back(Choosen());
		}

		//cout<<"HERE2"<<endl;

	return pop2;
}

vector<genome> GenAlg::nextGen(){
	vector<genome> pop3;
	pop3 = selection();
	vector<genome> intermed;
	double q2;
	for (int i = 0; i< populationSize; i++){
		pop3[i].mutate();
		q2 = fRand(0,1);

		//if (q2 < crossChance && i>0){
		//	cout<<"HERE--------------------------------------------------------------"<<endl;
			//cross(pop3[i],pop3[i-1]);
	//	}

	}

	return pop3;
}
