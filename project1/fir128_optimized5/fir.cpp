/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

//Solution1: pipeline + memory partitioning parameter=complete
/*
set_directive_array_partition -type complete -dim 1 "fir" delay_line
set_directive_pipeline "fir/shift_accum_loop1"
*/

//Solution2: pipeline + memory partitioning parameter=block
/*
set_directive_array_partition -type block -factor 2 -dim 1 "fir" delay_line
set_directive_pipeline "fir/shift_accum_loop1"
*/

//Solution3: pipeline + memory partitioning parameter=cyclic
/*
set_directive_array_partition -type cyclic -factor 2 -dim 1 "fir" delay_line
set_directive_pipeline "fir/shift_accum_loop1"
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
	static data_t delay_line[N]={};
	shift_accum_loop1: for(int i=N-1;i>=0;i--){
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
