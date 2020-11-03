#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE],DTYPE imag_out[SIZE])
{
#pragma HLS INTERFACE ap_vld port=real_sample
#pragma HLS INTERFACE ap_vld port=imag_sample
//#pragma HLS ARRAY_PARTITION variable=real_sample cyclic factor=16
//#pragma HLS ARRAY_PARTITION variable=imag_sample cyclic factor=16
	for(int i=0;i<SIZE;i++){
//#pragma HLS pipeline II=200
		for(int j=0;j<SIZE;j++){
			#pragma HLS unroll factor=16
			//#pragma HLS pipeline
			muladdre(real_sample[j],imag_sample[j],cos_coefficients_table[(i*j)&0xFF],sin_coefficients_table[(i*j)&0xFF], real_out[i]);
			muladdim(real_sample[j],imag_sample[j],cos_coefficients_table[(i*j)&0xFF],sin_coefficients_table[(i*j)&0xFF], imag_out[i]);
		}
	}
}
void muladdre(DTYPE re,DTYPE im,DTYPE co, DTYPE si, DTYPE &out){
	DTYPE tempmul1,tempmul2,tempsub;
	multiply_two_numbers(re,co,tempmul1);
	multiply_two_numbers(im,si,tempmul2);
	sub_two_numbers(tempmul1,tempmul2,tempsub);
	accumulate(tempsub,out);
}
void muladdim(DTYPE re,DTYPE im,DTYPE co, DTYPE si, DTYPE &out){
	DTYPE tempmul1,tempmul2,tempsub;
	multiply_two_numbers(re,si,tempmul1);
	multiply_two_numbers(im,co,tempmul2);
	add_two_numbers(tempmul1,tempmul2,tempsub);
	accumulate(tempsub,out);
}
void multiply_two_numbers(DTYPE A,DTYPE B, DTYPE &C){
	C=A*B;
}
void add_two_numbers(DTYPE A,DTYPE B, DTYPE &C){
	C=A+B;
}
void sub_two_numbers(DTYPE A,DTYPE B, DTYPE &C){
	C=A-B;
}
void accumulate(DTYPE A,DTYPE &C){
	C=A+C;
}
