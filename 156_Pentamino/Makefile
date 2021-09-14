STDCPP?=gnu++17
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas

make:	Pentamino

Pentamino:	Pentamino.o Piece.o Carre55.o

clean:
	rm -f Pentamino *.o
