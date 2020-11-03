#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
	DTYPE theta=0,thetac=0,thetas=0;
	DTYPE real_temp[SIZE],imag_temp[SIZE];
	for(int i=0;i<SIZE;i++){
		real_temp[i]=0;
		imag_temp[i]=0;
		theta = ((2*3.141592653589)/SIZE) *i;
		for(int j=0;j<SIZE;j++){
			thetac =cos(theta*j);
			thetas =-sin(theta*j);
			real_temp[i] += (real_sample[j]*thetac-imag_sample[j]*thetas);
			imag_temp[i] += (real_sample[j]*thetas+imag_sample[j]*thetac);
		}
	}
	for(int k=0;k<SIZE;k++){
		real_sample[k]=real_temp[k];
		imag_sample[k]=imag_temp[k];
	}
}
