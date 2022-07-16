// CS803_Comp20.cpp
// Play with new comparison operator <=> of C++ 20 and partial/strong ordering
//
// 2022-07-16	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <compare>

using namespace std;

// Partially ordered class, since double comparison with #NaN are undefined
class LengthDouble
{
private:
	double l;

public:
	LengthDouble(double d = 0.0) : l(d) {}
	partial_ordering operator <=>(const LengthDouble& other) const noexcept { return l <=> other.l; }
	bool operator ==(const LengthDouble& other) const noexcept { return l == other.l; }	// Operator <=> does not support == and !=
};

// Partially ordered class, since double comparison with #NaN are undefined
class LengthInt
{
private:
	int l;

public:
	LengthInt(int d = 0.0) : l(d) {}
	strong_ordering operator <=>(const LengthInt& other) const noexcept { return l <=> other.l; }
	bool operator ==(const LengthInt& other) const noexcept { return l == other.l; }	// Operator <=> does not support == and !=
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

int main()
{
	cout << "C++ <=> op" << endl;

	LengthDouble ld1(7);
	LengthDouble ld2(11);

	cout << "ld1<=>ld2 " << PartialOrderingToString(ld1 <=> ld2) << endl;
	cout << "ld1<l2    " << (ld1 < ld2) << endl;
	cout << "ld1<=l2   " << (ld1 <= ld2) << endl;
	cout << "ld1>l2    " << (ld1 > ld2) << endl;
	cout << "ld1>=l2   " << (ld1 >= ld2) << endl;
	cout << "ld1==l2   " << (ld1 == ld2) << endl;
	cout << "ld1!=l2   " << (ld1 != ld2) << endl << endl;

	LengthInt li1(7);
	LengthInt li2(11);

	cout << "li1<=>li2 " << StrongOrderingToString(li1 <=> li2) << endl;
	cout << "li1<l2    " << (li1 < li2) << endl;
	cout << "li1<=l2   " << (li1 <= li2) << endl;
	cout << "li1>l2    " << (li1 > li2) << endl;
	cout << "li1>=l2   " << (li1 >= li2) << endl;
	cout << "li1==l2   " << (li1 == li2) << endl;
	cout << "li1!=l2   " << (li1 != li2) << endl;

	return 0;
}
