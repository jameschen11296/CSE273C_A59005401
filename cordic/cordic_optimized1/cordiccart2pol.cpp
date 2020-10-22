#include "cordiccart2pol.h"
#include "ap_fixed.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

ap_fixed<27, 3> angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};

#define rot_num 11
data_t GainReciprocal[NO_ITER] ={0.707106781,0.632455532,0.613571991,0.608833913,0.607648256,0.607351770,0.607277644,0.607259112,0.607254479,0.607253321,0.607253032,0.607252959,0.607252941,0.607252937,0.607252935,0.607252935};

//set_directive_unroll "cordiccart2pol/cordiccart2pol_label0"
//set_directive_unroll "cordiccart2pol/cordiccart2pol_label1"

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE ap_vld port=y
#pragma HLS INTERFACE ap_vld port=x
	ap_fixed<27,3> xfix=x, yfix=y,temp=0,thetares=0;
	ap_fixed<27,3> gaintemp=GainReciprocal[rot_num-1],xtemp=0;
	if(xfix<0){
		if(yfix>0){
			thetares=1.570796327;
			temp=yfix;
			yfix=~xfix+(1>>24);
			xfix=temp;
		}
		else{
			thetares=-1.570796327;
			temp=yfix;
			yfix=xfix;
			xfix=~temp+(1>>24);
		}
	}
	cordiccart2pol_label0:for(int i=0;i<rot_num;i++){
		if(yfix>0){
			temp=xfix;
			xfix=xfix+(yfix>>i);
			yfix=yfix-(temp>>i);
			thetares=thetares+angles[i];
		}
		else if(yfix<0){
			temp=xfix;
			xfix=xfix-(yfix>>i);
			yfix=(temp>>i)+yfix;
			thetares=thetares-angles[i];
		}
	}
	cordiccart2pol_label1:for(int i=0;i<24;i++){
		xfix=xfix>>1;
		gaintemp=gaintemp<<1;
		if(gaintemp&0x01){
			xtemp+=xfix;
		}
	}
	*theta=thetares;
	*r=(float)xtemp;
}
