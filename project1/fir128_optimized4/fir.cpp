/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

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
	static data_t delay_line[N];
	shift_accum_loop1: for(int i=N-1;i>N/2;i--){
		//divide the N-1 iteration
		//this loop is from i=N-1 to i=N/2+1
		if(i==(N/2)+1){
			delay_line[(N/2)+1]=delay_line[N/2];
			data+=delay_line[N/2]*c[(N/2)+1];
		}
		else{
			delay_line[i]=delay_line[i-1];
			data+=delay_line[i]*c[i];
		}
	}
	shift_accum_loop2: for(int i=N/2;i>=0;i--){
		//this loop is from i=N/2 to i=0
		if(i==0){
			delay_line[0]=x;
			data+=x*c[0];
		}
		else{
			delay_line[i]=delay_line[i-1];
			data+=delay_line[i]*c[i];
		}
	}
	*y=data;
}
