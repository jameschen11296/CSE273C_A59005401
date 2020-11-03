#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
	int theta=0;
	DTYPE real_temp[SIZE],imag_temp[SIZE];
	for(int i=0;i<SIZE;i++){
		real_temp[i]=0;
		imag_temp[i]=0;
		for(int j=0;j<SIZE;j++){
			theta=(i*j)&0xFF;
			real_temp[i] += (real_sample[j]*cos_coefficients_table[theta]-imag_sample[j]*sin_coefficients_table[theta]);
			imag_temp[i] += (real_sample[j]*sin_coefficients_table[theta]+imag_sample[j]*cos_coefficients_table[theta]);
		}
	}
	for(int k=0;k<SIZE;k++){
		real_sample[k]=real_temp[k];
		imag_sample[k]=imag_temp[k];
	}
}
