// 555 CPP complex
// Complex class with use of User-Defined Literals (suffix i)
// 2016-10-13	PV
// 2017-04-29	PV		GitHub and Linux

#include <stdio.h>
#include <iostream>
#include <string>
#include <complex>
//#include <math.h>		<complex> includes <cmath> includes <math.h>

using namespace std;

typedef complex<double> cplx;

/*
double module(const cplx &z) {
	return hypot(z.real(), z.imag());
}
*/

int main() {
	cplx z1 = 3.0 + 4.0i;
	cout << "z1: " << z1 << endl;
	cout << "module z1: " << abs(z1) << endl;

	cplx z2 = asin(2.0 + 0.0i);
	cout << "z2: " << z2 << endl;
	cout << "sin(z2): " << sin(z2) << endl;

#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif

	return 0;
}
