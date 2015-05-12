CC = g++
CC_FLAGS = -Wall -std=c++11

SOURCES = src/main.cpp src/Literal.cpp src/Clause.cpp src/ConjunctiveNormalForm.cpp src/Netlist.cpp src/Net.cpp \
src/Gate.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o sat

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS)
