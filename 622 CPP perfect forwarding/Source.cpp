// 622 CPP Perfect forwarding
// Play with this concept
//
// 2017-04-29	PV	GitHub and Linux

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;


class c {
public:
	c() {
		cout << "c constructor\n";
	}

	c(const c& other) {
		cout << "c copy constructor\n";
	}

	c(c&& other) {
		cout << "c move constructor\n";
	}

	c& operator = (const c& other) {
		cout << "c copy assignment operator\n";
		return *this;
	}

	c& operator = (c&& other) {
		cout << "c move assignment operator\n";
		return *this;
	}

	c& operator + (int other) {
		cout << "c operator + (int)\n";
		return *this;
	}
};


void Test() {
	c r{};			// unary constructor
	cout << endl;
	c s = c(r);		// copy constructor
	cout << endl;
	s = r;			// copy assignment operator
	cout << endl;
	s = c(r);		// copy constructor then move assignment operator
	cout << endl;
	c tt = c(c{});	// constructor, then move constructor
}


template <typename T>
auto n(T&& r) {
	//return forward<T>(r);
	return r;
}


void Test2() {
	c r{};			// unary constructor
	cout << endl;
	c s = c(r);		// copy constructor
	cout << endl;
	s = r;			// copy assignment operator
	cout << endl;
	s = n(c(n(r)));		// copy constructor then move assignment operator
	cout << endl;
	c tt = n(c(c{}));	// constructor, then move constructor
}


int main() {
	Test2();

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
