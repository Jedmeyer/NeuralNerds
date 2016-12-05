

#include "GenAlg.h"

genome::genome(int gid){
	id = gid;
	genomeNum++;
}


void chromo::inherit(chromo *parent, bool mute){
	gid = parent.id;
	if (mute){
		specid = parent->fam.totalSpecs;
		parent->fam.totalSpecs++;
	}
}


//Generate builds the FIRST generation of the algorithm.
//Hence, it has entirely unique genome becuase the chromosomes are independently
//generated.
void generate(int gensz){
	genData = new chromo*[gensz];
	for (int i = 0; i<genSize; i++){
		genData[i] = new chromo
		int gid = genomeNum;
		fam = new genome(genomeNum);

	}



}




chromo* chromo::cross(chromo** gen){
	int r = (int)(rand()%genSize);
	chromo* a,b;
	a = gen[r];
	r = (int)(rand()%genSize);
	b = gen[r];
}
generation::generation(int gensz){
	genSize = gensz;
	generate(genSize);

}