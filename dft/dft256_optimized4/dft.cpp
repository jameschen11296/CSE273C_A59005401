#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE],DTYPE imag_out[SIZE])
{
#pragma HLS ARRAY_PARTITION variable=real_sample cyclic factor=8
#pragma HLS ARRAY_PARTITION variable=imag_sample cyclic factor=8
	int theta=0;
	for(int i=0;i<SIZE;i++){
		real_out[i]=0;
		imag_out[i]=0;
		for(int j=0;j<SIZE;j++){
			#pragma HLS UNROLL factor=8
			theta=(i*j)&0xFF;
			real_out[i] += (real_sample[j]*cos_coefficients_table[theta]-imag_sample[j]*sin_coefficients_table[theta]);
			imag_out[i] += (real_sample[j]*sin_coefficients_table[theta]+imag_sample[j]*cos_coefficients_table[theta]);
		}
	}
}
