
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>
#include <iostream>

class genome{ /**< Class genome tracks the inheritance of the chromosomes for each generation */
public:
	int id; /**< A number defining the genomic ID*/
	int totalSpecs;/**< Total number of species in the genome. Increases with each mutation. */
	genome(int gid); /**< Creates a genome with the specific genomic ID */
};
class chromo{
public:
	float* data; /**< Pointer to the chromosmal Data*/
	genome* fam;/**<Pointer to the genome the chromosome is a part of*/
	int gid;/**< Family's genomic ID*/
	int specid; /**< Chromosome's species ID*/
	double fitness;/**< Chromosome's fitness score */
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

void generate(int gensz, int chromolen);
double selection();
chromo* cross(chromo**, int);
void nextGen(int generationSize, int chromolen);
void calculate(chromo* c);
