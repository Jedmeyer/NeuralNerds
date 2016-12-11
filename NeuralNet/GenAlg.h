
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>


struct genome{
public:
	vector<double> chromoWeights; /**< Array of weights for the entire neural net, serves as ONE member of a generation */
	double fitness;
	genome();
	genome(double f1){fitness = f1;}
	genome(vector <double> w1, double f1);
	bool operator <(const genome &g1, const genome &g2)
};

class GenAlg{
	vector <genome> population;
	double popfitness; /**< Sum of all fitness values in the population */ 
	double topfit; /**< The top fitness in the population of the generation */
	int gnumNeurons =  params::numChromo;
	const int populationSize = params::pop;
	
	/**
	@param pop Population of the generation, Vector of genomes
	@param popfitness Total fitness of the population
	*/

	void cross(vector <genome> pop, double totfitness);
	void mutate(genome g1); /**< Alters the genome of a member of a population to be inherited in the next generation */
	void generate(); /** Starter for the random generation of the population*/


};

