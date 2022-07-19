// CS805_Templates.cpp
// Play with C++ templates
//
// 2022-07-19	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <concepts>
#include <type_traits>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

// Concept declaration
template <class T>
concept MyIntegral = std::is_integral_v<T>;
// bool, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long

template <MyIntegral T>
bool is_positive(T a)
{
	return a > 0;
}

// Abbreviated function template using auto placeholder
bool is_positive2(std::integral auto a)
{
	return a>0;
}

// Other concept
template <class T>
concept Equal = requires(T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};
template <Equal T>
bool areEqual(T x, T y)
{
	return x == y;
}

int main()
{
	cout << "C++ 20 concepts\n\n";

	cout << is_positive(5) << endl; // ok, int satisfies MyIntegral
	// is_positive("Hi"); // error, string does not satisfy MyIntegral
	cout << is_positive2(-3L) << endl;
	cout << areEqual(1, 1) << endl;

	return 0;
}
