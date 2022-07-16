// CS803_Comp20.cpp
// Play with new comparison operator <=> of C++ 20 and partial/strong ordering and designated initialization
//
// 2022-07-16	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <compare>

#ifdef _WIN32
#include <format>       // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

// Partially ordered class, since double comparison with #NaN are undefined
class LengthDouble
{
private:
	double l;

public:
	LengthDouble(double d = 0.0) : l(d) {}
	partial_ordering operator <=>(const LengthDouble& other) const noexcept { return l <=> other.l; }	// Defines < <= > >=
	bool operator ==(const LengthDouble& other) const noexcept { return l == other.l; }					// Defines == and !=
};

// Strongly ordered class, since int is a strongly ordered type
class LengthInt
{
private:
	int l;

public:
	LengthInt(int d = 0.0) : l(d) {}
	strong_ordering operator <=>(const LengthInt& other) const noexcept { return l <=> other.l; }		// Defines < <= > >=
	bool operator ==(const LengthInt& other) const noexcept { return l == other.l; }					// Defines == and !=
};

const char* PartialOrderingToString(partial_ordering res)
{
	if (res == partial_ordering::unordered)
		return "unordered";
	else if (res == partial_ordering::equivalent)
		return "equivalent";
	else if (res == partial_ordering::less)
		return "less";
	else if (res == partial_ordering::greater)
		return "greater";

	return "???";
}

const char* StrongOrderingToString(strong_ordering res)
{
	if (res == strong_ordering::equal)
		return "equal";
	else if (res == strong_ordering::equivalent)
		return "equivalent";
	else if (res == strong_ordering::less)
		return "less";
	else if (res == strong_ordering::greater)
		return "greater";

	return "???";
}


// C++ 20 auto-generated operators and designated initialization (since it's a simple aggregate type)
class Version
{
public:
	int major = 0, minor = 0, build = 0;
	strong_ordering operator <=>(const Version& other) const noexcept = default;		// Defines < <= > >=
	bool operator ==(const Version& other) const noexcept = default;					// Defines == and !=

	string ToString() { return format("{}.{}.{}", major, minor, build); }

	static void Test(Version&& v1, Version&& v2)
	{
		cout << v1.ToString() << [](auto x, auto y) { return (x < y) ? " < " : (x > y) ? " > " : " = "; }(v1, v2) << v2.ToString() << endl;
	}
};


int main()
{
	cout << "C++ 20 <=> operator\n\n";

	LengthDouble ld1(7);
	LengthDouble ld2(11);

	cout << "Partial order\n";
//	cout << "partial_ordering::unordered  " << static_cast<int>(partial_ordering::unordered._Value) << endl;
//	cout << "partial_ordering::equivalent " << static_cast<int>(partial_ordering::equivalent._Value) << endl;
//	cout << "partial_ordering::less       " << static_cast<int>(partial_ordering::less._Value) << endl;
//	cout << "partial_ordering::greater    " << static_cast<int>(partial_ordering::greater._Value) << endl << endl;


	cout << "ld1<=>ld2 " << PartialOrderingToString(ld1 <=> ld2) << endl;
	cout << "ld1<l2    " << (ld1 < ld2) << endl;
	cout << "ld1<=l2   " << (ld1 <= ld2) << endl;
	cout << "ld1>l2    " << (ld1 > ld2) << endl;
	cout << "ld1>=l2   " << (ld1 >= ld2) << endl;
	cout << "ld1==l2   " << (ld1 == ld2) << endl;
	cout << "ld1!=l2   " << (ld1 != ld2) << endl << endl;

	cout << "Strong order\n";

//	cout << "strong_ordering::equal      " << static_cast<int>(strong_ordering::equal._Value) << endl;
//	cout << "strong_ordering::equivalent " << static_cast<int>(strong_ordering::equivalent._Value) << endl;
//	cout << "strong_ordering::less       " << static_cast<int>(strong_ordering::less._Value) << endl;
//	cout << "strong_ordering::greater    " << static_cast<int>(strong_ordering::greater._Value) << endl << endl;

	LengthInt li1(7);
	LengthInt li2(11);

	cout << "li1<=>li2 " << StrongOrderingToString(li1 <=> li2) << endl;
	cout << "li1<l2    " << (li1 < li2) << endl;
	cout << "li1<=l2   " << (li1 <= li2) << endl;
	cout << "li1>l2    " << (li1 > li2) << endl;
	cout << "li1>=l2   " << (li1 >= li2) << endl;
	cout << "li1==l2   " << (li1 == li2) << endl;
	cout << "li1!=l2   " << (li1 != li2) << endl << endl;

	cout << "Auto-generated comparisons\n";
	Version::Test(Version{ 1,2,3 }, Version{ 1,2,4 });
	Version::Test(Version{ .major = 3,.minor = 5,.build = 0 }, Version{ .major = 1,.minor = 2,.build = 4 });	// designated initialization
	Version::Test(Version{ 2,5 }, Version{ 2,5,0 });

	return 0;
}
