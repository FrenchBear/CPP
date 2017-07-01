// 103 CPP 14
// Play with new C++ 14 features
//
// 2016-09-14	PV
// 2017-02-11	PV	Continue in VS2017, much better support!
// 2017-03-18	PV	const char* specialization of pi templace, myPow constexpr function
// 2017-04-29	PV	GitHub and Linux

#include <iostream>
#include <vector>
#include <list>
#include <memory>		// make_unique
#include <chrono>
#include <complex>
#include <functional>

using namespace std;


// Constructors can be constexpr
template<typename T>
class MyTemplatedClass {
public:
	constexpr MyTemplatedClass(int value);
};

template<typename T>
constexpr MyTemplatedClass<T>::MyTemplatedClass(int value)
{
}

template<typename T>
constexpr MyTemplatedClass<T> my_const = MyTemplatedClass<T>(123);

auto my_const_1 = my_const<vector<long double>>;
auto my_const_2 = MyTemplatedClass<vector<short>>(14);



// Can use templates to define constants
template<typename T>
constexpr T pi = T(3.141592653589793238462643383);

// Usual specialization rules apply:
template<>
constexpr const char* pi<const char*> = "pi";


// Variadic templates...
template<template<typename...> class Seq>
Seq<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };


// "Official" C++ 14 deprecated attribute
[[deprecated]] void f() {}
[[deprecated("cette fonction est depreciee")]] void g() {}



// do not need constexpr, a const can be initialized using this function
int factorial(int n)
{
	return n <= 1 ? 1 : (n * factorial(n - 1));
}

const int f5 = factorial(5);



// int, for, if are accepted in VS 2017 constexpr functions (but rejected by VS 2015)
constexpr int min(std::initializer_list<int> xs) {
	int min = std::numeric_limits<int>::max();
	for (int x : xs) {
		if (x < min) {
			min = x;
		}
	}
	return min;
}


// Just to use constexpr with a template
template <typename Tint>
static constexpr Tint myPow(Tint x, int p)
{
	if (p == 0) return (Tint)1;
	if (p == 1) return x;

	Tint tmp = myPow(x, p / 2);
	return (p % 2 == 0) ? tmp*tmp : x*tmp*tmp;
}

auto const f5b = myPow(10ll, 13);


// Template use auto and forward return type
template<typename LHS, typename RHS>
auto add(LHS lhs, RHS rhs) -> decltype(lhs + rhs) {
	return lhs + rhs;
}


// Actually in C++14 return type is not mandatory if inferred from return statements
template<typename LHS, typename RHS>
auto add2(LHS lhs, RHS rhs) {
	return lhs + rhs;
}

int two = 2;
int&& foo() { return (int &&)two; }


// operator ""
class my_class {
	char value{};
public:
	my_class(char c) : value{ c } {
	}
};

/*constexpr*/ my_class operator"" _mc(char c) {
	return my_class{ c };
}


class MyClass {
public:
	int i;

	MyClass() = default;

	MyClass(int x) : i(x) {}

	MyClass(initializer_list<int> args) :i(0) {
		for (auto x : args)
			cout << x << " ";
	}

	enum WeekEndDays
	{
		Saturday,
		Sunday
	};
};


constexpr int Somielle(int i) {
	enum Answers { Yes, No, Maybe };

	int s = 0;
	while (i > 0)
		s += i--;
	return s;
}


enum Color {
	Bleu,
	Blanc,
	Rouge = Somielle(5)
} MyColor, *MyColorPtr, &MyColorRef = MyColor, &&MyColorRefRef = Blanc;


enum class Speed {
	Slow,
	Medium,
	Fast
} MySpeed, *MySpeedPtr;


struct Point {
	int p, q;
	Point(int x, int y) : p(x), q(y) {}
};


union Mix {
	char c[4]; // 4 bytes 
	struct { short hi, lo; } s; // 4 bytes 
	int i; // 4 bytes 

	void Hello() {
		cout << "Hello\n";
		f = 3.14f;
	}

private:
	float f;		// Albeit private, still a union "supperposed" member
} m;



template <typename A>
void fooA(std::unique_ptr<A> a, std::unique_ptr<A> b)
{

}



int main() {
	auto const piD = pi<double>;
	auto const piF = pi<float>;
	auto const piI = pi<int>;			// piI == 3
	auto const piS = pi<const char*>;	// piS == "pi"

	MyTemplatedClass<int> at(2);

	auto x = my_const<double>;

	cout << "Hello\n";
	cout << piD << endl;
	cout << piF << endl;
	cout << piI << endl;
	cout << piS << endl;

	const int million = 1'000'000'000;
	const int cent_soixante_dix = 0b0000'0000'1010'1010;


	// Uncomment it causes compiler internal error in VS2015, not in VS15
	auto vec = primes<std::vector>;
	auto list = primes<std::list>;

	// Cause compilation error in VS (deprecated), while this should be a warning...
	// Found the problem: caused by option SDL checks (/sdl) that was set for some reason (it's not the default)
	// with g++, f is not reported as deprecated but g is...
	f();
	g();

	constexpr int vmin = min({ 1, 3, -2, 4 });


	int i = 0;
	double k = 2.0;
	decltype(k) j = i + 2; // j sera du même type que k, donc double.


	auto i1 = add(1, 1);   // int
	auto j1 = add(1, 1.0); // double

	// No type declaration with -> for a lambda
	auto fn = [](int rhs, int lhs) { return rhs + lhs; }; // ok 
	auto sn = fn(2, 3);

	const int i3{ 12 };
	decltype(i3) j3 = i3;
	//j3 += 34; // error: read-only variable is not assignable

	int&& foo();
	auto i4 = foo();            // int
	decltype(foo()) j4 = foo(); // int&&
	decltype(auto) k4 = foo();	// int&&

	// Template ??
	auto add5 = [](auto a, auto b) {return a + b; };

	auto a51 = add5(2, 3);
	auto a52 = add5(2, 3.0);
	auto a53 = add5(2.0f, 3.0f);

	// création d'une valeur
	auto f6 = [i = 5](int j) { return i * j; };


	auto x1 = 'p'_mc; // type my_class


	fooA(std::make_unique<my_class>('e'), std::make_unique<my_class>('f'));


	// New initialization 
	MyClass* a = new MyClass();
	MyClass& b = *new MyClass();

	MyClass c{ 1,2,3,4,5 };		// ctor initializer_list
	MyClass d{ 0 };				// ctor initializer_list
	MyClass e(0);				// ctor int
	MyClass f = MyClass(0);		// ctor int

								// delete a, &b is accepted...  But only delete the result a of comma expression "a, &b"
	delete a;
	delete &b;					// delete b is not allowed, only a ptr is accepted


	Color c1 = Bleu;
	Color c2 = Color::Bleu;

	Color& c3r = MyColor;
	Color&& c4r = Blanc;


	MyClass::WeekEndDays e1 = MyClass::Saturday;
	MyClass::WeekEndDays e2 = MyClass::WeekEndDays::Saturday;

	Speed s1 = Speed::Slow;		// Slow alone is not accepted (enum class)


	Point p1{ 2, 3 };			// Uniform initialization
	Point p2 = { 2,3 };			// Aggregate initialization
	Point p3 = Point(2, 3);		// Constructor


	cout << endl << endl;
	m.i = 0xFF00F00F; // 11111111 00000000 11110000 00001111 
	cout << hex << m.s.lo << endl; // 11111111 00000000 
	cout << hex << m.s.hi << endl; // 11110000 00001111 
	cout << hex << (int)m.c[3] << endl; // 11111111 
	cout << hex << (int)m.c[2] << endl; // 00000000 
	cout << hex << (int)m.c[1] << endl; // 11110000 
	cout << hex << (int)m.c[0] << endl; // 00001111
	m.Hello();
	cout << hex << m.i << dec << endl;


	// Standard user - defined literals
	// C++11 defined the syntax for user - defined literal suffixes, but the standard library did not use any of them.C++14 adds the following standard literals : [15]
	//
	//	"s", for creating the various std::basic_string types.
	//	"h", "min", "s", "ms", "us", "ns", for creating the corresponding std::chrono::duration time intervals.
	//	"if", "i", "il", for creating the corresponding std::complex<float>, std::complex<double> and std::complex<long double> imaginary numbers.
	//
	// The two "s" literals do not interact, as the string one only operates on string literals, and the one for seconds operates only on numbers

	auto str = "hello world"s;	// auto deduces string
	auto dur = 60s;				// auto deduces chrono::seconds
	auto z = 1i;				// auto deduces complex<double>


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
	//return 0;		// Actually not needed for main function
}
