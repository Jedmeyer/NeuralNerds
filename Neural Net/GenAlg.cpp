

#include "GenAlg.h"

genome::genome(int gid){
	id = gid;
	genomeNum++;
}


void chromo::inherit(chromo *parent, bool mute){
	gid = parent->fam->id;
	if (mute){
		specid = parent->fam->totalSpecs;
		parent->fam->totalSpecs++;
	}
}


//Generate builds the FIRST generation of the algorithm.
//Hence, it has entirely unique genome becuase the chromosomes are independently
//generated.
void generate(int gensz, int chromolen){
	genArr[0] = new chromo*[gensz];
	for (int i = 0; i<gensz; i++){

		genArr[genNum][i] = new chromo ();
		genArr[genNum][i]->data = new float[chromolen];
		float r = 0;
		for (int x=0; i<chromolen;i++){
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			genArr[genNum][i]->data[x] = r;
			// genData[i]->data[x] = r;
			;
		}

		genArr[0][i]->gid = genomeNum;
		genArr[0][i]->fam = new genome(genomeNum);

	}
	genNum++;



}




chromo* cross(chromo **a, int chromolen){
	int r = (int)(rand()%genSize);
	chromo* g;
	chromo* b;
	g = new chromo();
	b = new chromo();
	g->data = a[r]->data;
	r = (int)(rand()%genSize);
	b->data = a[r]->data;
	float* arr;
	arr = new float[chromolen];

	int c = (int)(rand()%chromolen);
	int d = chromolen - c;
	int len;
	for (len=0; len<c;len++){
		arr[len] = g->data[len];
	}
	for (int i=c+1; i<d; i++){
		arr[len+i] = b->data[i];
	}
	float *rv = arr;
	chromo* crossed = new chromo(rv);
	return crossed;
}

void calculate(chromo* c){
	int len;
	for (len = 0; c->data != '\0'; len++);
	int sum=0;
	for (int i=0; i<len; i++){
		sum += c->data[i];
	}
	c->fitness = sum;
}





double selection(){
	double tf=0;
	for (int i=0; i<genSize; i++){
		calculate(genArr[genNum-1][i]);
		tf += genArr[genNum-1][i]->fitness;
	}
	int selection;

	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	for (selection =0; r>0; selection++){
		r = r - genArr[genNum-1][selection]->fitness;
	}
	return selection;
}
void nextGen(int generationSize, int chromolen){
	genArr[genNum] = new chromo*[generationSize];
	bool mutate = false;
	bool crossover = false;
	int index=0;
	for (int i=0; i<generationSize; i++){
		index = selection();
		float *a = new float[chromolen];
		for (int x=0; x<chromolen; x++){
			a[x] = genArr[genNum-1][index]->data[x];
		}
		genArr[genNum][i] = new chromo(a,genArr[genNum-1][index]->fam);
	}
	genNum++;




}