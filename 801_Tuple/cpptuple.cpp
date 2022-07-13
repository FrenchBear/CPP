// CS801_Tuple.cpp
// Play with Tuple in C++
//
// 2022-07-13	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tuple>

using namespace std;

tuple<int, double, char> getTupleV1()
{
	return tuple<int, double, char>(5, 1.2, 'b');
}

auto getTupleV2()
{
	return make_tuple(5, 1.2, 'b');
}

// Since C++ 17
auto getTupleV3()
{
	return tuple(5, 1.2, 'b');
}

int main()
{
	cout << "C++ tuple" << endl;

	auto t1 = getTupleV1();
	auto t2 = getTupleV2();
	cout << (t1 == t2) << endl;
	cout << get<0>(t1)			   // "5"
		 << get<char>(t1) << endl; // "b"

	// Unpacking, before C++ 17
	int i;
	double d;
	// Unpack tuple into variables
	tie(i, d, ignore) = getTupleV1();
	cout << i << " " << d << endl; // "5 1.2"

	// Unpacking in C++ 17
	auto [i17, d17, c17] = getTupleV3();
	cout << i17 << endl; // "5"

	return 0;
}
