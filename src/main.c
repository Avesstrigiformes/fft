#include <stdio.h>
#include <math.h>
#include "utils.h"

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

    /*
    Complex test_input_sine[50] = {
        {0.0, 0.0}, {0.309, 0.0}, {0.588, 0.0}, {0.809, 0.0}, {0.951, 0.0},
        {1.0, 0.0}, {0.951, 0.0}, {0.809, 0.0}, {0.588, 0.0}, {0.309, 0.0},
        {1e-6, 0.0}, {-0.309, 0.0}, {-0.588, 0.0}, {-0.809, 0.0}, {-0.951, 0.0},
        {-1.0, 0.0}, {-0.951, 0.0}, {-0.809, 0.0}, {-0.588, 0.0}, {-0.309, 1e-6},
        {1e-6, 1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6},
        {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6},
        {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6},
        {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6},
        {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6},
        {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}, {1e-6, -1e-6}
    };
    Complex test_output[50];
    dft(test_input_sine, test_output, 50);
    print_complex_array(test_output, 50);
    */

    printf("Frequency magnitudes:\n");
    for (int k = 0; k < N / 2; k++) {
        //TODO WE SHOULD PROBABLY CHANGE THIS
        double mag = sqrt(output[k].real * output[k].real + output[k].imag * output[k].imag);
        double freq = (double)k * 44100.0 / N; //? frequency in Hz
        double db = 20.0 * log10(mag + 1e-6); //? magnitude in dB
        printf("bin %d (%.1f Hz): %f dB, mag: %f \n", k, freq, db, mag);
    }
    return 0;
}