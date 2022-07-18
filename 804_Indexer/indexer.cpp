// CS804_Indexer.cpp
// Play with C++, indexer operator
//
// 2022-07-18	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cassert>

#ifdef _WIN32
#include <format>       // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

class Polynome
{
private:
	int degre;
	vector<double> coeffs;

public:
	Polynome()
	{
		Clear();
	}

	Polynome(initializer_list<double> l)
	{
		Clear();
		int i = 0;
		for (auto c : l)
		{
			coeffs.push_back(c);
			i++;
		}
		degre = i - 1;
		Truncate();
	}

	Polynome(const Polynome& other)
	{
		degre = other.degre;
		for (int i = 0; i <= degre; i++)
			coeffs.push_back(other.coeffs[i]);
	}

	// Remove heading zero coefficients after an operation
	void Truncate()
	{
		while (degre > 0 && coeffs[degre] == 0.0)
		{
			coeffs.erase(coeffs.begin() + degre);
			degre--;
		}
	}

	void Clear()
	{
		degre = 0;
		coeffs.clear();
		coeffs.push_back(0.0);
	}

	int Degre() const { return degre; }

	// Indexer on const polynomial returns a double
	// Never change internal representation
	double operator[](int index) const {
		assert(index >= 0);
		if (index > degre)
			return 0.0;
		else
			return coeffs[index];
	}

	// while indexer on non-constant polynomial returns a double&
	// Update coeffs size if index>degre to provide a valid double&
	double& operator[](int index) {
		assert(index >= 0);
		while (degre < index)
		{
			coeffs.push_back(0.0);
			degre++;
		}
		return coeffs[index];
	}

	Polynome operator+(const Polynome& other) const
	{
		Polynome sum(*this);
		for (int i = 0; i <= other.degre; i++)
			sum[i] += other[i];
		sum.Truncate();
		return sum;
	}

	Polynome operator-() const
	{
		Polynome neg;
		for (int i = 0; i <= degre; i++)
			neg[i] = -coeffs[i];
		return neg;
	}
};

ostream& operator <<(ostream& out, const Polynome& p)
{
	bool first = true;
	for (int i = p.Degre(); i >= 0; i--)
	{
		double c = p[i];
		if (c != 0.0 || p.Degre() == 0)
		{
			if (c > 0 && !first)
				out << '+';
			if (c != 1.0 || i == 0)
				out << c;
			if (i == 1)
				cout << 'x';
			else if (i >= 2)
				cout << "x^" << i;
		}
		first = false;
	}
	return out;
}

int main()
{
	cout << "C++ 20 indexers\n\n";

	Polynome p1{ 0, 1, 2 };
	cout << p1 << "   degre=" << p1.Degre() << endl;
	//p1[4] = -6.0;
	//cout << p1 << "   degre=" << p1.Degre() << endl;

	Polynome p2{ -2,1,-2,3 };
	cout << p2 << "   degre=" << p1.Degre() << endl;

	Polynome s = p1 + p2;
	cout << s << "   degre=" << s.Degre() << endl;

	cout << s + (-s) << endl;

	return 0;
}
