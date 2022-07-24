// CS807_io.cpp
// Play with C++ input/output model
//
// DO NOT SAVE THIS FILE AS UTF-8 WITH BOM (VS2022 default when saving UTF-8), otherwise output is garbled...
// 
// 2022-07-24	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;



#include <iostream>
using namespace std;
// Génère une chaîne décrivant les états d’un flux
string etats(const ios& flux)
{
	string r;
	if (flux.bad()) r += "bad ";
	if (flux.fail()) r += "fail ";
	if (flux.eof()) r += "eof ";
	if (r.empty()) r += "good ";
	return r;
}

void TestCoutStatus()
{
	cout << "Entrez des nombres entiers, autre chose termine la boucle, ^D/^Z termine stdin.\n\n";
	int k;
	cout << "états de cin=" << etats(cin) << endl;

	while (cin >> k, cin.good())
		cout << "2^" << k << "=" << (1 << k) << endl;
	cout << "états de cin=" << etats(cin) << endl;
}

int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 I/O\n\n";
	TestCoutStatus();

	return 0;
}
