
#Driver: Driver.o GenAlg.o NeuralNet.o
#	g++ -g -Wall -std=c++11 -o driver driver.o GenAlg.o NeuralNet.o
#
#driver.o: driver.cpp NeuralNet.h GenAlg.h
#	g++ -g -Wall -std=c++11 -c driver.cpp
#
#NeuralNet.o: NeuralNet.cpp GenAlg.h
#	g++ -g -Wall -std=c++11 -c NeuralNet.cpp
#
#genDriver: GenAlg.o GenAlgDriver.cpp
#	g++ -g -Wall -std=c++11 -o genDriver GenAlg.o GenAlgDriver.cpp
#
#GenAlg.o: GenAlg.cpp NeuralNet.h
#	g++ -g -Wall -std=c++11 -c GenAlg.cpp


C2048: C2048.o Driver.o
	g++ -g -Wall -std=c++11 -o 2048Driver Driver.o

Driver.o: Driver.cpp C2048.h
	g++ -g -Wall -std=c++11 -c Driver.cpp

C2048.o: C2048.h
	g++ -g -Wall -std=c++11 -c C2048.cpp
