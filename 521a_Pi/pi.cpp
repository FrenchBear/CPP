// pi.cpp : Implementation of pi calculation
//
// 2014-03-26	PV		Port to VS 2013
// 2022-07-13	PV		Modern C++ cleanup

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr int MAXPRC = 4001;
char p[MAXPRC];
char t[MAXPRC];
int q;

void add();
void sub();
void mul(int multiplier);
void div(int divisor);
void mul4();
void div4();
int tiszero();


void arctan(int s)
{
	int n;

	t[0] = 1;
	div(s);			// t[] = 1/s
	add();
	n = 1;
	do {
		mul(n);
		div(s * s);
		div(n += 2);
		if (((n - 1) / 2) % 2 == 0)
			add();
		else
			sub();
	} while (!tiszero());
}

void add()
{
	int j;

	for (j = q; j >= 0; j--)
		if (t[j] + p[j] > 9) {
			p[j] += t[j] - 10;
			p[j - 1] += 1;
		}
		else
			p[j] += t[j];
}

void sub()
{
	int j;

	for (j = q; j >= 0; j--)
		if (p[j] < t[j]) {
			p[j] -= t[j] - 10;
			p[j - 1] -= 1;
		}
		else
			p[j] -= t[j];
}

void mul(int multiplier)
{
	int b;
	int i;
	int carry = 0, digit = 0;

	for (i = q; i >= 0; i--) {
		b = (t[i] * multiplier + carry);
		digit = b % 10;
		carry = b / 10;
		t[i] = static_cast<char>(digit);
	}
}

// t[] /= l
void div(int divisor)
{
	int i, b;
	int quotient, remainder = 0;

	for (i = 0; i <= q; i++) {
		b = (10 * remainder + t[i]);
		quotient = b / divisor;
		remainder = b % divisor;
		t[i] = static_cast<char>(quotient);
	}
}

void div4()
{
	int i, c, d = 0;

	for (i = 0; i <= q; i++) {
		c = (10 * d + p[i]) / 4;
		d = (10 * d + p[i]) % 4;
		p[i] = static_cast<char>(c);
	}
}

void mul4()
{
	int i, c, d;

	d = c = 0;

	for (i = q; i >= 0; i--) {
		d = (p[i] * 4 + c) % 10;
		c = (p[i] * 4 + c) / 10;
		p[i] = static_cast<char>(d);
	}
}

int tiszero()
{
	int k;

	for (k = 0; k <= q; k++)
		if (t[k] != 0)
			return false;
	return true;
}


int main()
{
	// Nb of decimals
	q = 4000;

	if (q >= MAXPRC) {
		cout << "Precision too large\n";
		return 66;
	}

	// Compute pi
	auto t0 = high_resolution_clock::now();
	arctan(2);
	arctan(3);
	mul4();
	auto t1 = high_resolution_clock::now();

	// Print pi
	cout << static_cast<int>(p[0]) << ".";
	for (int i = 1; i <= q; i++)
		cout << static_cast<int>(p[i]);
	cout << endl;
	cout << "Duration: " << fixed << setprecision(3) << duration_cast<milliseconds>(t1 - t0).count() << "ms for " << q << " digits of pi\n";

	return 0;
}

