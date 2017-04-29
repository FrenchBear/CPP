// CPP Arith2
// Metaprogramming and pairs in C++
// 2017-01-23	PV
// 2017-01-24	PV	Int4d --> template IntBase
// 2017-04-29	PV	GitHub and Linux

#include <iostream>
#include <string>
#include <tuple>
#include <initializer_list>
#include <random>
#include <chrono>
#include <climits>
#include <exception>

#include "InfInt.h"


using namespace std;


// Just to use constexpr with a template
template <typename Tint>
static constexpr Tint myPow(Tint x, int p)
{
	if (p == 0) return (Tint)1;
	if (p == 1) return x;

	Tint tmp = myPow(x, p / 2);
	return (p % 2 == 0) ? tmp*tmp : x*tmp*tmp;
}


// Base arithmetic class providing 4 decimal digits precision using
// native (processor) support of addition and multiplication
template <typename Tint, int dig>
class IntBase {
private:
	// Native storage for base class
	Tint val;

	// Contruction from int is just for internal use, publicly use construction from string
	IntBase(Tint n) : val(n) {}


	// Overload options to convert a string to an integral type
	void inline stringtointegral(short& sh, string s) {
		sh = static_cast<short>(stoi(s));
	}

	void inline stringtointegral(int& i, string s) {
		i = stoi(s);
	}

	void inline stringtointegral(long& l, string s) {
		l = stol(s);
	}

	void inline stringtointegral(long long& ll, string s) {
		ll = stoll(s);
	}


public:
	// Information on number of chars handled by the class
	static constexpr size_t digits = dig;
	static constexpr Tint k = myPow(10, dig);


	// Public default constructor
	IntBase() : val(0) {}

	// Normal construction
	IntBase(const string& s) {
		if (s.length() > digits)
		{
			auto msg = string("Invalid argument, len>") + std::to_string(digits);
			throw runtime_error(msg);
		}
		stringtointegral(val, s);
	}

	// Copy constructor
	IntBase(const IntBase& other) {
		val = other.val;
	}

	// Move constructor
	IntBase(IntBase&& other) {
		val = other.val;
	}

	// Copy assignment operator
	IntBase& operator =(const IntBase& other) {
		val = other.val;
		return *this;
	}

	// Move assignment operator
	IntBase& operator =(IntBase&& other) {
		val = other.val;
		return *this;
	}

	// Addition 4d+4d -> (4d carry, 4d result)
	static pair<IntBase, IntBase> Plus(std::initializer_list<const IntBase> args)
	{
		Tint s = 0;
		for (const auto& arg : args)
			s += arg.val;
		return pair<IntBase, IntBase>(IntBase(s / k), IntBase(s % k));
	}

	// Multiplication 4d*4d -> (4d high, 4d low)
	static pair<IntBase, IntBase> Mult(const IntBase& a, const IntBase& b)
	{
		Tint x = a.val * b.val;
		Tint h = x / k;
		Tint l = x % k;
		return pair<IntBase, IntBase>(IntBase(h), IntBase(l));
	}

	// Convenient helper for output formatting
	bool IsZero() const {
		return val == 0;
	}

	// Basic simple format
	string ToString() const {
		return std::to_string(val);
	}

	// Output always formatted using 'digits' digits
	string ToStringWithLeadingZeros() const {
		return std::to_string(val + k).substr(1);
	}

	// Helper for testing, prints a pair of Int4d numbers
	static string ToString2(pair<const IntBase&, const IntBase&> p) {
		if (p.first.val == 0)
			return p.second.ToString();
		else
			return p.first.ToString() + p.second.ToStringWithLeadingZeros();
	}
};


// Double Arithmetic: provides twice the capacity of type T
// Both Int4d and DA implement the same public members, so it's Ok
// to instantiate DA<Int4d>, DA<DA<Int4d>>, DA<DA<DA<Int4d>>>...
template <typename T>
class DA {
private:
	T high;
	T low;

	// Private constructor for intermediate calculations
	DA(const T& h, const T& l) :high{ h }, low{ l } {}


public:
	// Information on number of chars handled by the class
	static constexpr size_t digits = 2 * T::digits;

	// Default constructor (value=0)
	DA() {
	}

	// Constructor from string
	DA(const string& s) {
		if (s.length() > digits)
		{
			auto msg = string("Invalid argument, len>") + std::to_string(digits);
			throw runtime_error(msg);
		}

		if (s.length() > T::digits) {
			high = T(s.substr(0, s.length() - T::digits));
			low = T(s.substr(s.length() - T::digits, T::digits));
		}
		else {
			low = T(s);
		}
	}

	// Copy constructor
	DA(const DA& other) {
		high = other.high;
		low = other.low;
	}

	// Move constructor (makes performance in Debug build worse)
	DA(DA&& other) {
		high = move(other.high);
		low = move(other.low);
	}

	// Copy assignment operator
	DA& operator =(const DA& other) {
		high = other.high;
		low = other.low;
		return *this;
	}

	// Move assignment operator (makes performance in Debug build worse)
	DA& operator =(DA&& other) {
		high = move(other.high);
		low = move(other.low);
		return *this;
	}


	// Sum of two DA, using half-word addition provided by T
	static pair<DA, DA> Plus(std::initializer_list<const DA> args) {
		// Skipping 1st addition divides execution time by 10 in Debug build!!!!! (why such a difference??)
		//T h, l, ovh, ovl;
		T h{ args.begin()->high }, l{ args.begin()->low }, ovh, ovl;
		//bool first = false;
		bool first = true;
		for (const auto& arg : args) {
			if (first)
				first = false;
			else {
				T ov1, ov2;
				pair<T&, T&>{ov1, l} = T::Plus({ l, arg.low });
				pair<T&, T&>{ov2, h} = T::Plus({ h,  ov1, arg.high });
				pair<T&, T&>{ovh, ovl} = T::Plus({ ovl, ov2 });
			}
		}
		return pair<DA, DA>(DA{ ovh, ovl }, DA{ h, l });
	}


	// Multiplication of two DA, using half-word multiplication provided by T
	static pair<DA, DA> Mult(const DA&me, const DA& other) {
		T lowH, lowL, highH, highL;
		T t1h, t1l, t2h, t2l;

		pair<T&, T&> {lowH, lowL} = T::Mult(me.low, other.low);
		pair<T&, T&> {t1h, t1l} = T::Mult(me.high, other.low);
		pair<T&, T&> {t2h, t2l} = T::Mult(me.low, other.high);
		pair<T&, T&> { highH, highL } = T::Mult(me.high, other.high);

		T ov1, ov2, dummy;
		pair<T&, T&> {ov1, lowH} = T::Plus({ lowH, t1l, t2l });
		pair<T&, T&> {ov2, highL} = T::Plus({ highL, t1h, t2h, ov1 });
		pair<T&, T&> {dummy, highH} = T::Plus({ highH, ov2 });

		return pair<DA, DA>(DA{ highH, highL }, DA{ lowH, lowL });
	}


	// Convenient helper for output formatting
	bool IsZero() const {
		return high.IsZero() && low.IsZero();
	}

	// Basic simple format
	string ToString() const {
		if (high.IsZero())
			return low.ToString();
		else
			return high.ToString() + low.ToStringWithLeadingZeros();
	}

	// Output always formatted using 'digits' digits
	string ToStringWithLeadingZeros() const {
		return high.ToStringWithLeadingZeros() + low.ToStringWithLeadingZeros();
	}

	// Helper for testing, prints a pair of DA numbers
	static string ToString2(pair<const DA&, const DA&> p) {
		if (p.first.IsZero())
			return p.second.ToString();
		else
			return p.first.ToString() + p.second.ToStringWithLeadingZeros();
	}

};


// C++11 random reneration
std::mt19937 rng;

string GetRandomNumber(int digits)
{
	stringstream ss;
	uniform_int_distribution<short> cdis('0', '9');
	for (int i = 0; i < digits; i++)
		ss << (char)cdis(rng);

	return ss.str();
}


// Generic test function
template <typename T>
void Test() {
	cout << "Test Int" << T::digits << "d\n";
	string astr = GetRandomNumber(T::digits);
	string bstr = GetRandomNumber(T::digits);

	auto start1 = std::chrono::high_resolution_clock::now();
	T a(astr), b(bstr);
	cout << "a" << T::digits << ": " << a.ToString() << endl;
	cout << "b" << T::digits << ": " << b.ToString() << endl;
	T h, l;
	pair<T, T> sum = T::Plus({ a,b });
	string sumstr = T::ToString2(sum);
	cout << "a" << T::digits << "+b" << T::digits << ": " << sumstr << endl;
	pair<T, T> prod = T::Mult(a, b);
	string prodstr = T::ToString2(prod);
	cout << "a" << T::digits << ".b" << T::digits << ": " << prodstr << endl;
	auto finish1 = std::chrono::high_resolution_clock::now();
	auto milliseconds1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);

	// Check using InfInt
	auto start2 = std::chrono::high_resolution_clock::now();
	InfInt abi = astr;
	InfInt bbi = bstr;
	InfInt sumbi = abi + bbi;
	InfInt prodbi = abi * bbi;
	cout << "Sum: " << ((sumbi.toString() == sumstr) ? "Ok" : "Error");
	cout << ",  Prod: " << ((prodbi.toString() == prodstr) ? "Ok" : "Error") << endl;
	auto finish2 = std::chrono::high_resolution_clock::now();
	auto milliseconds2 = std::chrono::duration_cast<std::chrono::milliseconds>(finish2 - start2);
	std::cout << "Elapsed: " << milliseconds1.count() << " ms,  Check: " << milliseconds2.count() << " ms\n\n";
}



int main() {
	// Randomize
	rng.seed(std::random_device()());

	typedef IntBase<int, 4> Int4d;
	//typedef DA<IntBase<short, 2>> Int4d;

	// Manual test for Ind4d
	Int4d a4("1234");
	Int4d b4("8766");
	cout << "a4=" << a4.ToString() << endl;
	cout << "b4=" << b4.ToString() << endl;
	pair<Int4d, Int4d> s4 = Int4d::Plus({ a4, b4 });
	cout << "a4+b4=" << Int4d::ToString2(s4) << endl;
	pair<Int4d, Int4d> p4 = Int4d::Mult(a4, b4);
	cout << "a4.b4=" << Int4d::ToString2(p4) << endl << endl;;


	// Templated tests
	//typedef DA<Int4d> Int8d;
	typedef IntBase<long long, 8> Int8d;		// More efficient than DA<Int4dT<int, 4>>


	Test<Int8d>();
	//Int8d a8("12345678");
	//Int8d b8("87654321");
	//cout << "a8=" << a8.ToString() << endl;
	//cout << "b8=" << b8.ToString() << endl;
	//pair<Int8d, Int8d> s8 = Int8d::Plus({ a8, b8 });
	//cout << "a8+b8=" << Int8d::ToString2(s8) << endl;
	//pair<Int8d, Int8d> p8 = Int8d::Mult(a8, b8);
	//cout << "a8.b8=" << Int8d::ToString2(p8) << endl << endl;

	typedef DA<Int8d> Int16d;
	Test<Int16d>();

	typedef DA<Int16d> Int32d;
	Test<Int32d>();

	typedef DA<Int32d> Int64d;
	Test<Int64d>();

	typedef DA<Int64d> Int128d;
	Test<Int128d>();

	typedef DA<Int128d> Int256d;
	Test<Int256d>();

	typedef DA<Int256d> Int512d;
	Test<Int512d>();

	typedef DA<Int512d> Int1024d;
	Test<Int1024d>();

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
