CPP=g++
CXXFLAGS=-Wall -std=gnu++17

make:	pcpp

pcpp:		pcpp.o
		g++ -o $@ $^

pcpp.o:	*.h

clean:	
		rm -f pcpp.o pcpp
