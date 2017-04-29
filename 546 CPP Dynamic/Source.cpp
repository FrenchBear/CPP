// CPP Factorial
// An implementation of factorial in C++ at compile-time based on template
// 2017-04-09	PV	Added constexpr version, GitHub, Linux support

#include <stdio.h>
#include <iostream>

using namespace std;


template <int N> struct Factorial
{
	static const int value = N * Factorial<N - 1>::value; // recursive!
};

template <> struct Factorial<0> // required for terminating condition
{
	static const int value = 1;
};

void TestFactorial()
{
	int x = Factorial<10>::value; // 3628800, known at compile time
	cout << x << endl;
}



template <typename T> struct restrictor { };
template <> struct restrictor<float> { typedef float result; };
template <> struct restrictor<double> { typedef double result; };

template <typename T> typename restrictor<T>::result distance(T a1, T a2, T b1, T b2) {
	T tmp1 = a1 - b1;
	T tmp2 = a2 - b2;
	return std::sqrt(tmp1*tmp1 + tmp2*tmp2);
}


int main() {
	TestFactorial();

	double x1 = 0.0, y1 = 0.0, x2 = 4.0, y2 = 3.0;
	double d = distance<double>(x1, y1, x2, y2);
	cout << d << endl;

#ifdef _WIN32
	cout << "\n(Pause) ";
	getchar();
#endif
	return 0;
}
