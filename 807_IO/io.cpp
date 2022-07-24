// CS807_io.cpp
// Play with C++ input/output model
//
// DO NOT SAVE THIS FILE AS UTF-8 WITH BOM (VS2022 default when saving UTF-8), otherwise output is garbled...
// 
// 2022-07-24	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <string>
#include <ios>
#include <iomanip>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;



#include <iostream>
using namespace std;
// Génère une chaîne décrivant les états d'un flux
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

// custom iomanip, no parameter
template < typename C, typename T>
basic_ostream<C, T>& compilation_date(basic_ostream<C, T>& os)
{
	return os << __DATE__ << " " << __TIME__ << flush;
}



class binaire
{
private:
	int v_;		  // Valeur à imprimer
	int ndigits_; // Nombre de bits à prendre en compte
	bool printZ_; // Vrai si les zéros de tête sont requis
public:
	binaire(int k, int sz = sizeof(int) * 8) : v_(k), ndigits_(sz), printZ_(true)
	{
		if (ndigits_ == 0)
		{
			printZ_ = false; ndigits_ = sizeof(int) * 8;
		}
	}
	friend ostream& operator<<(ostream& os, const binaire& bs);
};


ostream& operator<<(ostream& os, const binaire& bs)
{
	bool bit1_found;
	unsigned int mask;

	for (mask = 1 << (bs.ndigits_ - 1), bit1_found = bs.printZ_; mask; mask >>= 1)
	{
		if (static_cast<unsigned int>(bs.v_) & mask)
		{
			bit1_found = true; os << '1';
		}
		else if (bit1_found || mask == 1)
			os << '0';
	}
	return os;
}

int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 I/O\n\n";

	// TestCoutStatus();

	cout << "boolalpha, noboolalpha\n";
	cout << boolalpha << true << " " << noboolalpha << true << endl;
	cout << boolalpha << false << " " << noboolalpha << false << endl;
	cout << endl;

	cout << "dec, hex, oct; showbase, noshowbase\n";
	int n = 51966;
	cout << "noshowbase: " << noshowbase << "dec:" << dec << n << ", hex:" << hex << n << ", oct:" << oct << n << endl;
	cout << "showbase: " << showbase << "dec:" << dec << n << ", hex:" << hex << n << ", oct:" << oct << n << endl;
	cout << endl;

	cout << "setbase\n";		// same as oct, dec and hex for 8,10 and 16; other values restore default (dec, input with base prefix)
	for (auto k : { 8,10,16,0 })
		cout << "base=" << dec << k << " : " << setbase(k) << 254 << endl;
	cout << endl;

	cout << "showpoint, noshowpoint\n";
	double d = 33.0, q = 33.1;
	cout << "showpoint: " << showpoint << d << " " << q << endl;
	cout << "noshowpoint: " << noshowpoint << d << " " << q << endl;
	cout << endl;

	cout << "showpos, noshowpos\n";
	double pi = 3.14159;
	cout << "showpos: " << showpos << pi << " " << 0.0 << " " << -pi << endl;
	cout << "noshowpos: " << noshowpos << pi << " " << 0.0 << " " << -pi << endl;
	cout << endl;

	cout << "fixed, scientific, defaultfloat, hexfloat\n";
	double x = 0.00002;
	cout << "fixed: " << fixed << x << endl;
	cout << "scientific: " << scientific << x << endl;
	cout << "defaultfloat: " << defaultfloat << x << endl;
	cout << "hexfloat: " << hexfloat << x << endl;
	cout << endl;

	cout << "uppercase, nouppercase\n";
	double y = 300.1234;
	int k = -559038737;
	cout << scientific << hex;
	cout << "uppercase: " << uppercase << y << " " << k << endl;
	cout << "nouppercase: " << nouppercase << y << " " << k << endl;
	cout << endl;

	// unitbuf, nounitbuf		nounitbuf -> no autoflush (default for cerr)

	// skipws, noskipws			heading spaces are skipped or not when using cin
	// ws						explicitly skip head characters

	cout << "left, right, internal; setw; setfill\n";
	int m = -77; n = 24;
	cout << "left:     " << left << hex << showbase << setfill('#') << setw(12) << n << "   " << dec << setfill(' ') << setw(6) << m << endl;
	cout << "right:    " << right << hex << showbase << setfill('#') << setw(12) << n << "   " << dec << setfill(' ') << setw(6) << m << endl;
	cout << "internal: " << internal << hex << showbase << setfill('#') << setw(12) << n << "   " << dec << setfill(' ') << setw(6) << m << endl;
	cout << endl;

	// in input mode, setw doesn't truncate numeric values longer than width
	cout << "setw input mode\n";
	istringstream is;
	is.str("0123456789");
	is.seekg(0);
	is >> setw(3) >> k;
	cout << k << endl;			// 123456789
	is.seekg(0);
	string s3;
	is >> setw(3) >> s3;
	cout << s3 << endl;			// 012
	cout << endl;

	// flush, endl				// endl inserts \n and flush

	cout << "ends\n";			// ends insert a nul character
	ostringstream os;
	os << "AAA" << ends << "BBB" << ends << "CCC" << ends << flush;
	string s = os.str();
	for (auto c : s)
		cout << hex << showbase << static_cast<int>(c) << " ";
	cout << endl << endl;

	cout << "setprecision 6, 0, 2 for 1234.56789\n";
	// fixed or scientific: define number of decimals
	// default: define number of significant digits
	x = 1234.56789;
	for (auto mode : { fixed, scientific, defaultfloat })
		cout << (mode == fixed ? "fixed: " : mode == scientific ? "scientific: " : "defaultfloat: ")
		<< mode << setprecision(6) << x << "   " << setprecision(0) << x << "   " << setprecision(2) << x << endl;
	cout << endl;

	cout << "quoted\n";
	string so, si = "Liberté Égalité Fraternité";
	stringstream flux;
	flux << si;
	flux >> so;
	cout << so << endl;
	stringstream qflux; // " implicite
	qflux << quoted(si);
	qflux >> quoted(so);
	cout << so << endl;
	stringstream bflux; // caractère |
	bflux << quoted(si, '|');
	bflux >> quoted(so, '|');
	cout << so << endl;
	stringstream xflux; // caractères < et >
	xflux << quoted(si, '<', '>');
	xflux >> quoted(so, '<', '>');
	cout << endl;

	cout << "Custom manip\n";
	cout << "Version : " << compilation_date << endl;
	cout << endl;
	cout << "Repr. de -1 = " << binaire(-1) << endl;
	cout << "Repr. de 0 = " << binaire(0) << endl;
	cout << "Repr. de 0 = " << binaire(0, 0) << endl;
	cout << "Repr. minimale de 1500 = " << binaire(1500, 0) << endl;
	cout << "Repr. de 1500 (16 bits) = " << binaire(1500, 16) << endl;
	cout << endl;

	return 0;
}
