CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=main
SRCS= starwars.cpp gl_framework.cpp shader_util.cpp camera.o humanoid.o hierarchy_node.o
INCLUDES=gl_framework.hpp shader_util.hpp starwars.hpp hierarchy_node.hpp

all: humanoid camera main

humanoid: humanoid.hpp humanoid.cpp
	g++ -c humanoid.cpp

camera: camera.cpp camera.hpp
	g++ -c camera.cpp

hierarchy_node: hierarchy_node.cpp hierarchy_node.hpp
	g++ -c hierarchy_node.cpp

main: $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)
	rm -f *~ *.o
	./main
clean:
	rm -f *~ *.o $(BIN)
