// CS804_Indexer.cpp
// Play with C++, indexer operator
//
// 2022-07-18	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
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
			if (i == 0)
				coeffs[i] = c;
			else
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

	virtual operator string() const
	{
		string res = "";
		bool first = true;
		for (int i = degre; i >= 0; i--)
		{
			double c = coeffs[i];
			if (c != 0.0 || degre == 0)
			{
				if (c > 0 && !first)
					res += '+';
				if (c != 1.0 || i == 0)
					res += format("{}", c);
				if (i == 1)
					res += 'x';
				else if (i >= 2)
					res += format("x^{}", i);
			}
			first = false;
		}
		return res;
	}

	bool operator==(const Polynome& other) const
	{
		for (int i = max(degre, other.degre); i >= 0; i--)
			if ((*this)[i] != other[i])
				return false;
		return true;
	}

	double operator()(double x) const
	{
		double res = coeffs[degre];
		for (int i = degre; --i >= 0;)
			res = (res * x) + coeffs[i];
		return res;
	}
};

ostream& operator <<(ostream& out, const Polynome& p)
{
	out << (string)p;
	return out;
}

int main()
{
	cout << "C++ 20 indexers\n\n";

	Polynome p1{ 6, -5, 1 };
	cout << "p1: " << p1 << endl;

	Polynome p2{ -2,1,-2,3 };
	cout << "p2: " << p2 << endl;

	Polynome s = p1 + p2;
	cout << "p1+p2: " << p1 << endl;

	cout << "s+(-s): " << s + (-s) << endl;
	Polynome p3 = Polynome{ 6 } + Polynome{ 0,-5 } + Polynome{ 0,0,1 };
	cout << "p3: " << p3 << endl;
	cout << "p1==p3 " << (p1 == p3) << endl;

	cout << "\nEval f1 from 1 to 4\n";
	for (double d = 1; d <= 4.0; d += 0.25)
		cout << fixed << setprecision(3) << d << "  " << p1(d) << endl;

	return 0;
}
