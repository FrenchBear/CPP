// Piece.h: interface for the Piece class.
//
// 2022-07-13	PV		Modern C++ cleanup

#pragma once

class Piece
{
public:
	short	hNumPiece;		// N° dans le jeu Katamino
	char	cPiece;			// Lettre
	Carre55 c[8];			// 8 transformations maxi
	int		iNbt;			// Nb de transformations


	Piece(short hNP, char cP,
		char i00, char i01, char i02, char i03, char i04,
		char i10, char i11, char i12, char i13, char i14,
		char i20, char i21, char i22, char i23, char i24);
	void Dessin() const;
};
