#include "NeuralNet.h"

using namespace std;

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1,1); //doubles from -1 to 1


Neuron::Neuron(int nI) : numInputs(nI+1){


	for(int i=0; i < nI+1; ++i){

		//Set up with random Weight values


		vecWeight.push_back(distribution(generator));

	}
}

NeuronLayer::NeuronLayer(int nNurons,
												 int numInputsPerNeuron) : numNeurons(nNurons){


	for(int i = 0; i < nNurons; ++i){

		//Call Constructor for each Neuron

		vecNeurons.push_back(Neuron(numInputsPerNeuron));

	}

}

////////////////////////////--Defualt Constructor--////////////////////////////
// Grabs Params.ini variables
///////////////////////////////////////////////////////////////////////////////

NeuralNet::NeuralNet(){

	numInputs           =  Params::numInputs;
	numOutputs	        =  Params::numOutputs;
	numHiddenLayers     =  Params::numHidden;
	neuronsPerHiddenLyr =  Params::neuronsPerHiddenLayer;

	CreateNet();
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
	  vecLayers.push_back(NeuronLayer(numOutputs, numInputs));
  }
}

////////////////////////////--Get Weights --////////////////////////////
// Returns a vector containing the weights
////////////////////////////////////////////////////////////////////////

vector<double> NeuralNet::GetWeights() const{

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

int NeuralNet::GetNumberOfWeights() const{

	// # weights
	int weights = 0;

	for(int i = 0; i < numHiddenLayers +1; ++i){

		//each neuron
		for(int j = 0; j < vecLayers[i].numNeurons; ++j){

			//each weights
			for(int k = 0; k < vecLayers[i].vecNeurons[j].numInputs; ++k){

				//add to weights
				weights++;
				//cout<<"Here: "<<weights<<endl;
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

	if(inputs.size() != this->numInputs){
		cout<<numInputs<<endl;
		//Return empty vector if incorrect
		cout<<"Incorrect Size"<<endl;
		return outputs;
	}

	//each layer
	for(int i = 0; i < numHiddenLayers +1; ++i){

		if(i>0){
			inputs = outputs;
		}

		outputs.clear();

		//Counts for iterations
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
				totInput +=vecLayers[i].vecNeurons[j].vecWeight[k] * inputs[weight];
				weight++;


			}

			totInput += vecLayers[i].vecNeurons[j].vecWeight[numInputs-1] * Params::bias;

			//Store the output as generated
			outputs.push_back(totInput);

			weight = 0;


		}
	}

	return outputs;
}
