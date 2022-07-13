CXX=g++-10
STDCPP?=gnu++2a
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas 
LDFLAGS=/usr/lib/x86_64-linux-gnu/libpthread.so

T=Source

make:	$(T)

$(T):	$(T).o File.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(T) *.o
