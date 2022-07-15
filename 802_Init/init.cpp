// CS802_Init.cpp
// Play with constructors and initialization in C++
//
// 2022-07-15	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <format>

using namespace std;

class V2
{
public:
	double x, y;
	V2();
	V2(double, double);
	~V2() { cout << "Destruction of " << this << endl; }

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
		cout << "Copy constructor, this=" << this << ", other=" << &other << endl;
		x = other.x;
		y = other.y;
	}

	// Copy assignment operator
	V2 &operator=(const V2 &other)
	{
		cout << "Copy assignment operator, this=" << this << ", other=" << &other << endl;
		x = other.x;
		y = other.y;
		return *this;
	}

	// Move constructor
	V2(const V2 &&other)
	{
		cout << "Move constructor, this=" << this << ", other=" << &other << endl;
		x = other.x;
		y = other.y;
		// Actually there is nothing to steal and initialize in this class
	}

	// Move assignment operator
	V2 &operator=(V2 &&other)
	{
		cout << "Move assignment operator, this=" << this << ", other=" << &other << endl;
		x = other.x;
		y = other.y;
		return *this;
		// Actually there is nothing to steal and initialize in this class
	}

	V2 operator+(const V2 &other) const
	{
		cout << "Operator+, this=" << this << ", other=" << &other << endl;
		return V2(x + other.x, y + other.y);
		// return V2(*this) += other;
	}

	V2 &operator+=(const V2 &other)
	{
		cout << "Operator+=, this=" << this << ", other=" << &other << endl;
		x += other.x;
		y += other.y;
		return *this;
	}

	V2(initializer_list<int> il)
	{
		cout << "initializer_list<int> constructor -> " << this << endl;
		int i = 0;
		x = y = 0.0;
		for (auto m : il)
		{
			switch (i)
			{
			case 0:
				x = m;
				break;
			case 1:
				y = m;
				break;
			}
			i++;
		}
	}
};

V2::V2() : x(0.0), y(0.0)
{
	cout << "Parameterless constructor -> " << this << endl;
}

V2::V2(double a, double b) : x(a), y(b)
{
	cout << "(double, double) constructor -> " << this << endl;
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
