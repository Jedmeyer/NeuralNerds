

#include "GenAlg.h"



void chromo::inherit(chromo *parent, bool mute){
	gid = parent.id;
	if (mute){
		specid = parent->fam.totalSpecs;
		parent->fam.totalSpecs++;
	}
}

void generate(int gensz){
	genData = new chromo*[gensz];



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