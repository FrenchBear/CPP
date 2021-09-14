// 102 CPP Dynamic
// An implementation of factorial in C++ at compile-time based on template
// Also show type restictor to limit accepted types from a template
//
// 2017-04-09	PV		Added constexpr version, static_assert, GitHub, Linux support
// 2021-09-14	PV		Visual Studio 2022

#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;


// template-based version
template <int N> struct Factorial
{
	static const int value = N * Factorial<N - 1>::value; // recursive!
};

template <> struct Factorial<0> // required for terminating condition
{
	static const int value = 1;
};


// constepr-based version
constexpr long fact(long n) {
	long res = 1;
	while (n > 1)
		res *= n--;
	return res;
}

void TestFactorial()
{
	int x = Factorial<10>::value;	// 3628800, known at compile time
	cout << "Factorial<10>::value = " << x << endl;
	constexpr int y = fact(10);				// 3628800, also known at compile time
	cout << "fact(10) = " << y << endl << endl;;

	// Check that both are computed at compile-time
	static_assert(fact(5) == Factorial<5>::value, "There is a problem");
}


// Example of template that only accepts float or double
// From http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf
template <typename T> struct restrictor { };
template <> struct restrictor<float> { typedef float result; };
template <> struct restrictor<double> { typedef double result; };

// Can only compute distance on float and double types 
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
	(void)getchar();
#endif
	return 0;
}
