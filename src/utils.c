#include <stdio.h>
#include <math.h>
#include "utils.h"

// read 16-bit mono wav (very simplified)

int read_wav_samples(const char *filename, double *buffer, int max_samples) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;
    //! skip WAV header (44 bytes)
    unsigned char header[44];
    fread(header, sizeof(unsigned char), 44, f);

    int16_t sample;
    int i = 0;

    while (fread(&sample, sizeof(int16_t), 1, f) == 1 && i < max_samples) {
        buffer[i++] = (double)sample / 32768.0; //! normalize [-1,1]
    }

    fclose(f);
    return i;
}

void dft(Complex *input, Complex *output, int N) {
    for (int k = 0; k < N; k++) {
        output[k].real = 0.0;
        output[k].imag = 0.0;

        for (int n = 0; n < N; n++) {
            double angle = 2.0 * PI * k * n / N;

            double cos_val = cos(angle);
            double sin_val = sin(angle);
            
            //Yes, the imaginary part of the input is considered... We're doing maths here!
            output[k].real += input[n].real * cos_val + input[n].imag * sin_val;
            output[k].imag += input[n].imag * cos_val - input[n].real * sin_val;
        }
    }
}

void print_complex_array(Complex *arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("X[%d] = %f + %fi\n", i, arr[i].real, arr[i].imag);
    }
}