// pi_con.cpp
// 2007-01-10	PV	Max 400 digits
// 2017-04-30	PV	VC2017 and Git
// 2017-08-18	PV	Build on Debian 9.1

#include "stdafx.h"

int main(int argc, char* argv[])
{
	long a = 10000, b, c, d, e, *f, g;

	printf("digits? ");
	(void)scanf("%ld", &c); (void)getchar();
	c *= 3.5; c -= c % 14;
	f = (long *)malloc(4 * c + 4);
	for (b = 0; b - c;)f[b++] = a / 5;
	for (e = 0; d = 0, g = c * 2; c -= 14, printf("%.4ld", e + d / a), e = d%a)
		for (b = c; d += f[b] * a, f[b] = d%--g, d /= g--, --b; d *= b);
	printf("\n");

	printf("\n(pause) ");
	(void)getchar();
	return 0;
}
