
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

Controller:	GenAlg.o Controller.o NeuralNet.o C2048.o Params.o
	g++ -g -Wall -std=c++11 -o NeuralNetFinal GenAlg.o Controller.o NeuralNet.o C2048.o Params.o

Control2048:	C2048.o Controller.o GenAlg.o NeuralNet.o
	g++ -g -Wall -std=c++11 -o Control2048 Controller.o C2048.o GenAlg.o NeuralNet.o

Controller.o:	controller.cpp C2048.h GenAlg.h NeuralNet.h
	g++ -g -Wall -std=c++11 -c controller.cpp

GenAlg.o:	GenAlg.cpp NeuralNet.h Params.h
	g++ -g -Wall -std=c++11 -c GenAlg.cpp

NeuralNet.o:	NeuralNet.cpp
	g++ -g -Wall -std=c++11 -c NeuralNet.cpp

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

NetTest: NeuralNet.o Driver.o Params.o
	g++ -g -Wall -std=c++11 -o NetTest Driver.o NeuralNet.o

Driver.o: Driver.cpp NeuralNet.h
	g++ -g -Wall -std=c++11 -c Driver.cpp

NeuralNet.o:	NeuralNet.cpp Params.h
	g++ -g -Wall -std=c++11 -c NeuralNet.cpp

Params.o: Params.cpp
	g++ -g -Wall -std=c++11 -c Params.cpp
