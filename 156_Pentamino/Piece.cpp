// Piece.cpp: implementation of the Piece class.
// Gestion "haut niveau" d'un pentomino
//
// 1998-12-26	PV
// 2006-10-01   PV		VS2005
// 2012-02-25   PV		VS2010
// 2017-08-18   PV		Compile on Debian, case-sensitive FS updates
// 2022-07-13	PV		Modern C++ cleanup

#include <iostream>

#include "Carre55.h"
#include "Piece.h"

#ifdef _WIN32
#include <format>       // std::format
#else
#include "gpp_format.h"
#endif

using namespace std;


Piece::Piece(short hNP, char cP,
			char i00, char i01, char i02, char i03, char i04,
			char i10, char i11, char i12, char i13, char i14,
			char i20, char i21, char i22, char i23, char i24)
{
	hNumPiece = hNP;
	cPiece = cP;
	c[0] = Carre55(i00, i01, i02, i03, i04, i10, i11, i12, i13, i14, i20, i21, i22, i23, i24);
	iNbt = 1;
	if (i00 + i01 + i02 + i03 + i04 + i10 + i11 + i12 + i13 + i14 + i20 + i21 + i22 + i23 + i24 != 5)
		cout << "Définition de la pièce " << hNP << " incorrecte\n";

	// On génère le tableau des transformations possibles
	for (int i = 1; i < 8; i++)
	{
		Carre55 &&ct = c[0].Transformation(i);
		int bDejaVu = false;

		for (int j = 0; j < iNbt; j++)
			if (c[j] == ct)
			{
				bDejaVu = true;
				break;
			}
		if (!bDejaVu)
			c[iNbt++] = ct;
	}
}



// Traces
void Piece::Dessin() const
{
	cout << std::format("Pi�ce {} {} iNbt={}\n", hNumPiece, cPiece, iNbt);
}
