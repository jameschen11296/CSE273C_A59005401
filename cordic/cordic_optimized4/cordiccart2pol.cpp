#include "cordiccart2pol.h"
#include "ap_fixed.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

ap_fixed<27,3> angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};

#define rot_num 16
data_t GainReciprocal[NO_ITER] ={0.707106781,0.632455532,0.613571991,0.608833913,0.607648256,0.607351770,0.607277644,0.607259112,0.607254479,0.607253321,0.607253032,0.607252959,0.607252941,0.607252937,0.607252935,0.607252935};

//set_directive_unroll "cordiccart2pol/cordiccart2pol_label0"
//set_directive_unroll "cordiccart2pol/cordiccart2pol_label1"

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE ap_vld port=y
#pragma HLS INTERFACE ap_vld port=x
	ap_fixed<27,3> xfix=x, yfix=y,temp=0,xtemp0,xtemp1,ytemp0,ytemp1,thetarestemp;
	ap_fixed<27,3> thetares=0,thetarespositive,thetaresnegative;
	ap_fixed<27,3> gaintemp=GainReciprocal[rot_num-1],xtemp=0,xtempadd=0;
	temp=yfix;
	thetarestemp=yfix>0?1.570796327:-1.570796327;
	ytemp0=~xfix+(1>>24);
	xtemp0=~temp+(1>>24);
	ytemp1=yfix>0?ytemp0:xfix;
	xtemp1=yfix>0?temp:xtemp0;

	thetares=xfix<0?thetarestemp:thetares;
	yfix=xfix<0?ytemp1:yfix;
	xfix=xfix<0?xtemp1:xfix;

	cordiccart2pol_label0:for(int i=0;i<rot_num;i++){
		temp=xfix;
		xfix=yfix>0?xfix+(yfix>>i):xfix-(yfix>>i);
		thetarespositive=thetares+angles[i];
		thetaresnegative=thetares-angles[i];
		thetares=yfix>0?thetarespositive:thetares;
		thetares=yfix<0?thetaresnegative:thetares;
		yfix=yfix>0?yfix-(temp>>i):(temp>>i)+yfix;
	}
	cordiccart2pol_label1:for(int i=0;i<24;i++){
		xfix=xfix>>1;
		gaintemp=gaintemp<<1;
		xtempadd=xfix+xtemp;
		xtemp=gaintemp&0x01?xtempadd:xtemp;
	}
	*theta=thetares;
	*r=(float)xtemp;
}
