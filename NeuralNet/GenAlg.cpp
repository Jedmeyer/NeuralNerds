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




	





<<<<<<< HEAD
=======
void nextGen(int generationSize, int chromolen){
	cout << endl;
	cout << genNum;
	cout << "\nNext Generation...";
	genArr[1] = new chromo*[generationSize];
	cout << "\nGeneration Allocated";
	bool mutate = false;
	bool crossover = false;
	int index=0;
	float r,n,p; //Intermediates for determining odds of mutation and crossover;
	for (int i=0; i<generationSize; i++){
		genArr[genNum][i]= new chromo();
		p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (p < crossChance){
			genArr[genNum][i] = cross(genArr[genNum-1],chromolen);
		}
		else{
			index = selection();
			float *a = new float[chromolen];
			for (int x=0; x<chromolen; x++){
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (r < mutationChance){a[x] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); cout << "Mutation!\n";}
				else{ a[x] = genArr[genNum-1][index]->data[x];}
			}
		genArr[genNum][i] = new chromo(a,genArr[genNum-1][index]->fam);
		}
	}
	genNum++;
>>>>>>> 7d30cdfac4ad3a31f4eb36ce6a4b7ca0ba026965





