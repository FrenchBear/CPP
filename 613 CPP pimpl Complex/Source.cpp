// CPP613 pimpl
// Pimpl idio (pointer to implementation) from "Welcome back to C++" example
//
// In this example, Complex.cpp contains private implementation of a Complex number class,
// that can be either based on private rectangular or polar corrdinates.
// Changing coordinates model in private implementation located in Complex.cpp will
// only lead to recompilation of Complex.cpp, no change is visible in Complex.h, 
// avoiding cascade recompilations/rebuilds after an implementation change.
//
// 2017-02-02	PV	First version, also worked hard to output UTF-16/Unicode on console...

#include <Windows.h>

#include <fcntl.h>  
#include <io.h>  
#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>
#include "Complex.h"

using namespace std;


void Test() {
	Complex c1(3.0);
	c1 = Complex(2, 1) + Complex(1, 2);
	/*
	Complex c1(3.0);
	wcout << "c1: " << c1 << endl;
	Complex c2(0.0, 4.0);
	wcout << "c2: " << c2 << endl;
	Complex c3 = c1 + c2;
	c3 = move(c3);
	wcout << "c3=c1+c2: " << c3 << endl;
	c3 += Complex(2.0, 1.0);
	wcout << "c3+Complex(2,1): " << c3 << endl;
	c3 = -c3;
	wcout << "-c3: " << c3 << endl;

	Complex c(3.0, 4.0);
	wcout << L"Module(" << c.ToWString() << L") = " << c.Module() << endl;

	Complex cs("-2.5+3i");
	wcout << "cs: " << cs << endl;
	wcout << "cs.ToWString(): " << cs.ToWString() << endl;
	wcout << "(wstring)cs: " << (wstring)cs << endl;
	wcout << "wstring(cs): " << wstring(cs) << endl;
	wcout << "static_cast<wstring>(cs): " << static_cast<wstring>(cs) << endl;

	Complex j = 2.0_i;
	wcout << "j: " << j << endl;
	wcout << "j(1.5): " << j(1.5) << endl;
	*/
}


int main() {
	//setlocale(LC_ALL, "");
	//SetConsoleOutputCP(CP_UTF8);
	//_setmode(_fileno(stdout), _O_U8TEXT);
	//printf(u8"Σφε\n");
	//cout << u8"Σφε" << endl;

	// For wcout and wstrings
	// Without this, unicode characters block output on wcout
	// With this, wcout can output unicode characters...  but then cout crashes on an internal error!!!!!!!!!!!!!!
	_setmode(_fileno(stdout), _O_U16TEXT);

	Test();

	wcout << L"\n(Pause)";
	wcin.get();
	return 0;
}
