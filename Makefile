CXX=g++-10
STDCPP?=gnu++2a
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas -Wno-psabi
ifeq ('$(APPLE)','M1')
LDFLAGS=/opt/homebrew/Cellar/fmt/8.1.1_1/lib/libfmt.a
else
LDFLAGS=-lfmt
endif

T=Source

make:	$(T)

#$(T):	$(T).o module.o
#	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(T) *.o
