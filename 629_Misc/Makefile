CXX=g++-10
STDCPP?=gnu++2a
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas -Wno-psabi
#LDFLAGS=/usr/lib/x86_64-linux-gnu/libfmt.a

T=Source

make:	$(T)

$(T):	$(T).o Shape.o Circle.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(T) *.o
