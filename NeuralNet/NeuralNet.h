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
	///Number of input neurons for the net
	int numInputs;

	///Number of output neurons in the net
	int numOutputs;

	///Number of hidden layers
	int numHiddenLayers;

	/// Neurons for every hidden layer
	int neuronsPerHiddenLyr;

	///Storage for Layers of nerons, includes output
	vector<NeuronLayer> vecLayers;

public:
	///Neural Net Construcor, Grabs from Params.ini
	NeuralNet();

	///Creates a Neural
	void CreateNet();

	/** Gets the weights from neural net
	@return vector of all weights in order
	*/
	vector<double> GetWeights()const;

	/** returns total number of weights in the net
	@return number of weights in the neural net
	*/
	int GetNumberOfWeights()const;

	/** replaces weights w/ new ones;
	@param weights vector of weights to set the neural net to
	*/
	void PutWeights(vector<double> &weights);

	/** calc outputs from set of inputs, main function of neural net
	@param inputs input layer numbers
	@return output layer calculations
	*/
	vector<double> Update(vector<double> &inputs);

};

#endif
