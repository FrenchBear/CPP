// 629 CPP misc
// Examples of various C++ features
// Stroustrup Tour of C++, §11 and 12
//
// 2017-04-13	PV
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>
#include <string>
#include <array>
#include <bitset>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <utility>
#include <memory>
#include <chrono>
#include <functional>	// bind, mem_fn
#include <cmath>
#include <numeric>
#include <random>
#include <valarray>

#include "Shape.h"
#include "Circle.h"


using namespace std;
using namespace std::chrono;


// Helper to simplify implementation of operator << for various containers
template<typename C>
void LessLessHelper(ostream& os, C container) {
	bool first = true;
	for (auto it = container.begin(); it != container.end(); ++it) {
		if (first)
			first = false;
		else
			os << ", ";
		os << *it;
	}
}

// Generic operator << for vector
// Actually making it too generic with T container creates many conflicting calls, compiler
// has too many choices to output other types
template <typename T>
ostream& operator <<(ostream& os, vector<T> container) {
	os << '{';
	LessLessHelper(os, container);
	os << '}';
	return os;
}

// Generic operator << for forward_list
template <typename T>
ostream& operator <<(ostream& os, forward_list<T> container) {
	os << "((";
	LessLessHelper(os, container);
	os << "))";
	return os;
}


// operator << for pairs
template <typename T1, typename T2>
ostream& operator <<(ostream& os, pair<T1, T2> mypair) {
	os << '(' << mypair.first << ", " << mypair.second << ')';
	return os;
}


// Variadic operator << for tuple
// Got this from stack overflow, but it's not clear to me how it works, "typename std::enable_if<(n >= sizeof...(T))>::type" ??

// Termination function
template <size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream&, const std::tuple<T...>&)
{}

template <size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
	print_tuple(std::ostream& os, const std::tuple<T...>& tup)
{
	if (n != 0)
		os << ", ";
	os << std::get<n>(tup);
	print_tuple<n + 1>(os, tup);
}

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tup)
{
	os << "<";
	print_tuple<0>(os, tup);
	return os << ">";
}



// make_unique<T> from Stroustrup himself, but actually not needed, it is now included in standard library...
//template <typename T, typename... Args>
//unique_ptr<T> make_unique(Args&&... args) {
//	return std::unique_ptr<T>{new T { std::forward<Args>(args)... }};
//}



// Exercise of implementing a reverse function that reverses order of members of a container,
// whether they support indexed access or not, using type tags provided by iterator_traits

// Helper that actually reverse elements in a container that supports indexed access
template<typename C>
void do_reverse(C& c) {
	size_t size = c.size();
	using T = typename C::value_type;
	for (size_t i = 0; i < size / 2; i++)
	{
		T temp = c[i];
		c[i] = c[size - 1 - i];
		c[size - 1 - i] = temp;
	}
}

// reverse version when container supports direct indexing, that's easy, just call the helper
template<typename C>
void reverse_helper(C& c, random_access_iterator_tag) {
	do_reverse(c);
}


// reverse version when container only supports forward access and no indexing
// Copy the container in a vector, reverse it, and copy back elements to original container
// Actually, wouldn't a move (c -> vector and vector -> c) be more efficient, if T is a movable type?
template<typename C>
void reverse_helper(C& c, forward_iterator_tag) {
	using T = typename C::value_type;
	vector<T> v{ c.begin(), c.end() };
	do_reverse(v);
	copy(v.begin(), v.end(), c.begin());
}

// General container reverser, whether the container supports direct indexing or not
// "official" function to call
template<typename C>
void reverse(C& c) {
	using Iter = typename C::iterator;
	using Iterator_category = typename iterator_traits<Iter>::iterator_category;
	reverse_helper(c, Iterator_category{});		// Compiler choses which helper to call depending on Iterator_category type
}


void TestTransformReverse() {
	vector<int> v(10);
	iota(v.begin(), v.end(), 1);

	// transform and reverse
	cout << "v = " << v << endl;
	transform(v.begin(), v.end(), v.begin(), [](int x) {return x*x; });
	cout << "v squared = " << v << endl;
	reverse(v);
	cout << "v squared reversed = " << v << endl << endl;
}



// 1-line equivalent of bind, hiding some parameters of a function call and exposing a simplified list of arguments
double p2(double x) { return pow(x, 2.0); }

void TestBind() {
	// bind, can provide values for some parameters of a function and expose a simplified call interface
	// Now what is a realistic use for this feature remains obscure, since a basic ordinary 1-line function can do it easily...
	// Moreover it's not possible to convert the result of bind to an ordinary function pointer, whereas the 1-line function wrapper does it for free
	using namespace placeholders;
	auto pow2 = bind((double(*)(double, double))pow, _1, 2.0);
	cout << "7^2 = " << pow2(7.0) << endl;
	cout << "7^2 = " << p2(7.0) << endl;
}


// Just a test for TimeExecution()
void compute_primes() {
	constexpr int pmax = 1'000'000;
	vector<bool> tb(pmax / 2 + 1, false);
	int nprime = 1;
	int nv = 3;
	while (nv <= pmax)
	{
		if (!tb[(nv - 1) / 2])
		{
			nprime++;
			int nvr = nv + nv + nv;          // skip even numbers
			while (nvr <= pmax)
			{
				// this test actually slows execution down about 20%
				/* if (!tb[(nvr - 1) / 2]) */ tb[(nvr - 1) / 2] = true;
				nvr += nv + nv;
			}
		}
		nv += 2;
	}
	cout << "Nb primes 2.." << pmax << " = " << nprime << endl;
}

void TimeExecution(void(*f)()) {
	auto t0 = high_resolution_clock::now();
	f();
	auto t1 = high_resolution_clock::now();
	cout << "Elapsed=" << duration_cast<milliseconds>(t1 - t0).count() << " ms" << endl;
}

void TestTime() {
	// time and vector<bool>
	// On HIGGS, x86 debug:   Nb primes 2..1000000 = 78498   Elapsed=3165 ms
	//           x86 release: Nb primes 2..1000000 = 78498   Elapsed=7 ms
	//           x64 debug:   Nb primes 2..1000000 = 78498   Elapsed=3412 ms
	//           x64 release: Nb primes 2..1000000 = 78498   Elapsed=6 ms
	TimeExecution(compute_primes);
	// Nb primes 2..100000000 = 5761455   Elapsed=1261 ms
}


void TestNumericalAlgorithms() {
	vector<double> vd{ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2 };
	auto b = vd.cbegin();
	auto e = vd.cend();
	auto b10 = b + 10;

	cout << "data: " << vd << endl << endl;
	cout << "accumulate(+): " << accumulate(b, e, 0.0) << endl;
	cout << "accumulate(*): " << accumulate(b, e, 1.0, [](double acc, double v) {return acc * v; }) << endl;
	cout << "inner product 0..9 by 10..19: " << inner_product(b, b10, b10, 0.0) << endl;

	vector<double> vps;
	auto ps = partial_sum(b, e, back_inserter(vps));
	cout << "partial_sum: " << vps << endl;

	vector<double> vpd;
	auto pd = adjacent_difference(b, e, back_inserter(vpd));
	cout << "adjacent_difference: " << vpd << endl;
}


class Rand_int {
	default_random_engine re;
	uniform_int_distribution<> dist;
public:
	Rand_int(int low, int high) : dist{ low, high } {}
	int operator()() { return dist(re); }
};

void TestRandomNumbers() {
	auto diedist = uniform_int_distribution<int>(1, 6);
	auto engine = default_random_engine{};

	vector<int> dice;
	for (size_t i = 0; i < 6; i++)
		dice.push_back(diedist(engine));
	cout << "6 dice: " << dice << endl;

	auto die2 = bind(diedist, engine);
	cout << "2 dice: " << die2() << ' ' << die2() << endl;

	auto die3 = bind(uniform_int_distribution<int>(1, 6), default_random_engine());
	cout << "3 dice: " << die3() << ' ' << die3() << ' ' << die3() << endl;

	Rand_int die4(1, 6);
	cout << "4 dice: " << die4() << ' ' << die4() << ' ' << die4() << ' ' << die4() << endl;
}


void TestValArray() {
	auto dist = uniform_real_distribution<double>(0.0, 1.0);
	auto engine = default_random_engine{};
	size_t n = 1'000'000;
	valarray<double> v1(n), v2(n);
	auto t0 = high_resolution_clock::now();
	for (size_t i = 0; i < n; i++)
	{
		v1[i] = dist(engine);
		v2[i] = dist(engine);
	}
	auto t1 = high_resolution_clock::now();
	valarray<double> v3 = v1*3.14 + v2 / v1 - 1.1;
	auto t2 = high_resolution_clock::now();

	cout << "\nGeneration v1 and v2: " << duration_cast<milliseconds>(t1 - t0).count() << " ms" << endl;
	cout << "Computation: " << duration_cast<milliseconds>(t2 - t1).count() << " ms" << endl;
}



int main() {
	// Use of a ptr as an array in C++ is conflicting with automatic conversion derived * into base *
	Circle tc[3]{ Circle("alpha", 1.0, 1.0, 1.0), Circle("beta", 2.0, 2.0, 2.0), Circle("gamma", 3.0, 3.0, 3.0) };
	Shape *ps = tc;

	cout << "sizeof(Shape)=0x" << hex << sizeof(Shape) << " sizeof(Circle)=0x" << hex << sizeof(Circle) << endl;
	cout << "&tc[0]=" << &tc[0] << " &tc[1]=" << &tc[1] << " &tc[2]=" << &tc[2] << endl;
	cout << "&ps[0]=" << &ps[0] << " &ps[1]=" << &ps[1] << " &ps[2]=" << &ps[2] << endl;
	// Real problem here -- Actually works with VC++ since per coincidence, sizeof(Circle) = 2*sizeof(Shape)!!!
	// But causes a core dumped error with gcc
	//cout << ps[2].name << endl;
	cout << dec;

	// in C++, array<T, n> is safer since it prevents accidental conversion
	array<Circle, 3> ac{ tc[0], tc[1], tc[2] };
	//ps = ac;	// No conversion from array<Circle, 3> to Shape * 

	// Specialized bitset type, mostly useful if the number of bits is more than what a int can hold
	bitset<64> bs64{ 0x1122334455667788ul };
	cout << bs64 << endl;

	// equal_range returns a pair
	vector<int> v{ 1, 2, 4, 4, 5, 6, 6, 6, 7, 9 };
	auto fr = equal_range(v.begin(), v.end(), 6, [](int i1, int i2) {return i1 < i2; });
	for (auto p = fr.first; p != fr.second; ++p)
		cout << *p << " ";
	cout << endl;

	forward_list<int> fli{ 1,2,3,4,5,6,7,8 };
	cout << "list = " << fli << endl;
	reverse(fli);
	cout << "list reversed = " << fli << endl << endl;

	// pair
	auto myPair = make_pair(1.414, "Hello");
	cout << myPair << endl;

	// tuple
	auto myTuple = make_tuple(12, 3.1416, 'c', "Hello", myPair, 0x1122334455667788ul);
	cout << myTuple << endl;

	// make_unique returns a unique_ptr calling directly type constructor (~ unique_ptr<T>(new T(args))
	auto ups = make_unique<Shape>("Square");
	auto upc = make_unique<Circle>("Round", 4.0, 5.0, 3.0);

	TestTransformReverse();

	// mem_fn (works with a virtual member function)
	cout << endl;
	auto print_shape_name = mem_fn(&Shape::print_name);		// transform a thiscall into a stdcall
	for_each(ac.begin(), ac.end(), print_shape_name);
	cout << endl;
	for_each(ac.cbegin(), ac.cend(), [](const Circle& rc) {rc.print_name(); });	// same with a lambda
	cout << endl;

	TestBind();

	//TestTime();

	//TestNumericalAlgorithms();

	TestRandomNumbers();

	TestValArray();

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
