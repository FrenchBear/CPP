// CS805_Templates.cpp
// Play with C++ templates
//
// 2022-07-19	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

// Function template
template <typename T>
void my_swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

// Class template
template <class T>
class MyBox
{
public:
	T a, b;
	void swap();
};

// if a method is defined outside of the class template, that definition must also be preceded by the template declaration.
template <class T>
void MyBox<T>::swap()
{
	T tmp = a;
	a = b;
	b = tmp;
}

// Non-type parameters
template <class T, unsigned int N>
class MyBoxNum
{
public:
	T store[N];
};

// Class template specialization
template <class T>
class MyBoxMsg
{
public:
	T a;
	void print() { std::cout << a; }
};

// bool class specialization
template <>
class MyBoxMsg<bool>
{
public:
	bool a;
	void print() { std::cout << (a ? "true" : "false"); }
};

// function template specialization
template <class T>
class MyBoxSp
{
public:
	T a;
	template <class T>
	void print()
	{
		std::cout << a;
	}
	template <>
	void print<bool>()
	{
		std::cout << (a ? "true" : "false");
	}
};

// Variable templates
template<class T>
constexpr T pi = T(3.1415926535897932384626433L);

int main()
{
	cout << "C++ 20 templates\n\n";

	int a = 1, b = 2;
	my_swap<int>(a, b); // calls int version of my_swap

	bool c = true, d = false;
	my_swap(c, d); // calls bool version of my_swap

	MyBox<string> mb1{"hello"s, "world"s};
	mb1.swap();
	cout << mb1.a << ' ' << mb1.b << endl;

	MyBoxNum<float, 10> mbn;
	cout << size(mbn.store) << endl;

	MyBoxMsg<bool> box{true};
	box.print(); // "true"
	cout << endl;

	MyBoxSp<bool> boxSp = {false};
	boxSp.print<bool>(); // "true"
	cout << endl;

	int iPi = pi<int>; // 3
	float fPi = pi<float>; // 3.14...
	double dPi = pi<double>; // 3.14...
	cout << iPi << endl << fPi << endl << dPi <<endl;

	return 0;
}
