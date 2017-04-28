// 553 CPP Rvalues References
// Examples of && in C++ 11
//
// 2016-10-06	PV

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
	string &r3 = three();		// should be refused, rvalue, but accepted...
	//string &r4 = four();		// refused, rvalue, and would lose const qualifier

	cout << r3 << endl;

	complexe &rc = complexe(3.0, 4.0);
	//complexe *pc = &complexe(3.0, 4.0);
	//cout << pc->real() << ", " << pc->imag() << endl;
	
	getchar();
	return 0;
}