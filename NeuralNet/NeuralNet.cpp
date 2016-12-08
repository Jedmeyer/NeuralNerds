#include <iostream>
#include "NeuralNet.h"
#include <vector>
#include <random>

using namespace std;



Neuron::Neuron(int nI) : numInputs(nI+1){


	for(int i=0; i < nI+1; ++i){

		//Set up with random Weight values

		vecWeight.push_back(RandomClamped());

	}
}


NeuronLayer::NeuronLayer(int nNurons, int numInputsPerNeuron) : numNeurons(numNeurons){


	for(int i = 0; i < nNurons; ++i){

		//Call Constructor for each Neuron
		
		vecNeurons.push_back(Neuron(numInputsPerNeuron));
	}
}

vector<double> NeuralNet::Update(vector<double> &inputs){

	// stores result outputs from each layer
	vector<double> outputs;

	int weight = 0;

	// safety check: make sure we have the correct # of inputs
	if(inputs.size() != NumInputs){
		// return empty vector if incorrect
		return outputs;
	}

	// For each layer ( are there for each loops in c++?)

	for( int i = 0; i < numHiddenLayers+1; ++1){

		if(i>0){
			inputs = outputs;
		}

		outputs.clear();

		weight = 0;

		for(int j = 0; j < vecLayers[i].numNeurons; ++j)
		{
			double netinput = 0;

			int NumInputs = vecLayers[i].vecNeurons[j].NumInputs;

			for(int k = 0; k < NumInputs-1; ++k){

				netinput += vecLayers[i].vecNeurons[j].vecWeight[k] * inputs[weight++];
				
			}

			// add parameter bias ->
			netinput += vecLayers[i].vecNeurons[j].vecWeight[NumInputs-1] *  ; //add bias from params here//

			outputs.push_back(Sigmoid(netinput,  )) //Add activation from params
		}
	}

	

}

double NeuralNet::Sigmoid(double netinput, double response){

	return ( 1 / ( 1 + exp( -netinput / response)));
}