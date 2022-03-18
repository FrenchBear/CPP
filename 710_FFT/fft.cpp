// FFT C++
// 2021-02-14   PV

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>

using namespace std;

typedef complex<double> Complex;

void fft(Complex f[], long n, int isign)
{
    double pi = isign> 0 ? M_PI : -M_PI;

    for (long m=n; m > 1; m /= 2)
    {
        long mh = m / 2;
        double phi= pi / mh;
        for (long j=0; j < mh; ++j)
        {
            double p = phi* j;
            Complex cs = Complex(cos(p), sin(p));

            for (long t1=j; t1< j+n; t1+= m) {
                Complex u = f[t1];
                Complex v = f[t1+mh];
                f[t1] = u+v;
                f[t1+mh] = (u-v) * cs;
            }
        }
    }

    //I data reordering:
    for (long m=1, j=0; m < n-1; ++m)
    {
        for (long k=n>>1; (!((j^=k)&k)); k>>=1) {;}
        if ( j > m) // SWAP(f[m], f[j]);
        {
            Complex t = f[m];
            f [m] = f[j];
            f [j] = t;
        }
    }

    if (isign < 0) // normalise if backwards transform
        for (long k=0; k < n; ++k) f[k] /= n;
}

int main()
{
    Complex fh[8];
    fh[0] = Complex(1, 0);
    fh[1] = Complex(2, 0);
    fh[2] = Complex(3, 0);
    fh[3] = Complex(4, 0);
    fh[4] = Complex(0, 0);
    fh[5] = Complex(0, 0);
    fh[6] = Complex(0, 0);
    fh[7] = Complex(0, 0);

    fft(fh, 8, 1);

    for (int i=0 ; i<8 ; i++)
        cout << fh[i] << "  ";
    cout << "\n";
}
