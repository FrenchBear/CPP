// CS802_Init.cpp
// Play with constructors and initialization in C++
//
// 2022-07-15	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#ifdef _WIN32
#include <format>       // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

class V2
{
public:
	double x, y;
	V2();
	V2(double, double);
	~V2() { cout << "Destruction of " << ToString() << endl; }

	string ToString() const
	{
		return format("{} ({}, {})", (void *)this, x, y);
	}

	// Copy constructor
	// It is called when a new object is created from an existing object, as a copy of the existing object
	// It creates a separate memory block for the new object.
	// It is an overloaded constructor.
	// C++ compiler implicitly provides a copy constructor, if no copy constructor is defined in the class.

	// Assignment operator
	// This operator is called when an already initialized object is assigned a new value from another existing object.
	// It does not create a separate memory block or new memory space.
	// It is a bitwise operator.
	// A bitwise copy gets created, if the Assignment operator is not overloaded.

	// Copy constructor
	V2(const V2 &other)
	{
		x = other.x;
		y = other.y;
		cout << "Copy constructor, this=" << ToString() << ", other=" << other.ToString() << endl;
	}

	// Copy assignment operator
	V2 &operator=(const V2 &other) noexcept
	{
		x = other.x;
		y = other.y;
		cout << "Copy assignment operator, this=" << ToString() << ", other=" << other.ToString() << endl;
		return *this;
	}

	// Move constructor
	V2(V2 &other) noexcept
	{
		x = other.x;
		y = other.y;
		cout << "Move constructor, this=" << ToString() << ", other=" << other.ToString() << endl;
		// Actually there is nothing to steal and initialize in this class
	}

	// Move assignment operator
	V2 &operator=(V2 &other) noexcept
	{
		cout << "Move assignment operator, this=" << ToString() << ", other=" << other.ToString();
		x = other.x;
		y = other.y;
		cout << " -> " << this->ToString() << endl;
		return *this;
		// Actually there is nothing to steal and initialize in this class
	}

	V2 operator+(const V2 &other) const
	{
		auto res = V2(x + other.x, y + other.y);
		cout << "Operator+, this=" << ToString() << ", other=" << other.ToString() << " -> " << res.ToString() << endl;
		return res;
		// return V2(*this) += other;
	}

	V2 &operator+=(const V2 &other)
	{
		cout << "Operator+=, this=" << ToString() << ", other=" << other.ToString();
		x += other.x;
		y += other.y;
		cout << " -> " << this->ToString() << endl;
		return *this;
	}

	V2(initializer_list<int> il)
	{
		auto ip = il.begin();
		x = *ip;
		if (++ip == il.end())
			y = 0;
		else
			y = *ip;
		cout << "initializer_list<int> constructor -> " << ToString() << endl;
	}
};

V2::V2() : x(0.0), y(0.0)
{
	cout << "Parameterless constructor -> " << ToString() << endl;
}

V2::V2(double a, double b) : x(a), y(b)
{
	cout << "(double, double) constructor -> " << ToString() << endl;
}

int main()
{
	cout << "C++ init" << endl;

	V2 v1;			  // Parameterless constructor
	V2 v2(1.2, 3.4);  // (double, double) constructor
	V2 v3(v1);		  // copy constructor
	V2 v4 = V2(v1);	  // copy constructor
	V2 v5 = v1;		  // copy constructor
	v4 = v1;		  // Copy assignment operator
	V2 v6 = move(v5); // Move constructor 'force called'
					  //	V2 v7(v1 + v2);	  // Optimized by compiler, only one call to (double, double) constructor in operator+
	v6 = v4 + v2;	  // Move assignment operator
	V2 v7{};		  // Parameterless constructor
	V2 v8 = {1, 2};	  // initializer_list<int> constructor
	//V2 v9 {.x=3.2, .y=1.5};	// designated initialization can only be used to initialize aggregate class types

	return 0;
}
