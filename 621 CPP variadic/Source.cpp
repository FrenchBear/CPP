// CPPVariadic
// Example of variadic template in C++
// https://en.wikipedia.org/wiki/Variadic_template
// 2017-03-17	PV

#include <iostream>
#include <string>
#include <complex>
#include <chrono>
#include <functional>

using namespace std;
typedef complex<double> cplx;


void process(int i) {
	cout << "int " << i << endl;
}

void process(double d) {
	cout << "double " << d << endl;
}

void process(char c) {
	cout << "char " << c << endl;
}

void process(const char *s) {
	cout << "const char* " << s << endl;
}

void process(string s) {
	cout << "string " << s << endl;
}

void process(cplx z) {
	cout << "complex (" << z.real() << ", " << z.imag() << ")" << endl;
}

void process(chrono::duration<long long, milli> d) {
	cout << "duration(ms) " << d.count() << endl;
}

void process(std::function<int(int, int)> f) {
	cout << "function<int(int, int)>, call on (2,3): " << f(2, 3) << endl;
}


void func() {} // termination version

template<typename Arg1, typename... Args>
void func(const Arg1& arg1, const Args&... args)
{
	process(arg1);
	func(args...);
}


// Functor object
struct Plus1 {
	template <typename T, typename U>
	auto operator()(T&& t, U&& u) const {
		return forward<T>(t) + forward<U>(u);
	}
};



int main() {
	func(12, "Hello", "world"s, 2.0i + 3.0, sqrt(2), 140ms, 
		Plus1{}, [](int x, int y) {return x * y; });

	cout << "\n(Pause)";
	cin.get();
}
