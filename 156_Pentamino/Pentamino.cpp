// pentamino.cpp
// Résolution de problèmes de pentaminos (pavage)
//
// 1998-12-26	PV
// 2006-10-01   PV		VS2005
// 2012-02-25   PV		VS2010
// 2017-04-30	PV		VS2017 and Git
// 2017-08-18   PV		Compile on Debian, case-sensitive FS updates
// 2021-09-14	PV		VS2022; Fixed warnings; 64-bit compilation; Source UTF-8, it contains French accents...
// 2022-07-13	PV		Modern C++ cleanup

#include <iostream>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

// To avoid compiler useless Warning C6386: Buffer overrun while writing to 'jeu2':  the writable size is '60' bytes, but '70' bytes might be written.
#pragma warning(disable: 6385)
#pragma warning(disable: 6386)

const int MAXLIG = 12;
const int MAXCOL = 5;
const int MAXPIECE = 12;

const int MAXSOLUTION = 1000;


#include "Carre55.h"
#include "Piece.h"

int iNbSol = 0;
int iNbAppelPavage = 0;


// Plan de jeu
typedef char Jeu[MAXLIG][MAXCOL];

// Tableau de pointeurs sur les pentaminos à utiliser pour le problème
Piece* tP[MAXPIECE];


#pragma inline_recursion(on)
#pragma inline_depth(12)

void __inline Pavage(int lstart, int cstart, Jeu& jeu, int iMasquePieces)
{
	int l, c;
	int bTrouve = false;

	if (iNbSol > MAXSOLUTION) return;

	iNbAppelPavage++;

	// On cherche une case vide à couvrir, de gauche à droite, de haut en bas
	for (l = 0; l < MAXLIG; l++)
	{
		for (c = 0; c < MAXCOL; c++)
		{
			if (l == 0 && c == 0)	  // Accélération, on part de la dernière case vide trouvée
			{
				l = lstart;
				c = cstart;
			}

			if (jeu[l][c] == 0)
			{
				bTrouve = true;
				break;
			}
		}
		if (bTrouve)
			break;
	}

	// Si on n'en a pas trouvé, c'est que le pavage est terminé!
	if (l == MAXLIG && c == MAXCOL)
	{
		iNbSol++;
		return;
	}

	// On cherche parmi toutes les pièces qui restent une pièce pour couvrir la case vide
	int i, j;
	for (i = 0; i < MAXPIECE; i++)
		if (iMasquePieces & (1 << i))
			for (j = 0; j < tP[i]->iNbt; j++)	// Pour chacune des transformations
			{
				Carre55& ca = tP[i]->c[j];
				int l2, c2;
				int bCollision;

				//int bContinue = false;
				if (c + ca.cmax - ca.iOffsetCol > MAXCOL || // Trop large
					l + ca.lmax > MAXLIG ||					// Trop haut
					c < ca.iOffsetCol)						// Doit être décalée trop à gauche
					continue;

				bCollision = false;
				for (l2 = 0; l2 < ca.lmax; l2++)
				{
					for (c2 = 0; c2 < ca.cmax; c2++)
					{
						if (ca.tMotif[l2][c2] && jeu[l + l2][c + c2 - ca.iOffsetCol])  // Case déjà occupée
						{
							bCollision = true;
							break;
						}
					}
					if (bCollision)
						break;
				}

				if (!bCollision)
				{
					// Piece valable! On la place
					Jeu jeu2;
					memcpy(jeu2, jeu, sizeof(Jeu));

					for (l2 = 0; l2 < ca.lmax; l2++)
						for (c2 = 0; c2 < ca.cmax; c2++)
							if (ca.tMotif[l2][c2]) jeu2[l + l2][c + c2 - ca.iOffsetCol] = (char)(i + 1);

					// On continue avec les pièces qui restent
					Pavage(l, c, jeu2, iMasquePieces & ~(1 << i));
				}
			}
}


int main()
{
	// Préparation des pièces
	Piece P1(1, 'I', 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Piece P2(2, 'L', 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
	Piece P3(3, 'Y', 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	Piece P4(4, 'N', 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
	Piece P5(5, 'V', 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0);
	Piece P6(6, 'P', 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	Piece P7(7, 'U', 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	Piece P8(8, 'Z', 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0);
	Piece P9(9, 'F', 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0);
	Piece P10(10, 'T', 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0);
	Piece P11(11, 'W', 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0);
	Piece P12(12, 'X', 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0);

	/*
	P1.Dessin();
	P2.Dessin();
	P3.Dessin();
	P4.Dessin();
	P5.Dessin();
	P6.Dessin();
	P7.Dessin();
	P8.Dessin();
	P9.Dessin();
	P10.Dessin();
	P11.Dessin();
	P12.Dessin();
	*/

	if constexpr (MAXLIG * MAXCOL != 5 * MAXPIECE)
	{
		cout << "Constantes MAXLIG/MAXCOL/MAXPIECE incohérentes !\n";
		return 1;
	}

	// Plan à paver
	Jeu j;
	memset(&j, 0, static_cast<size_t>(MAXLIG * MAXCOL));

	// Pieces à utiliser
	tP[0] = &P2;
	tP[1] = &P3;
	tP[2] = &P6;
	tP[3] = &P11;
	tP[4] = &P8;
	tP[5] = &P4;
	tP[6] = &P5;
	tP[7] = &P10;
	tP[8] = &P9;
	tP[9] = &P1;
	tP[10] = &P7;
	tP[11] = &P12;

	auto t0 = high_resolution_clock::now();
	Pavage(0, 0, j, (1 << MAXPIECE) - 1);
	auto t1 = high_resolution_clock::now();
	auto duration = t1 - t0;

	cout << "Duration " << duration_cast<milliseconds>(t1 - t0).count() << "ms\n";
	cout << iNbSol << " solutions\n";
	cout << iNbAppelPavage << " calls to Pavage()\n";

	//printf("\n(pause) ");
	//(void)getchar();

	return 0;
}
