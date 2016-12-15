#ifndef GENALG_H
#define GENALG_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <vector>
#include "NeuralNet.h"
#include "Params.h"
using namespace std;


struct genome{
public:
	double mutationChance;
	double crossChance;
	vector<double> chromoWeights; /**< Array of weights for the entire neural net, serves as ONE member of a generation */
	double fitness;
	genome();
	genome(double f1);
	genome(vector <double>, double);
	bool operator <(const genome&);
	void setfitness(double ft);/** < Sets the fitness of a specific genome structure */
	void mutate(); /**< Alters the genome of a member of a population to be inherited in the next generation */
	double fRand(double, double);

};

class GenAlg{
public:
	double mutationChance;
	double crossChance;
	vector<genome> population;
	double popfitness; /**< Sum of all fitness values in the population */
	double topfit; /**< The top fitness in the population of the generation */
	int gnumNeurons =  Params::numChromo;
	const int populationSize = Params::pop;



	/**
	@param pop Population of the generation, Vector of genomes
	@param popfitness Total fitness of the population
	*/

	/**
	BEFORE SELECTION CAN BE CALLED, A FITNESS
	MUST BE ASSIGNED TO EACH MEMBER OF THE POPULATION
	**/

	double fRand(double, double);

	void cross(genome&, genome&); //Should return cross of two genome split somewhere down the doubles array
	GenAlg(NeuralNet&); /**< Constructor, also starter for the random generation of the population*/
	vector<genome> selection(); /**< Selection process should return a vector of ALL THE SELECTED genomes to be set equal to the current generation */
	vector<genome> nextGen();
	genome Choosen();

};
/*
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
*/


#endif
