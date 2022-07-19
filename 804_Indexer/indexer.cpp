// CS804_Indexer.cpp
// Play with C++, indexer operator and smart pointers
//
// 2022-07-18	PV		First version
// 2022-07-19	PV		degre() as a function and not a private field (was wrong)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <memory>

#ifdef _WIN32
#include <format>       // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

class Polynome
{
private:
	unique_ptr<vector<double>> coeffs = nullptr;

public:
	int degree() const { return static_cast<int>(coeffs->size()) - 1; }

	Polynome()
	{
		coeffs = make_unique<vector<double>>();
		coeffs->push_back(0.0);;
	}

	Polynome(initializer_list<double> l)
	{
		coeffs = make_unique<vector<double>>();
		for (auto c : l)
			coeffs->push_back(c);
		Truncate();
	}

	Polynome(const Polynome& other)
	{
		cout << "Copy constructor\n";
		coeffs = make_unique<vector<double>>();
		int deg = other.degree();
		for (int i = 0; i <= deg; i++)
			coeffs->push_back((*other.coeffs)[i]);
	}

	Polynome(Polynome&& other) noexcept
	{
		cout << "Move constructor\n";
		coeffs = move(other.coeffs);
		other.coeffs = nullptr;
	}

	// Construction from double, enables simple conversion double -> Polynome, which 
	// initializer_list<double> does not (without {})
	Polynome(double d)
	{
		coeffs = make_unique<vector<double>>();
		coeffs->push_back(d);
	}

	Polynome& operator=(const Polynome& other)
	{
		cout << "Operator =\n";
		coeffs->clear();
		for (int i = 0; i <= degree(); i++)
			coeffs->push_back((*other.coeffs)[i]);
		return *this;
	}


	// Remove heading zero coefficients after an operation for optimized representation
	void Truncate()
	{
		int deg = degree();
		while (deg > 0 && (*coeffs)[deg] == 0.0)
			coeffs->erase(coeffs->begin() + deg--);
	}

	//void Clear()
	//{
	//	coeffs->clear();
	//	coeffs->push_back(0.0);
	//}

	// Indexer on const polynomial returns a double
	// Never change internal representation
	double operator[](int index) const {
		assert(index >= 0);
		if (index > degree())
			return 0.0;
		else
			return (*coeffs)[index];
	}

	// while indexer on non-constant polynomial returns a double&
	// Update coeffs size if index>degree() to provide a valid double&
	double& operator[](int index) {
		assert(index >= 0);
		while (degree() < index)
			coeffs->push_back(0.0);
		return (*coeffs)[index];
	}

	Polynome operator+(const Polynome& other) const
	{
		Polynome sum(*this);
		for (int i = 0; i <= other.degree(); i++)
			sum[i] += other[i];
		sum.Truncate();
		return sum;
	}

	Polynome operator-() const
	{
		Polynome neg;
		for (int i = 0; i <= degree(); i++)
			neg[i] = -(*coeffs)[i];
		return neg;
	}

	Polynome operator-(const Polynome& other) const
	{
		return *this + (-other);		// Maybe not very efficient
	}

	virtual operator string() const
	{
		string res = "";
		bool first = true;
		for (int i = degree(); i >= 0; i--)
		{
			double c = (*coeffs)[i];
			if (c != 0.0 || degree() == 0)
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
		for (int i = max(degree(), other.degree()); i >= 0; i--)
			if ((*this)[i] != other[i])
				return false;
		return true;
	}

	double operator()(double x) const
	{
		double res = (*coeffs)[degree()];
		for (int i = degree(); --i >= 0;)
			res = (res * x) + (*coeffs)[i];
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

	s = Polynome{ 6,5,-1 };
	cout << "\nEval p1 from 1 to 4\n";
	for (double d = 1; d <= 4.0; d += 0.25)
		cout << fixed << setprecision(3) << d << "  " << p1(d) << endl;

	cout << endl << "p1-5: " << p1 - 5.0 << endl;

	return 0;
}
