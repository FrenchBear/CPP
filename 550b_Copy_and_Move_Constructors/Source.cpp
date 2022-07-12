// 550b C++ Copy and Move constructors
// More examples
//
// 2017-01-22	PV
// 2017-04-29	PV		GitHub and Linux
// 2021-09-14	PV		Visual Studio 2022
// 2022-07-13	PV		Modern C++ cleanup

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
	C(C&& other) noexcept
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
	C& operator=(C&& other) noexcept
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


#ifdef _WIN32
	cout << "\n(Pause)";
	cin.get();
#endif
	return 0;
}
