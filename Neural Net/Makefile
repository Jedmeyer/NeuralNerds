
driver: driver.o GenAlg.o NeuralNet.o
	g++ -g -Wall -std=c++11 -o driver GenAlg.o NeuralNet.o

driver.o: driver.cpp NeuralNet.h GenAlg.h
	g++ -g -Wall -std=c++11 -c driver.cpp

NeuralNet.o: NeuralNet.cpp GenAlg.h
	g++ -g -Wall -std=c++11 -c NeuralNet.cpp

GenAlg.o: GenAlg.cpp NeuralNet.h
	g++ -g -Wall -std=c++11 -c GenAlg.cpp