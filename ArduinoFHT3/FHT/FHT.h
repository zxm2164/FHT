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


class audio {
	private:
			int numBins;														//number of bins in the fht
			void fht( float *v, int n, float *tmp );	//calculate the fht with a sample set
	public:
		int getBinAmplitude(int bin);
		void setNumBins(int num);
		int update(int sample);
};
