// Piece.cpp: implementation of the Piece class.
// Gestion "haut niveau" d'un pentomino
// 1998-12-26	PV
// 2006-10-01   PV  VS2005
// 2012-02-25   PV  VS2010
// 2017-08-18   PV  Compile on Debian, case-sensitive FS updates

#include "StdAfx.h"
#include <stdio.h>

#include "Carre55.h"
#include "Piece.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Piece::Piece(short hNP, char cP,
	int i00, int i01, int i02, int i03, int i04,
	int i10, int i11, int i12, int i13, int i14,
	int i20, int i21, int i22, int i23, int i24)
{
	hNumPiece = hNP;
	cPiece = cP;
	c[0] = Carre55(i00, i01, i02, i03, i04, i10, i11, i12, i13, i14, i20, i21, i22, i23, i24);
	iNbt = 1;
	if (i00 + i01 + i02 + i03 + i04 + i10 + i11 + i12 + i13 + i14 + i20 + i21 + i22 + i23 + i24 != 5)
		printf("Définition de la pièce %d incorrecte\n", hNP);

	// On génère le tableau des transformations possibles
	int i, j;


	for (i = 1; i < 8; i++)
	{
		Carre55 ct = c[0].Transformation(i);
		int bDejaVu = FALSE;

		for (j = 0; j < iNbt; j++)
			if (c[j] == ct)
			{
				bDejaVu = TRUE;
				break;
			}
		if (!bDejaVu)
			c[iNbt++] = ct;
	}
}



// Traces
void Piece::Dessin()
{
	printf("Pièce %d %c iNbt=%d\n", hNumPiece, cPiece, iNbt);
}
