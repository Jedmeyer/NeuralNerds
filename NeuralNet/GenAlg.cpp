#include "GenAlg.h"



using namespace std;

genome::genome(){fitness = 0;}

genome::genome(double f1){
	fitness = f1;};

genome::genome(vector<double> w1, double f1){
	chromoWeights = w1;
	fitness = f1;
};
void genome::setfitness(double ft){
	fitness = ft;
};

bool genome::operator <(const genome &g1, const genome &g2){
	return g1.fitness < g2.fitness;
};
void genome::setfitness(double ft){
	fitness = ft;
}


GenAlg::GenAlg(NeuralNet &nn){
	genome.reserve(populationSize);
	
	for (int i=0; i<populationSize; i++){
		nn.CreateNet();
		population[i].chromoWeights = nn.GetWeights();
	}
}
vector<genome> GenAlg::cross(genome &g1, genome &g2){
		genome g3;
		genome g4;
		g3.chromoWeights.reserve(g1.size());
		g4.chromoWeights.reserve(g1.size());
		srand(time());
		int r,p;
		r = rand()%g1.size();
		p = g2.size() - r;
		int i;
		for ( i = 0; i < r; i++){
			g3.chromoWeights[i] = g1.chromoWeights[i];
			g4.chromoWeights[i] = g2.chromoWeights[i];
		}
		for (i = 0 ; i < p; i++){
			g3.chromoWeights[i+r] = g2.chromoWeights[i+r];
			g4.chromoWeights[i+r] = g1.chromoWeights[i+r];
		}
		vector<genome> kross;
		kross[0] = g3;
		kross[1] = g4;
		return kross;


}

vector<genome> GenAlg::selection(){
	vector<genome> pop2;
	pop2.reserve(populationSize);
	popfitness = 0;
	topfit =0;
	double r;
	// Loop calculates all important fitness related things...
	for (int i =0; i<populationSize; i++){
		popfitness += population[i].fitness;
		if (population[i].fitness > topfit){topfit=population[i].fitness;}
	}
	for (int i=0; i<populationSize; i++){
		int selection;
		r = 0;
		srand(time());
		r = rand() % popfitness;
		for (selection=0; r>0; selection++){
			r = r - population[selection].fitness;
			if (selection>populationSize){cout << "\nSelection Error!";break;}
		}
		pop2[i] = population[selection];
	}
	return pop2;
}




	










