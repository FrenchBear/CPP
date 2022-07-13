// CS800_Auto.cpp
// Play with auto and decltype
//
// 2022-07-13	PV		First version

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

#include <iostream>
#include <string>
#include <vector>

int main()
{
	cout << "C++ auto" << endl;

	int i = 0;
	auto ai = i;
	auto& ari = i;
	const auto& cari = i;

	decltype(i) j = i;
	decltype(ai) aj = ai;
	decltype(ari) arj = ari;
	decltype(cari) carj = cari;

	decltype(auto) k = i;
	decltype(auto) ak = ai;
	decltype(auto) ark = ari;
	decltype(auto) cark = cari;

	// auto&& is special, it means either & or && depending if the target is a l-value or a r-value
	auto&& ral = i;			// int &
	auto&& ral2 = i + 1;	// int &&
	auto&& ral3 = vector<int>{ 1,2,3 };	// vector<int> &&

	return 0;
}
