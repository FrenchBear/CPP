STDCPP?=gnu++17
CXXFLAGS=-Wall -std=$(STDCPP)

make:	Source

Source:	Source.o Complex.o
		g++ Source.o Complex.o -o Source

clean:
	rm -f Source Source.o Complex.o
