﻿// 551 CPP Lambdas
// Examples of Lambdas in C++
//
// 2016-10-04	PV
// 2017-01-14	PV		Higher order lambdas example; removed trigraphs code
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022
// 2022-07-13	PV		Modern C++ refresh

#define _SCL_SECURE_NO_WARNINGS		// Otherwise use of copy generated a deprecated error
#pragma warning (disable: 4189 4100 4101)

#include <iostream>
#include <algorithm>
#include <vector>
#include <iso646.h>
#include <functional>

using namespace std;


struct LambdaFunctor {
	void operator() (int n) const {
		cout << n << endl;
	}
	void operator() (double d) const {
		cout << d << endl;
	}
};

void ActionInt(int n, void(*action)(int))
{
	action(n);
}



template <typename T, typename Predicate>
void keep_if(vector<T>& v, Predicate pred) {
	auto notpred = [&](const T& t) {
		return !pred(t);
	};
}

template <typename Container>
void print(const Container& c) {
	for_each(c.begin(), c.end(), [](const typename Container::value_type& e) { cout << e << " "; });
	cout << endl;
}

class MutableLambda
{
public:
	MutableLambda(int n) {
		int s = 0;
		// Without mutable can't update captured (by value) variable s in the lambda
		auto f1 = [s](int n) mutable {for (int i = 1; i <= n; i++) s += i; return s; };
		int sum1 = f1(100);

	}
};

int doublerOfInt(int x)
{
	using namespace std;
	//auto la = [this](int i) {return 3 * i};		// this not allowed outside a non-static member function
	return 2 * x;
}


int main() {
	auto f1 = [](int n) {int s = 0; for (int i = 1; i <= n; i++) s += i; return s; };
	int sum1 = f1(100);
	cout << "sum1: " << sum1 << endl;

	int sum2 = 0;
	auto f2 = [&sum2](int n) {sum2 = 0; for (int i = 1; i <= n; i++) sum2 += i; };
	f2(100);
	cout << "sum2: " << sum2 << endl;

	// For fun!
	[]() {}();
	[]()->void {}();
	[] {}();


	// Higher order lambdas (need #include <functional>)
	auto addtwointegers = [](int x) -> function<int(int)> {
		return [=](int y) { return x + y; };
	};

	// The following code declares a lambda expression that takes another
	// lambda expression as its argument.
	// The lambda expression applies the argument z to the function f
	// and multiplies by 2.
	auto higherorder = [](const function<int(int)>& f, int z) {
		return f(z) * 2;
	};

	// Call the lambda expression that is bound to higher order. 
	auto answer = higherorder(addtwointegers(7), 8);

	// Print the result, which is (7+8)*2.
	cout << "HO: " << answer << endl;



	// C++ is more flexible than C#, a lambda [](int)->int is backward/forward convertible to a int (*)(int) and a function<int(int)>
	// Actually, more precisely, from 'Welcome Back to CPP':
	// Additionally, stateless lambdas are now convertible to function pointers. 
	// C++11 5.1.2[expr.prim.lambda]/6 has this description: "The closure type for a lambda-expression with no lambda-capture has a public 
	// non-virtual non-explicit const conversion function to pointer to function having the same parameter and return types as the closure 
	// type’s function call operator. The value returned by this conversion function shall be the address of a function that, when invoked,
	// has the same eﬀect as invoking the closure type’s function call operator." 
	// (The Visual C++ in VS 2012 implementation is even better than that, because it makes stateless lambdas convertible to function pointers
	// that have arbitrary calling conventions.This is important when you are using APIs that expect things like __stdcall function pointers.)
	auto doubler1 = [](int x) { return 2 * x; };
	auto doubler2 = doublerOfInt;
	int(*doubler3)(int) = doubler1;
	int(*doubler4)(int) = doubler2;
	function<int(int)> doubler5 = doubler1;
	function<int(int)> doubler6 = doubler2;


	// iso464
	if constexpr (2 > 0 or 3 > 0) cout << endl;

	ActionInt(42, [](int n) {cout << n << endl; });
	LambdaFunctor()(12);

	auto lf = LambdaFunctor();
	lf(3.1416);

	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), [](int n) {
		cout << n;
		if (n % 2 == 0) {
			cout << " even ";
		}
		else {
			cout << " odd ";
		}
	});
	cout << endl;

	// Variables can be initialized in the lambda capture clause
	int a = 1;
	[&, b = 2] { a += b; }();	// can skip parentheses if lambda has no parameters
	cout << a << endl;	// 3

	auto x = [] { return 3; };
	// Default construct new lambda of same type
	decltype(x) y = x; // valid in C++20

	// Make copy of lambda
	auto copy = x;
	// Assign copy to x since they have same type
	x = copy; // valid in C++20

	// In C++ 20 can use lambdas in unevaluated contexts
	// Default construct inlined lambda
	decltype([] { return 17; }) aa{}; // valid in C++20; although its use...
	cout << aa() << endl;	// 17

//#ifdef _WIN32
//	cout << "(Pause)";
//	(void)getchar();
//#endif
	return 0;
}
