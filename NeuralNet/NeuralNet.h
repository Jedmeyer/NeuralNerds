struct Neuron{
	
	/// Number of inputs to the given Neuron 
	int numInputs;

	///Array of weights from each input
	vector<double> vecWeight;

	///contstructor
	Neuron(int nI);
};

struct NeuronLayer{

	///number neurons in this layer
	int numNeurons;

	///layer of neurons
	vector<Neuron> vecNeurons;

	///constructor
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

	NeuralNet();

	void CreateNet();

	// Gets the weight from neural net
	vector<double> GetWeights()const;

	// returns total number of weights in the net
	int GetNumberOfWeights()const;

	// replaces weights w/ new ones;
	int PutWeights(vector<double> &weights);

	// calc outputs from set of inputs;
	vector<double> Update(vector<double> &inputs);

	// sigmoid response curve
	inline double Sigmoid(double activation, double response);

};