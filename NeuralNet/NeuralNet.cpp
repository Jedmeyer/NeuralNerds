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

////////////////////////////--Defualt Constructor--////////////////////////////
// Grabs Params.ini variables
///////////////////////////////////////////////////////////////////////////////

NeuralNet::NerualNet(){
	numInputs           =  Params::numInputs;
	numoutputs	        =  Params::numOutputs;
	numHiddenLayers     =  Params::numHiddenLayers;
	neuronsPerHiddenLyr =  Params::numHiddenLayers;
}

////////////////////////////--Creating the Net--////////////////////////////
// Sets up Net with random Weights -1 -> 1
////////////////////////////////////////////////////////////////////////////

void NeuralNet::CreateNet(){
	//create the layers of the network
	if (numHiddenLayers > 0){
		//create first hidden layer
	  vecLayers.push_back(NeuronLayer(neuronsPerHiddenLyr, numInputs));

    for (int i=0; i<numHiddenLayers-1; ++i){

			vecLayers.push_back(NeuronLayer(neuronsPerHiddenLyr,
                                         neuronsPerHiddenLyr));
    }

    //create output layer
	  vecLayers.push_back(NeuronLayer(numOutputs, neuronsPerHiddenLyr));
	}

  else{
	  //create output layer
	  vecLayers.push_back(SNeuronLayer(numOutputs, numInputs));
  }
}

////////////////////////////--Get Weights --////////////////////////////
// Returns a vector containing the weights
////////////////////////////////////////////////////////////////////////

vector<double> NeuralNet::GetWeights(){

	//return vector
	vector<double> weights;

	//each layer
	for(int i = 0; i < numHiddenLayers + 1; ++i){

		//each neuron
		for(int j = 0; j < vecLayers[i].numNeurons; ++j){

			//each weight
			for(int k = 0; k < vecLayers[i].vecNeurons[j].numInputs; ++k){

				//add Weight to vec of weights
				weights.push_back(vecLayers[i].vecNeurons[j].vecWeight[k]);
			}
		}
	}
	return weights;
}

////////////////////////////--Put Weights --////////////////////////////
// Returns a vector containing the weights
////////////////////////////////////////////////////////////////////////

void NeuralNet::PutWeights(vector<double> &weights){

	// weight position
	int weight = 0;

	//each layer
	for(int i = 0; i < numHiddenLayers +1; ++i){

		//each neuron
		for(int j = 0; j < vecLayers[i].numNeurons; ++j){

			//each weights
			for(int k = 0; k < vecLayers[i].vecNeurons[j].numInputs; ++k){

				//set weights
				vecLayers[i].vecNeurons[j].vecWeight[k] = weights[weight++];

			}
		}
	}
	return;
}

///////////////////////--Get Number Of Weights --///////////////////////
// Returns an int of # of weights total
////////////////////////////////////////////////////////////////////////

int NeuralNet::GetNumberOfWeights(){

	// # weights
	int weights = 0;

	for(int i = 0; i < numHiddenLayers +1; ++i){

		//each neuron
		for(int j = 0; j < vecLayers[i].numNeurons; ++j){

			//each weights
			for(int k = 0; k < vecLayers[i].vecNeurons[j].numInputs; ++k){

				//add to weights
				weights++;

			}
		}
	}
	return weights;
}

////////////////////////////-- Update --////////////////////////////
// Send it inputs, returns outputs
// Main function of the neural net
////////////////////////////////////////////////////////////////////

vector<double> NeuralNet::Update(vector<double> &inputs){

	vector<double> outputs;

	int weight = 0;

	if(inputs.size() != NumInputs){
		//Return empty vector if incorrect
		return outputs;
	}

	//each layer
	for(int i = 0; i < numHiddenLayers +1; ++i){

		if(i>0){
			inputs = outputs;
		}

		outputs.clear();

		weight = 0;

		//each neuron
		for(int j = 0; j < vecLayers[i].numNeurons; ++j){

			//stores the total Input later
			double totInput = 0;

			//Simplify later lines
			int numInputs = vecLayers[i].vecNeurons[j].numInputs;


			//each weights
			for(int k = 0; k < numInputs - 1; ++k){

				// Weights * inputs
				totInput +=vecLayers[i].vecNeurons[j].vecWeight[k] * inputs[weight++];
			}

			//add bias
			totInput += vecLayers[i].vecNeurons[j].vecWeight[numInputs-1] * Params::bias;

			//Store the output as generated
			outputs.push_back(totInput);

			weight = 0;
		}
	}
	return outputs;
}
