#ifndef NEURALNET_H
#define NEURALNET_H

#include <iostream>
#include "Params.h"
#include <vector>
#include <random>
#include <time.h>
#include <cstdlib>

using namespace std;

struct Neuron{

	/// Number of inputs to the given Neuron
	int numInputs;

	///Array of weights from each input
	vector<double> vecWeight;

	/** Neuron constructor
	@param nI Number of Inputs
	*/
	Neuron(int nI);
};

struct NeuronLayer{

	///number neurons in this layer
	int numNeurons;

	///layer of neurons
	vector<Neuron> vecNeurons;

	/** NeuronLayer Constructor
	@param nNurons Number of Nurons
	@param numinputsPerNeuron
	*/
	NeuronLayer(int nNurons, int numInputsPerNeuron);
};


class NeuralNet{

private:

	int numInputs;

	int numOutputs;

	int numHiddenLayers;

	int neuronsPerHiddenLyr;

	//Storage for Layers of nerons, includes output
	vector<NeuronLayer> vecLayers;

public:

	// std::default_random_engine generator;
	// std::uniform_real_distribution<double> distribution(-1,1); //doubles from -1 to 1

	NeuralNet();

	void CreateNet();

	// Gets the weight from neural net
	vector<double> GetWeights()const;

	// returns total number of weights in the net
	int GetNumberOfWeights()const;

	// replaces weights w/ new ones;
	void PutWeights(vector<double> &weights);

	// calc outputs from set of inputs;
	vector<double> Update(vector<double> &inputs);

	// sigmoid response curve
	//inline double Sigmoid(double activation, double response);

};

#endif
