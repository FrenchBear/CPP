STDCPP?=gnu++17
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable

make:	Source

Source:	Source.o Circle.o Shape.o
		g++ Source.o Circle.o Shape.o -o Source

Circle.o:	Circle.cpp Circle.h
			g++ $(CXXFLAGS) -c Circle.cpp

Shape.o:	Shape.cpp Shape.h
			g++ $(CXXFLAGS) -c Shape.cpp

clean:
	rm -f Source Source.o Circle.o Shape.o
