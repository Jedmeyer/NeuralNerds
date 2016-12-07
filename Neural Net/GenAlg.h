
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>

class genome{
public:
	int id;
	int totalSpecs;
	genome(int gid);
};
class chromo{
public:
	float* data; // instead of using the bitsets, each "gene" will be a float from 0-1;
	genome* fam;
	int gid;
	int specid;
	double fitness;
	void inherit(chromo *parent, bool mute);
	//Used for initial generate function to make the first set of chromosomes.
	chromo(){;}
	chromo(float* in){
		data = in;
	}
	//Used for mutations to define a new species of chromosome
	chromo(float* in, genome *parent){
		data = in;
		fam = parent;


	}
};
class generation{
public:
	int genSize;
	chromo** genData;
	void generate(int gensz, int chromolen);
	double selection();

	generation(int gensz, int chromolen);
};

chromo* cross(generation, int);
void nextGen(int generationSize, int chromolen);
void calculate(chromo* c);

int genomeNum;
chromo ***genArr;
int genNum;
