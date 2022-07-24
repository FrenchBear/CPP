CXX=g++-10
STDCPP?=gnu++2a
CXXFLAGS=-Wall -std=$(STDCPP) -Wno-unused-but-set-variable -Wno-unused-variable -Wno-deprecated-declarations -Wno-unknown-pragmas 
ifeq ('$(APPLE)','M1')
LDFLAGS=/opt/homebrew/Cellar/fmt/8.1.1_1/lib/libfmt.a
else
LDFLAGS=/usr/lib/x86_64-linux-gnu/libfmt.a
endif

T=io

make:	$(T)

$(T):	$(T).o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(T) *.o
