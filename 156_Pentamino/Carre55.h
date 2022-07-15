// Carre55.h: interface for the Carre55 class.
//
// 2022-07-13	PV		Modern C++ cleanup

#pragma once

class Carre55
{
public:
	char	tMotif[5][5];
	int		lmax, cmax;		// Encombrement de la pi�ce
	int		iOffsetCol;		// D�calage de colonne pour occuper la cellule [0][0]


	Carre55()
	{
		int l, c;
		for (l = 0; l < 5; l++)
			for (c = 0; c < 5; c++)
				tMotif[l][c] = 0;
		lmax = cmax = 0;
		iOffsetCol = 0;
	}

	Carre55(char i00, char i01, char i02, char i03, char i04,
			char i10, char i11, char i12, char i13, char i14,
			char i20, char i21, char i22, char i23, char i24)
	{
		tMotif[0][0] = i00; tMotif[0][1] = i01; tMotif[0][2] = i02; tMotif[0][3] = i03; tMotif[0][4] = i04;
		tMotif[1][0] = i10; tMotif[1][1] = i11; tMotif[1][2] = i12; tMotif[1][3] = i13; tMotif[1][4] = i14;
		tMotif[2][0] = i20; tMotif[2][1] = i21; tMotif[2][2] = i22; tMotif[2][3] = i23; tMotif[2][4] = i24;
		tMotif[3][0] = 0;   tMotif[3][1] = 0;   tMotif[3][2] = 0;   tMotif[3][3] = 0;   tMotif[3][4] = 0;
		tMotif[4][0] = 0;   tMotif[4][1] = 0;   tMotif[4][2] = 0;   tMotif[4][3] = 0;   tMotif[4][4] = 0;

		lmax = 3;
		if (i20 + i21 + i22 + i23 + i24 == 0) lmax = 2;
		if (i10 + i11 + i12 + i13 + i14 == 0) lmax = 1;

		cmax = 5;
		if (i04 + i14 + i24 == 0) cmax = 4;
		if (i03 + i13 + i23 == 0) cmax = 3;
		if (i02 + i12 + i22 == 0) cmax = 2;
		if (i01 + i11 + i21 == 0) cmax = 1;

		MkOffset();
	}


	// D�termine la propri�t� iOffsetCol, c'est � dire le nombre de colonnes qu'il
	// faut translater le dessin � gauche pour occuper la cellule [0][0]
	void MkOffset()
	{
		if (tMotif[0][0])
			iOffsetCol = 0;
		else if (tMotif[0][1])
			iOffsetCol = 1;
		else if (tMotif[0][2])
			iOffsetCol = 2;
		else if (tMotif[0][3])
			iOffsetCol = 3;
		else
			iOffsetCol = 4;
	}


	// Op�rateur de comparaison
	int operator == (const Carre55 &k) const
	{
		return lmax == k.lmax && cmax == k.cmax &&
			tMotif[0][0] == k.tMotif[0][0] && tMotif[0][1] == k.tMotif[0][1] && tMotif[0][2] == k.tMotif[0][2] && tMotif[0][3] == k.tMotif[0][3] && tMotif[0][4] == k.tMotif[0][4] &&
			tMotif[1][0] == k.tMotif[1][0] && tMotif[1][1] == k.tMotif[1][1] && tMotif[1][2] == k.tMotif[1][2] && tMotif[1][3] == k.tMotif[1][3] && tMotif[1][4] == k.tMotif[1][4] &&
			tMotif[2][0] == k.tMotif[2][0] && tMotif[2][1] == k.tMotif[2][1] && tMotif[2][2] == k.tMotif[2][2] && tMotif[2][3] == k.tMotif[2][3] && tMotif[2][4] == k.tMotif[2][4] &&
			tMotif[3][0] == k.tMotif[3][0] && tMotif[3][1] == k.tMotif[3][1] && tMotif[3][2] == k.tMotif[3][2] && tMotif[3][3] == k.tMotif[3][3] && tMotif[3][4] == k.tMotif[3][4] &&
			tMotif[4][0] == k.tMotif[4][0] && tMotif[4][1] == k.tMotif[4][1] && tMotif[4][2] == k.tMotif[4][2] && tMotif[4][3] == k.tMotif[4][3] && tMotif[4][4] == k.tMotif[4][4];
	}

	// Transformations
	int TL(int iT, int l, int c) const;
	int TC(int iT, int l, int c) const;
	Carre55 Transformation(int iT) const;

	void Dessin() const;
};

