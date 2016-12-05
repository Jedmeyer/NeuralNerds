
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <math.h>

class genome{
	int id;
	int totalSpecs;
}
class chromo{
public:
	float** data; // instead of using the bitsets, each "gene" will be a float from 0-1;
	genome* fam;
	int gid;
	int specid;
	void inherit(chromo *parent, bool mute);
	chromo* cross(chromo** gen);
	chromo(float** in)	{
		data = in;
	}
	chromo(float** in, genome *parent){
		data = in;
		fam = parent;


	}
}
class generation{
	int genSize;
}


void generate();
void nextGen();
