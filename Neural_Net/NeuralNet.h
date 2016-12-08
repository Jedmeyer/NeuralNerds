struct Neuron{
	//Number of inputs to the given Neuron
	int numInputs;

	//Array of weights from each input
	vector<double> vecWeight;

	//contstructor
	Neuron(int nI);
};

struct NeuronLayer{

	//number neurons in this layer

	int numNeurons;

	//layer of neurons

	vector<Neuron> vecNeurons;

	//constructor
	NeuronLayer(int nNurons, int numInputsPerNeuron);
};


class NeuralNet{

};