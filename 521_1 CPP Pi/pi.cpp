// pi.cpp : Implementation of pi calculation
// 2014-03-26	PV	Port to VS 2013
//

#include "stdafx.h"

#define	MAXPRC	4001
char p[MAXPRC];
char t[MAXPRC];
int q;

#define	FALSE	0
#define	TRUE	1

void add();
void sub();
void mul(register int multiplier);
void div(int divisor);
void mul4();
void div4();
int tiszero();


void arctan(register int s)
{
	register int n;

	t[0] = 1;
	div(s);			/* t[] = 1/s */
	add();
	n = 1;
	do {
		mul(n);
		div(s * s);
		div(n += 2);
		if (((n - 1) / 2) % 2 == 0)
			add();
		else
			sub();
	} while (!tiszero());
}

void add()
{
	register int j;

	for (j = q; j >= 0; j--)
		if (t[j] + p[j] > 9) {
			p[j] += t[j] - 10;
			p[j - 1] += 1;
		}
		else
			p[j] += t[j];
}

void sub()
{
	register int j;

	for (j = q; j >= 0; j--)
		if (p[j] < t[j]) {
			p[j] -= t[j] - 10;
			p[j - 1] -= 1;
		}
		else
			p[j] -= t[j];
}

void mul(register int multiplier)
{
	int b;
	register int i;
	int carry = 0, digit = 0;

	for (i = q; i >= 0; i--) {
		b = (t[i] * multiplier + carry);
		digit = b % 10;
		carry = b / 10;
		t[i] = digit;
	}
}

/* t[] /= l */

void div(int divisor)
{
	register int i, b;
	int quotient, remainder = 0;

	for (i = 0; i <= q; i++) {
		b = (10 * remainder + t[i]);
		quotient = b / divisor;
		remainder = b % divisor;
		t[i] = quotient;
	}
}

void div4()
{
	register int i, c, d = 0;

	for (i = 0; i <= q; i++) {
		c = (10 * d + p[i]) / 4;
		d = (10 * d + p[i]) % 4;
		p[i] = c;
	}
}

void mul4()
{
	register int i, c, d;

	d = c = 0;

	for (i = q; i >= 0; i--) {
		d = (p[i] * 4 + c) % 10;
		c = (p[i] * 4 + c) / 10;
		p[i] = d;
	}
}

int tiszero()
{
	register int k;

	for (k = 0; k <= q; k++)
		if (t[k] != 0)
			return(FALSE);
	return(TRUE);
}


int _tmain(int argc, _TCHAR* argv[])
{
	time_t startime, endtime;
	register int i;

	// Nb of decimals
	q = 4000;

	if (q >= MAXPRC) {
		printf("Precision too large\n");
		return(66);
	}

	/* compute pi */
	time(&startime);
	arctan(2);
	arctan(3);
	mul4();
	time(&endtime);

	/* print pi */

	printf("%d", p[0]);
	for (i = 1; i <= q; i++)
		printf("%d", p[i]);
	printf("\n");
	printf("%d seconds to compute %d digits of pi\n", (int)(endtime - startime), q);

	getchar();
	return 0;
}

