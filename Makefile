CXX = g++
CXXFLAGS = -Wall -Wextra -I inc

SRC = src/image_pgm.cpp
INC = inc/image_pgm.hpp
OBJ = $(subst src,obj,$(patsubst %.cpp,%.o,$(SRC)))

.PHONY: all clean purge test-pgm

all: a.out

a.out: obj/test_image_pgm.o $(OBJ)
	$(CXX) -o $@ $^ 

test-pgm: a.out
	./a.out [ImagePGM]

obj/%.o: src/%.cpp $(INC)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

obj/%.o: test/%.cpp $(INC)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	find . -name "*.o" -delete

purge: clean
	find . -name "*.out" -delete
