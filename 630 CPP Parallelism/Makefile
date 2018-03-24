STDCPP?=gnu++17
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-variable

make:	Source

Source:	Source.o File.o
		g++ Source.o File.o -lpthread -o Source

clean:
	rm -f Source Source.o File.o
