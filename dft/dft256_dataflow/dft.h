
typedef float DTYPE;
#define SIZE 256 		/* SIZE OF DFT */
void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE], DTYPE real_out[SIZE], DTYPE imag_out[SIZE]);
void muladdre(DTYPE re, DTYPE im,DTYPE co, DTYPE si, DTYPE &out);
void muladdim(DTYPE re, DTYPE im,DTYPE co, DTYPE si, DTYPE &out);
void multiply_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void add_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void sub_two_numbers(DTYPE A,DTYPE B, DTYPE &C);
void accumulate(DTYPE A,DTYPE &C);
