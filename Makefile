CXX = $(shell wx-config --cxx)

PROGRAM = easyrpg

OBJECTS = $(PROGRAM).o

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX) -c `wx-config --cxxflags` -Wall -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) `wx-config --libs` -Wall

clean:
	rm -f *.o $(PROGRAM)
