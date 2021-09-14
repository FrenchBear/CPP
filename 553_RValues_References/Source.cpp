// 553 CPP Rvalues References
// Examples of && in C++ 11
//
// 2016-10-06	PV
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#define _SCL_SECURE_NO_WARNINGS		// Otherwise use of copy generated a deprecated error

#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string one("cute");
const string two("fluffy");
string three() { return string("kit")+string("tens"); }
const string four() { return "reek"; }

class complexe {
private:
	double x, y;

public:
	complexe(double r, double i) : x(r), y(i) { cout << "complexe constructor " << x << ", " << y << endl; }
	complexe() : x(0), y(0) { cout << "complexe constructor " << x << ", " << y << endl; }
	~complexe() { cout << "complexe destructor " << x << ", " << y << endl; }

	double real() { return x; }
	double imag() { return y; }
};

int main() {
	string &r1 = one;
	//string &r2 = two;			// refused, would lose const qualifier
#ifdef _WIN32
	string &r3 = three();		// should be refused, rvalue, but accepted by VS (with a warning): Warning C4239: nonstandard extension used: 'initializing': conversion from 'std::string' to 'std::string &'

#else
	const string& cr3 = three();
	string &r3 = const_cast<string &>(cr3);
#endif
	//string &r4 = four();		// refused, rvalue, and would lose const qualifier

	cout << r3 << endl;

// gcc doesn't like following code:
// Source.cpp:48:34: error: invalid initialization of non-const reference of type complexe& from an rvalue of type complexe
//  complexe &rc = complexe(3.0, 4.0);
//                                  ^
#ifdef _WIN32
	complexe &rc = complexe(3.0, 4.0);
#endif
	//complexe *pc = &complexe(3.0, 4.0);
	//cout << pc->real() << ", " << pc->imag() << endl;
	
#ifdef _WIN32
	cout << "(Pause)";
	(void)getchar();
#endif
	return 0;
}
