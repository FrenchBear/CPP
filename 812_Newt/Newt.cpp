// CS812_Newt.cpp
// C++ simulation of Newt display
//
// 2023-01-01	PV		First version

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ios>
#include <vector>

#ifdef _WIN32
#include <format> // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;

class Display
{
private:
	string title;
	vector<string> lines;
	string btn_Up, btn_Down;
	string btn_B1, btn_B2, btn_B3, btn_B4;
	string btn_R1, btn_R2, btn_R3, btn_R4;

public:
	Display(string title, vector<string> lines, 
			string btn_Up, string btn_Down,
			string btn_B1, string btn_B2, string btn_B3, string btn_B4,
			string btn_R1, string btn_R2, string btn_R3, string btn_R4):
		title(title), lines(lines),
		btn_Up(btn_Up), btn_Down(btn_Up),
		btn_B1(btn_B1), btn_B2(btn_B2), btn_B3(btn_B3), btn_B4(btn_B4),
		btn_R1(btn_R1), btn_R2(btn_R2), btn_R3(btn_R3), btn_R4(btn_R4)
	{ }

	inline string gl(size_t n)
	{
		return (n < lines.size()) ? lines[n] : "";
	}

	void Print()
	{
		ostringstream l[13];

		l[0] << "+------------------------------------------+----+";
		l[1] << "| " << setw(41) << left << title <<       "| R1 |";
		l[2] << "| ---------------------------------------- |    |";
		l[3] << "| " << setw(41) << left << gl(0) <<       "+----+";
		l[4] << "| " << setw(41) << left << gl(1) <<       "| R2 |";
		l[5] << "| " << setw(41) << left << gl(2) <<       "|    |";
		l[6] << "| " << setw(41) << left << gl(3) <<       "+----+";
		l[7] << "| " << setw(41) << left << gl(4) <<       "| R3 |";
		l[8] << "+---+ " << setw(37) << left << gl(5) <<   "|    |";
		l[9] << "| ^ | " << setw(37) << left << gl(6) <<   "+----+";
		l[10]<< "+---+--------------------------------------+ R4 |";
		l[11]<< "| v |    B1   |    B2   |    B3   |    B4  |    |";
		l[12]<< "+---+-------------------------------------------+";

		for (size_t i = 0; i < 13; i++)
			cout << l[i].str() << endl;
	}

};



int main()
{
#ifdef _WIN32
	system("CHCP 65001 >NUL");
#endif

	cout << "C++ 20 Newt\n\n";

	auto d1 = Display("Ecran principal", vector<string> {"line 1", "line 2", "line 3", "line 4"}, "up", "dn",
		"B1", "B2", "B3", "B4", "R1", "R2", "R3", "R4");
	d1.Print();

	return 0;
}
