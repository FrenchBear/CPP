CXXFLAGS=-Wall -std=gnu++17 -Wno-reorder

make:	Source

Source:	Source.o
	g++ Source.o -o Source

Source.o:	Source.cpp InfInt.h
	g++ $(CXXFLAGS) -c Source.cpp -o Source.o
