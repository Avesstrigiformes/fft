#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
typedef struct {double real; double imag;} Complex;

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
        buffer[i++] = (double)sample / 32768.0; // normalize [-1,1]
    }

    fclose(f);
    return i;
}

// DFT implementation

void dft(Complex *input, Complex *output, int N) {
    for (int k = 0; k < N; k++) {
        output[k].real = 0.0;
        output[k].imag = 0.0;

        for (int n = 0; n < N; n++) {
            double angle = -2.0 * PI * k * n / N;

            double cos_val = cos(angle);
            double sin_val = sin(angle);

            // Multiply input[n] * e^{-i angle}
            output[k].real += input[n].real * cos_val - input[n].imag * sin_val;
            output[k].imag += input[n].real * sin_val + input[n].imag * cos_val;
        }
    }
}

// Utility to print complex array (for debugging)

void print_complex_array(Complex *arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("X[%d] = %f + %fi\n", i, arr[i].real, arr[i].imag);
    }
}

int main() {
    int N = 1024; //? DFT size

    double samples[44100]; //? buffer for 1 second of audio at 44.1kHz
    int sample_count = read_wav_samples("audio.wav", samples, 44100);

    if (sample_count < 0) {
        printf("Failed to open WAV file\n");
        return 1;
    }

    Complex input[N];
    Complex output[N];

    for (int i = 0; i < N; i++) {
        input[i].real = samples[i];
        input[i].imag = 0.0;
    }

    dft(input, output, N);

    printf("Frequency magnitudes:\n");
    for (int k = 0; k < N / 2; k++) {
        double mag = sqrt(output[k].real * output[k].real + output[k].imag * output[k].imag);
        double freq = (double)k * 44100.0 / N; //? frequency in Hz
        double db = 20.0 * log10(mag + 1e-6); //? magnitude in dB
        printf("bin %d (%.1f Hz): %f dB, mag: %f \n", k, freq, db, mag);
    }
    return 0;
}