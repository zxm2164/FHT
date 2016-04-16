/* Factored discrete Hartley transform, or FHT, and its inverse iFHT */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define q	3		/* for 2^3 points */
#define N	(1<<q)		/* N-point FFT, iFFT */

typedef float real;

#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif


/* Print a vector of reals. */
static void
print_vector(
	     const char *title,
	     real *x,
	     int n)
{
  int i;
  printf("%s (dim=%d):", title, n);
  for(i=0; i<n; i++ ) printf(" %8.4f", x[i]);
  putchar('\n');
  return;
}


/*
   fht(v,N):
   [0]  If N==1 then return.
   [1]  For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2]  Compute fht(ve, N/2);
   [3]  For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4]  Compute fht(vo, N/2);
   [5]  For m = 1 to N/2-1, do [6] through [9]
   [6]    Let c = cos(2*PI*m/N)
   [7]    Let s = sin(2*PI*m/N)
   [8]    Let v[m] = ve[m] + c*vo[m] + s*vo[N/2-m]
   [9]    Let v[m+N/2] = ve[m] - c*vo[m] - s*vo[N/2-m]
   [10] Let v[0] = ve[0] + vo[0]
   [11] Let v[N/2] = ve[N/2] - vo[N/2]
 */
void
fht( real *v, int n, real *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
    int k,m;    real *vo, *ve, c, s;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    fht( ve, n/2, v );		/* FHT on even-indexed elements of v[] */
    fht( vo, n/2, v );		/* FHT on odd-indexed elements of v[] */
    for(m=1; m<n/2; m++) {
      c = cos(2*PI*m/(double)n);
      s = sin(2*PI*m/(double)n);
      v[  m  ] = ve[m] + c*vo[m] + s*vo[n/2-m];
      v[m+n/2] = ve[m] - c*vo[m] - s*vo[n/2-m];
    }
    v[ 0 ] = ve[0] + vo[0];
    v[n/2] = ve[0] - vo[0];	/* since ve[n/2]==ve[0] and vo[n/2]==vo[0] */
  }
  return;
}
