

#include "GenAlg.h"
using namespace std;

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
void generate(int gensz, int chromolen, int totalGens){
	cout << "\nTotal number of Generations\n";
	cout << totalGens;
	genArr = new chromo**[totalGens];
	genArr[0] = new chromo*[gensz];
	for (int i = 0; i<gensz; i++){

		genArr[genNum][i] = new chromo ();
		genArr[genNum][i]->data = new float[chromolen];
		float r = 0;
		for (int x=0; x<chromolen;x++){
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			cout << endl << r;
			genArr[genNum][i]->data[x] = r;
			// genData[i]->data[x] = r;
			;
		}

		genArr[0][i]->gid = genomeNum;
		genArr[0][i]->fam = new genome(genomeNum);

	}
	genNum++;
	cout << genNum;
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




}

int main(){
	cout << endl;
	cout << "Compilation complete.\n";
	generate(10,2,10);
	genArr[1] = '\0';
	cout << endl;
	cout << genArr[1];
	genArr[1] = new chromo*[10];
	// cout << endl << "First gen complete. Continuing...";
 // 	nextGen(10,10);
	// for (int i = 0; i<10;i++){ delete[] genArr[i];}

	//Deallocating genArr;
	delete[] genArr[1];
	delete[] genArr;
 }
