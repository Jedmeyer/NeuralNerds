
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

Control2048:	C2048.o Controller.o
	g++ -g -Wall -std=c++11 -o Control2048 Controller.o C2048.o

Controller.o:	Controller.cpp C2048.h
	g++ -g -Wall -std=c++11 -c Controller.cpp

C2048: C2048.o Driver.o
	g++ -g -Wall -std=c++11 -o C2048 Driver.o C2048.o

Driver.o: Driver.cpp C2048.h
	g++ -g -Wall -std=c++11 -c Driver.cpp

C2048.o: C2048.cpp
	g++ -g -Wall -std=c++11 -c C2048.cpp


Params: Params.o Driver.o
	g++ -g -Wall -std=c++11 -o ParamTest Driver.o Params.o

Driver.o: Driver.cpp Params.h
	g++ -g -Wall -std=c++11 -c Driver.cpp

Params.o: Params.cpp
	g++ -g -Wall -std=c++11 -c Params.cpp
