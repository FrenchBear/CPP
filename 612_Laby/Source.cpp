// C12 CPP Laby.cpp
// C++ implementation of labyrinth using digging method
//
// 2016-06-03	PV
// 2017-01-27	PV	Windows version (CPP 612 Laby)
// 2017-02-01	PV	Added recursive dividing algorithm
// 2017-04-29	PV	GitHub and Linux

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <stack>
#include <string.h>

#ifdef _WIN32
// Windows
#include <tchar.h>
#include "Xgetopt.h"

#define DefaultASCIIMode true
#define DefaultMonochrome true

#pragma warning(disable: 4566)		// Warning	C4566: Character represented by universal - character - name '\u2502' cannot be represented in the current code page(1252)
#else
// Linux
#include <getopt.h>

#define DefaultASCIIMode false
#define DefaultMonochrome false
#endif

using namespace std;

int Algorithm = 1;
bool IsASCIIMode = DefaultASCIIMode;
bool IsMonochrome = DefaultMonochrome;
bool ShowSolution = false;
bool IsDetailedBuild = false;



struct Square {
public:
	int Walls;

	union {
		int IsVisited;
		int DirSolution;
		int IsSolution;
	};

	// Bitmask for Walls member
	enum WallsEnum { TopWall = 1, RightWall = 2, BottomWall = 4, LeftWall = 8 };
};

int rows = 10, cols = 20;
struct Square **Cells;
int colStart, colEnd;

void SetWall(int r, int c, Square::WallsEnum w) {
	Cells[r][c].Walls |= w;
	if (w & Square::RightWall && c < cols - 1) Cells[r][c + 1].Walls |= Square::LeftWall;
	if (w & Square::LeftWall && c > 0) Cells[r][c - 1].Walls |= Square::RightWall;
	if (w & Square::BottomWall && r < rows - 1) Cells[r + 1][c].Walls |= Square::TopWall;
	if (w & Square::TopWall && r > 0) Cells[r - 1][c].Walls |= Square::BottomWall;
}

void ClearWall(int r, int c, Square::WallsEnum w) {
	Cells[r][c].Walls &= ~w;
	if (w & Square::RightWall && c < cols - 1) Cells[r][c + 1].Walls &= ~Square::LeftWall;
	if (w & Square::LeftWall && c > 0) Cells[r][c - 1].Walls &= ~Square::RightWall;
	if (w & Square::BottomWall && r < rows - 1) Cells[r + 1][c].Walls &= ~Square::TopWall;
	if (w & Square::TopWall && r > 0) Cells[r - 1][c].Walls &= ~Square::BottomWall;
}



// ======================================================================================
// Generating, recursive divide

// Recursively draw a random vertical wall with a random opening, then
// a random horizontal wall in the two areas, and repeat until width or
// height of the area is only 1 row or column
void BuildWall(int cmin, int cmax, int rmin, int rmax, bool isVertical)
{
	if (IsDetailedBuild)
		cout << "BuildWall cmin=" << cmin << ", cmax=" << cmax << ", rmin=" << rmin << ", rmax=" << rmax << ", " << (isVertical ? "Vertical" : "Horizontal") << endl;

	if (rmin == rmax || cmin == cmax)
	{
		if (IsDetailedBuild)
			cout << "rmin==rmax or cmin==cmax, nothing to do" << endl;
		return;
	}

	if (isVertical)
	{
		if (cmax > cmin)
		{
			int c = cmin + rand() % (cmax - cmin);
			int rHole = rmin + rand() % (rmax - rmin);

			if (IsDetailedBuild)
				cout << "Vertical wall at c=" << c << " between rows " << rmin << " and " << rmax << " with a hole at r=" << rHole << endl;
			for (int r = rmin; r <= rmax; r++)
				if (r != rHole)
					SetWall(r, c, Square::RightWall);

			BuildWall(cmin, c, rmin, rmax, false);
			BuildWall(c + 1, cmax, rmin, rmax, false);
		}
		else
			if (IsDetailedBuild)
				cout << "No vertical build since cmin==cmax" << endl;
	}
	else
	{
		if (rmax > rmin)
		{
			int r = rmin + rand() % (rmax - rmin);
			int cHole = cmin + rand() % (cmax - cmin);

			if (IsDetailedBuild)
				cout << "Horizontal wall at r=" << r << " between cols " << cmin << " and " << cmax << " with a hole at c=" << cHole << endl;
			for (int c = cmin; c <= cmax; c++)
				if (c != cHole)
					SetWall(r, c, Square::TopWall);

			BuildWall(cmin, cmax, rmin, r, true);
			BuildWall(cmin, cmax, r + 1, rmax, true);
		}
		else
			if (IsDetailedBuild)
				cout << "No horizontal build since rmin==rmax" << endl;
	}
}

void GenerateRecursiveDividing() {
	// Clear all the walls
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++) {
			if (c < cols - 1) Cells[r][c].Walls &= ~Square::RightWall;
			if (r < rows - 1) Cells[r][c].Walls &= ~Square::BottomWall;
			if (r > 0) Cells[r][c].Walls &= ~Square::TopWall;
			if (c > 0) Cells[r][c].Walls &= ~Square::LeftWall;
		}

	BuildWall(0, cols - 1, 0, rows - 1, true);
}


// --------------------------------------------------------------------------------------
// Generating, original method

void GenerateOriginalMethod() {
	int remaining = rows * cols;// # of cells remaining to open
	int first = true;
	while (remaining > 0) {
		int r, c;

		// We start with an already visited cell
		do {
			r = rand() % rows;
			c = rand() % cols;
			if (first) {// Except for the very first one, since nothing has been visited yet
				first = false;
				break;
			}
		} while (!Cells[r][c].IsVisited);

		// Dig r, c
		int dir;// Direction: 0=up, 1=right, 2=down, 3=left
		for (;;) {
			if (!Cells[r][c].IsVisited) {
				Cells[r][c].IsVisited = true;
				remaining--;
			}
			dir = rand() % 4;
			int rt = 0, ct = 0;
			int ntest = 1;
			int dirmask = 0xF;

			for (;;) {
				dirmask &= ~(1 << dir);
				switch (dir) {
					case 0:rt = r - 1; ct = c; break;
					case 1: rt = r; ct = c + 1; break;
					case 2:rt = r + 1; ct = c; break;
					case 3: rt = r; ct = c - 1; break;
				}
				if (rt >= 0 && rt < rows && ct >= 0 && ct < cols)
					if (!Cells[rt][ct].IsVisited)
						break;	// Found an unvisited neighbor, good!

				ntest++;		// Not found an unvisited neighbor, chose another direction
				if (ntest == 5)
					goto NextGallery;// Can't use "continue" to continue an outer nested loop

				for (;;) {
					dir = rand() % 4;
					if (dirmask&(1 << dir))
						break;
				}
			}

			// Erase border
			Square::WallsEnum WallMaskCell;
			switch (dir)
			{
				case 0:	WallMaskCell = Square::TopWall; break;
				case 1:	WallMaskCell = Square::RightWall; break;
				case 2:	WallMaskCell = Square::BottomWall; break;
				case 3:	WallMaskCell = Square::LeftWall; break;
			}
			assert(rt >= 0 && rt < rows && ct >= 0 && ct < cols);
			ClearWall(r, c, WallMaskCell);

			r = rt;
			c = ct;
		}

	NextGallery:;
	}
}


// --------------------------------------------------------------------------------------
// Generating

void Generate() {
	// Crate array of cells and set all walls
	Cells = new Square *[rows];
	for (int r = 0; r < rows; r++) {
		Cells[r] = new Square[cols];
		for (int c = 0; c < cols; c++) {
			Cells[r][c].Walls = Square::TopWall | Square::RightWall | Square::BottomWall | Square::LeftWall;
			Cells[r][c].IsVisited = false;
		}
	}

	switch (Algorithm)
	{
		case 1:	GenerateOriginalMethod(); break;
		case 2: GenerateRecursiveDividing(); break;
	}

	// Open 1 cell on 1st and last row
	colStart = rand() % cols;
	colEnd = rand() % cols;
	Cells[0][colStart].Walls &= ~Square::TopWall;
	Cells[rows - 1][colEnd].Walls &= ~Square::BottomWall;
}


// ======================================================================================
// Printing

const char *coulOn() {
	if (IsMonochrome)
		return "";
	else
		return "\033[32m";
}

const char *coulOff() {
	if (IsMonochrome)
		return "";
	else
		return "\033[37m";
}

const char *CellEmpty() {
	return "  ";
}

const char *CellSolution() {
	if (IsASCIIMode)
		return "**";
	else
		return "\u25cf\u25cf";
	//return "\u25a0\u25a0";
}

const char *VerticalWall() {
	if (IsASCIIMode)
		return "|";
	else
		return "\u2502";
}

const char *VerticalSolution() {
	if (IsASCIIMode)
		return "*";
	else
		return "\u25cf";
	//return "\u25a0";
}

const char *VerticalEmpty() {
	return " ";
}

const char *HorizontalWall() {
	if (IsASCIIMode)
		return "--";
	else
		return "\u2500\u2500";
}

const char *HorizontalSolution() {
	if (IsASCIIMode)
		return "**";
	else
		return "\u25cf\u25cf";
	//return "\u25a0\u25a0";
}

const char *HorizontalEmpty() {
	return "  ";
}

int GetTopWall(int r, int c) {
	if (c < 0 || c >= cols)
		return 0;

	if (r >= 0 && r < rows)
		return Cells[r][c].Walls & Square::TopWall;
	else if (r == rows)
		return Cells[r - 1][c].Walls & Square::BottomWall;
	else
		return 0;
}

int GetLeftWall(int r, int c) {
	if (r < 0 || r >= rows)
		return 0;

	if (c >= 0 && c < cols)
		return Cells[r][c].Walls & Square::LeftWall;
	else if (c == cols)
		return Cells[r][c - 1].Walls & Square::RightWall;
	else
		return 0;
}

const char * GetCorner(int up, int right, int down, int left) {
	if (IsASCIIMode)
		return "+";
	else {
		static const char *corners[16] = {
			" ",// ----
			"\u2502",// U--- = UD
			"\u2500",// -R-- = RL
			"\u2514",// UR--
			"\u2502",// --D- = UD
			"\u2502",// U-D-
			"\u250c",// -RD-
			"\u251c",// URD-
			"\u2500",// ---L = RL
			"\u2518",// U--L
			"\u2500",// -R-L
			"\u2534",// UR-L
			"\u2510",// --DL
			"\u2524",// U-DL
			"\u252c",// -RDL
			"\u253c" // URDL
		};

		return corners[(up ? 1 : 0) + (right ? 2 : 0) + (down ? 4 : 0) + (left ? 8 : 0)];
	}
}


// Prints top left corner of [r][c]
// It is Ok for r to get value rows and c value cols (while not present in Cells)
void PrintCorner(int r, int c) {
	int up = GetLeftWall(r - 1, c);
	int right = GetTopWall(r, c);
	int down = GetLeftWall(r, c);
	int left = GetTopWall(r, c - 1);

	cout << GetCorner(up, right, down, left);
}

int IsSolution(int r, int c) {
	if (!ShowSolution) return false;
	return (r < 0 || r >= rows || c < 0 || c >= cols) ? false : Cells[r][c].IsSolution;
}

void PrintLeftWall(int r, int c) {
	if (c == cols)
		cout << VerticalWall();
	else if (Cells[r][c].Walls&Square::LeftWall)
		cout << VerticalWall();
	else if (IsSolution(r, c) && IsSolution(r, c - 1))
		cout << coulOn() << VerticalSolution() << coulOff();
	else
		cout << VerticalEmpty();
}

void PrintTopWall(int r, int c) {
	if (r == rows && c == colEnd) {
		if (ShowSolution)
			cout << coulOn() << HorizontalSolution() << coulOff();
		else
			cout << HorizontalEmpty();
	}
	else if (r == rows && c != colEnd)
		cout << HorizontalWall();
	else if (Cells[r][c].Walls&Square::TopWall)
		cout << HorizontalWall();
	else if (IsSolution(r, c) && ((r == 0 && c == colStart) || IsSolution(r - 1, c)))
		cout << coulOn() << HorizontalSolution() << coulOff();
	else
		cout << HorizontalEmpty();
}

void PrintCell(int r, int c) {
	if (IsSolution(r, c))
		cout << coulOn() << CellSolution() << coulOff();
	else
		cout << CellEmpty();
}


void Print() {
	for (int r = 0; r < rows; r++) {
		// row top walls
		for (int c = 0; c < cols; c++) {
			PrintCorner(r, c);
			PrintTopWall(r, c);
		}
		PrintCorner(r, cols);
		cout << endl;
		// row left/right walls
		for (int c = 0; c < cols; c++) {
			PrintLeftWall(r, c);
			PrintCell(r, c);
		}
		PrintLeftWall(r, cols);
		cout << endl;
	}
	// Last row
	for (int c = 0; c < cols; c++) {
		PrintCorner(rows, c);
		PrintTopWall(rows, c);
	}
	PrintCorner(rows, cols);
	cout << endl;
}



// ======================================================================================
// Solving

// Non-recursive solver using a stack
void Solve() {
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			Cells[r][c].DirSolution = -1;

	int rStart = 0, cStart = colStart, rEnd = rows - 1, cEnd = colEnd;

	stack<int> rst;
	stack<int> cst;
	rst.push(rStart);
	cst.push(cStart);

	do {
		int r = rst.top();
		int c = cst.top();

		int dir = ++Cells[r][c].DirSolution;
		if (dir < 4) {
			int rt = 0, ct = 0;

			switch (dir) {
				case 0:rt = r - 1; ct = c; break;
				case 1: rt = r; ct = c + 1; break;
				case 2:rt = r + 1; ct = c; break;
				case 3: rt = r; ct = c - 1; break;
			}

			if (rt >= 0 && rt < rows && ct >= 0 && ct < cols)
				if (!(Cells[r][c].Walls&(1 << dir))) {
					if (rt == rEnd && ct == cEnd) {
						// Flag last cell
						Cells[rt][ct].DirSolution = 2;// Going down

													  // Clean-up solution
						for (r = 0; r < rows; r++)
							for (c = 0; c < cols; c++)
								Cells[r][c].IsSolution = (Cells[r][c].DirSolution >= 0 && Cells[r][c].DirSolution < 4) ? 1 : 0;

						return;
					}
					if (Cells[rt][ct].DirSolution < 0) {
						rst.push(rt);
						cst.push(ct);
					}
				}
		}
		else
		{
			// Explored all directions, done with this cell
			rst.pop();
			cst.pop();
		}
	} while (rst.size() > 0);
}


// ======================================================================================
// Main, options processing

// Simple helper
inline bool isInteger(const char *s) {
	if ((s == NULL) || (s[0] == 0) || ((!isdigit(s[0]) && (s[0] != '-') && (s[0] != '+')))) return false;
	char *p;
	strtol(s, &p, 10);
	return *p == 0;
}


int main(int argc, char **argv) {
	int c;

	while ((c = getopt(argc, argv, "amhsdva:r:c:")) != -1)
		switch (c)
		{
			case 'h':
				cerr << "Usage: laby [-h] [-A 1|2] [-a] [-m] [-s] [-d] [-v] [-r rows] [-c cols]\n"
					"-h       Shows this message\n"
					"-A algo  Select algorithm: 1=original (default), 2=recursive divide\n"
					"-a       ASCII output\n"
					"-m       Monochrome (no color) output\n"
					"-s       Shows solution\n"
					"-d       Shuffle random generator\n"
					"-v       Verbose, shows information during build\n"
					"-r rows  Number of rows in [5..100], default 10\n"
					"-c cols  Number of columns in [5..100], default 20\n";
				return 1;

			case 'a':
				IsASCIIMode = true;
				break;

			case 'm':
				IsMonochrome = true;
				break;

			case 's':
				ShowSolution = true;
				break;

			case 'd':
				srand((unsigned int)time(NULL));
				break;

			case 'r':
				if (!isInteger(optarg)) {
					cerr << "laby: rows must be an integer" << endl;
					return 1;
				}
				rows = strtol(optarg, NULL, 10);
				if (rows < 5 || rows>100) {
					cerr << "laby: rows must be in 5..100 range" << endl;
					return 1;
				}
				break;

			case 'c':
				if (!isInteger(optarg)) {
					cerr << "laby: cols must be an integer" << endl;
					return 1;
				}
				cols = strtol(optarg, NULL, 10);
				if (cols < 5 || cols>100) {
					cerr << "laby: cols must be in 5..100 range" << endl;
					return 1;
				}
				break;

			case 'A':
				if (strcmp(optarg, "1") == 0)
					Algorithm = 1;
				else if (strcmp(optarg, "2") == 0)
					Algorithm = 2;
				else {
					cerr << "laby: Only algorithms 1 and 2 are supported" << endl;
					return 1;
				}
				break;

			case '?':
				if (optopt == 'r' || optopt == 'c')
					cerr << "laby: option -" << optopt << " requires an argument" << endl;
				else
					cerr << "laby: unknown option -" << optopt << endl;
				return 1;
		}

	if (optind < argc) {
		for (int i = optind; i < argc; i++)
			cerr << "laby: unknown argument " << argv[i] << endl;
		cerr << "Use laby -h to get usage" << endl;
		return 1;
	}


	cout << "rows: " << rows << ", cols: " << cols << endl;
	cout << coulOff();

	Generate();
	if (ShowSolution)
		Solve();
	Print();


#ifdef _WIN32
	cout << endl << "(Pause)";
	cin.get();
#endif
	return 0;
}

