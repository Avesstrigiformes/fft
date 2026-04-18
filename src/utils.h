#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#define PI 3.14159265358979323846
typedef struct {double real; double imag;} Complex;
int read_wav_samples(const char *filename, double *buffer, int max_samples);
void dft(Complex *input, Complex *output, int N);
void print_complex_array(Complex *arr, int N);

#endif