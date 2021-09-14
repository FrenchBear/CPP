// Pi1Line.c
// Calcul de Pi au compte-gouttes, 8000 chiffres maxi
// 2014-03-26	PV	VS2013
// 2017-08-18	PV	Debian 9.1

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

int a = 10000, b, c, d, e, *f, g;
int main(int argc, char**argv)
{
	printf("digits?"); scanf("%d", &c); c *= 3.5; c -= c % 14; f = (int*)malloc(4 * c + 4);
	for (; b - c;) f[b++] = a / 5; 
	for (; d = 0, g = c * 2; c -= 14, printf("%.4d", e + d / a), e = d%a)
		for (b = c; d += f[b] * a, f[b] = d%--g, d /= g--, --b; d *= b);
	printf("\n");
	getchar();
	return 0;
}
