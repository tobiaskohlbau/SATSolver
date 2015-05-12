CC = g++
DOC = doxygen
CC_FLAGS = -Wall -std=c++11 -O3
PROJECT = sat

SOURCES = src/main.cpp src/Literal.cpp src/Clause.cpp src/ConjunctiveNormalForm.cpp src/Netlist.cpp src/Net.cpp \
src/Gate.cpp
OBJECTS = $(SOURCES:.cpp=.o)


compile: $(OBJECTS)
	$(CC) $(OBJECTS) -o sat

run: compile
	./$(PROJECT)


%.o: %.cpp
	$(CC) -c $(CC_FLAGS) -o $@ $<


doc:
	$(DOC) edat.doxyfile

clean:
	rm -f $(OBJECTS)
