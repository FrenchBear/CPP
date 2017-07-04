// 632 CPP Move and Forward Implementation
// Manual implementation of std::move and std::forward
// Copied (shamelessly) in fact from STL code...
//
// 2017-06-25	PV

#include <iostream>
#include <utility>		// FORWARD
#include <vector>

using namespace std;


// REMOVE_REFERENCE helper, three versions binding to T, T& and T&& give access to T
template<class _Ty>
struct REMOVE_REFERENCE
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct REMOVE_REFERENCE<_Ty&>
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct REMOVE_REFERENCE<_Ty&&>
{	// remove rvalue reference
	typedef _Ty type;
};


// MOVE template
// Return T&& from T, T& or T&&
// Note than argument cannot be const T, const T& or const T&& by definition (otherwise couldn't move it)
template<class _Ty> inline
constexpr typename REMOVE_REFERENCE<_Ty>::type&&
MOVE(_Ty&& _Arg) noexcept
{	// FORWARD _Arg as movable
	return (static_cast<typename REMOVE_REFERENCE<_Ty>::type&&>(_Arg));
}



// TEMPLATE FUNCTION FORWARD
template<class _Ty> inline
constexpr _Ty&& FORWARD(
	typename REMOVE_REFERENCE<_Ty>::type& _Arg) noexcept
{	// FORWARD an lvalue as either an lvalue or an rvalue
	return (static_cast<_Ty&&>(_Arg));
}

template<class _Ty> inline
constexpr _Ty&& FORWARD(
	typename REMOVE_REFERENCE<_Ty>::type&& _Arg) noexcept
{	// FORWARD an rvalue as an rvalue
	static_assert(!is_lvalue_reference<_Ty>::value, "bad FORWARD call");
	return (static_cast<_Ty&&>(_Arg));
}




class C {
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



int main() {
	C c1;					// Default constructor
	C c1b(c1);				// Copy constructor
	C c2 = MOVE(c1);		// Move constructor
	c1 = c2;				// Copy assignment operator
	c1 = MOVE(c2);			// Move assignment operator

	auto f = FORWARD<C>(c1);

	cout << "\n(Pause)";
	cin.get();
}
