#include "ap_int.h"

struct axis_t {
	float data;
	ap_int<1> last;
};

typedef float DTYPE;
#define SIZE 1024 		/* SIZE OF DFT */
void dft(axis_t *INPUT1, axis_t *INPUT2, axis_t *OUTPUT1, axis_t *OUTPUT2);
void muladdre(DTYPE re, DTYPE im,DTYPE co, DTYPE si, DTYPE &out);
void muladdim(DTYPE re, DTYPE im,DTYPE co, DTYPE si, DTYPE &out);
void multiply_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void add_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void sub_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void accumulate(DTYPE A,DTYPE &C);
