#include<math.h>
#include "dft.h"
#include"coefficients1024.h"

void dft(axis_t *INPUT1, axis_t *INPUT2, axis_t *OUTPUT1, axis_t *OUTPUT2){
#pragma HLS INTERFACE s_axilite port=1024 bundle=CTRL
#pragma HLS INTERFACE axis depth=1024 port=OUTPUT1
#pragma HLS INTERFACE axis depth=1024 port=OUTPUT2
#pragma HLS INTERFACE axis depth=1024 port=INPUT1
#pragma HLS INTERFACE axis depth=1024 port=INPUT2
	DTYPE real_sample[SIZE], imag_sample[SIZE];
	DTYPE real_out[SIZE], imag_out[SIZE];
	for(int i=0; i<SIZE; i++){
			axis_t cur1 = *INPUT1++;
			axis_t cur2 = *INPUT2++;
			real_sample[i] = cur1.data;
			imag_sample[i] = cur2.data;
	}
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			#pragma HLS unroll factor=16
			muladdre(real_sample[j],imag_sample[j],cos_coefficients_table[(i*j)%SIZE],sin_coefficients_table[(i*j)%SIZE], real_out[i]);
			muladdim(real_sample[j],imag_sample[j],cos_coefficients_table[(i*j)%SIZE],sin_coefficients_table[(i*j)%SIZE], imag_out[i]);
		}
	}
	axis_t cur3,cur4;
	for(int i=0;i<SIZE-1;i++){
		cur3.data=real_out[i];
		cur3.last=0;
		*OUTPUT1++ = cur3;
		cur4.data=imag_out[i];
		cur4.last=0;
		*OUTPUT2++ = cur4;
	}
	cur3.data=real_out[SIZE-1];
	cur3.last=1;
	*OUTPUT1++ = cur3;
	cur4.data=imag_out[SIZE-1];
	cur4.last=1;
	*OUTPUT2++ = cur4;
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
