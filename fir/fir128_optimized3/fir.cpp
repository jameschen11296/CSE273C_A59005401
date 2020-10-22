/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/
//Solution1: no pipeline
//
//Solution2: add pipleline 
//set_directive_pipeline -II 1 "fir/shift_accum_loop1"

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{
#pragma HLS INTERFACE ap_vld port=y
#pragma HLS INTERFACE ap_vld port=x
	coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	data_t data=0;
	int i;
	static data_t delay_line[N]={};
	shift_accum_loop1: for(int i=N-1;i>0;i--){
		delay_line[i]=delay_line[i-1];
		data+=delay_line[i]*c[i];
	}
	delay_line[0]=x;
	data+=x*c[0];
	//the operation for i=0 is done outside the loop
	*y=data;
}



