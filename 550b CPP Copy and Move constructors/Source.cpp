// 550b C++ Copy and Move constructors
// More examples
// 2017-01-22	PV

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class C
{
private:
	vector<int> v;

public:
	// Default constructor
	C() : v(3)
	{
		cout << "C Default constructor\n";
	}

	// Unary constructor
	C(int initialValue) : v(3, initialValue)
	{
		cout << "C Unary constructor\n";
	}

	// Copy constructor
	C(C const& other)
	{
		cout << "C Copy constructor\n";
		v = other.v;
	}

	// Move constructor
	C(C&& other)
	{
		cout << "C Move constructor\n";
		v = std::move(other.v);
	}

	// Destructor
	~C()
	{
		cout << "C Destructor\n";
	}

	// Copy assignment
	C& operator=(const C& other)
	{
		cout << "C Copy assignment operator\n";
		v = other.v;
		return *this;
	}

	// Move assignment
	C& operator=(C&& other)
	{
		cout << "C Move assignment operator\n";
		v = std::move(other.v);
		return *this;
	}
};


C fn() {
	return C{};
}


int main() {
	cout << "default constructor\n";
	C foo;

	cout << "\ncopy constructor\n";
	C barr(foo);

	cout << "\ncopy constructor\n";
	C bar = foo;

	cout << "\nmove constructor\n";
	C baz = std::move(fn());

	cout << "\ncopy assignment\n";
	foo = bar;

	cout << "\nmove assignment \n";
	baz = C();


	cout << "\n(Pause)";
	cin.get();

	return 0;
}
