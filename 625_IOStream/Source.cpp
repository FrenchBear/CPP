// CPP 625 iostream
//
// 2017-04-01	PV
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;


struct sprocket {
	int i;
	char c;

	sprocket() :i(0), c(0) {};
	sprocket(int I, char C) : i(I), c{ C } {};
};

ostream& operator << (ostream &os, const sprocket& s) {
	return os << "{" << s.i << ",'" << s.c << "'}";
}

istream& operator >> (istream &is, sprocket& s) {
	char c;
	int i;
	if (is >> c && c == '{' && is >> i)
		if (is >> c && c == ',' && is >> c && c == '\'' && is >> c) {
			sprocket stemp = sprocket{ i, c };
			if (is >> c && c == '\'' && is >> c && c == '}') {
				s = stemp;
				return is;
			}
		}
	// There was a problem
	is.setstate(ios_base::failbit);
	return is;
}


void TestDouble() {
	double d1 = sqrt(2);

	cout.precision(2);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(4);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(8);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(12);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	//	1.4    1.41e+00    1.41
	//	1.414    1.4142e+00    1.4142
	//	1.4142136    1.41421356e+00    1.41421356
	//	1.41421356237    1.414213562373e+00    1.414213562373

	d1 = 4000 * atan(1.0);
	cout.precision(2);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(4);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(8);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	cout.precision(12);
	cout << defaultfloat << d1 << "    " << scientific << d1 << "    " << fixed << d1 << endl;
	//	3.1e+03    3.14e+03    3141.59
	//	3142    3.1416e+03    3141.5927
	//	3141.5927    3.14159265e+03    3141.59265359
	//	3141.59265359    3.141592653590e+03    3141.592653589793
}


int main() {
	sprocket s1{ 1,'a' };
	sprocket s2{ 2,'b' };

	cout << s1 << endl;
	cout << s2 << endl << endl;

	string s{ "{3,'c'}\n{4,'d'}" };
	istringstream is(s);
	for (sprocket s; is >> s;)
		cout << s << endl;
	cout << endl;

	TestDouble();

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
}
