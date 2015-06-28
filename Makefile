CC = g++
DOC = doxygen
LD_FLAGS = -lpthread
CC_FLAGS = -Wall -std=c++11 -O3 -g
PROJECT = sat

SOURCES = src/main.cpp src/Literal.cpp src/Clause.cpp src/ConjunctiveNormalForm.cpp src/Netlist.cpp src/Net.cpp \
src/Gate.cpp src/Solver.cpp
OBJECTS = $(SOURCES:.cpp=.o)


compile: $(OBJECTS)
	$(CC) $(LD_FLAGS) $(OBJECTS) -o sat

run: compile
	./$(PROJECT)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) -o $@ $<


doc:
	$(DOC) edat.doxyfile

clean:
	rm -f $(OBJECTS)
