OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

proto-graph: proto-graph.o
	g++ $(OPTS) -o proto-graph proto-graph.o $(LIBS)

proto-graph.o: proto-graph.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c proto-graph.cpp

clean:
	rm -f *.o proto-graph
