STDCPP?=gnu++17
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-reorder

make:	Source

Source:	Source.o
	g++ Source.o -o Source

Source.o:	Source.cpp InfInt.h
	g++ $(CXXFLAGS) -c Source.cpp -o Source.o

clean:
	rm -f Source Source.o
