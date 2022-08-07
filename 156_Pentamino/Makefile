CXX=g++-10
STDCPP?=gnu++2a
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas 
LDFLAGS=-lfmt

make:	Pentamino

Pentamino:	Pentamino.o Piece.o Carre55.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f Pentamino *.o
