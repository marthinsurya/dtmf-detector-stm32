#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FS 8000.0f
#define PI_F 3.14159265f
#define N 800
#define KEYS_PER_SNR 16
#define NUM_TONES 4
#define NUM_SNRS 4
#define INPUT_SCALE 0.25f

int16_t float_to_q15(float x) {
    float scaled = x * 32768.0f;
    if (scaled > 32767.0f) {
        scaled = 32767.0f;
    }
    if (scaled < -32768.0f) {
        scaled = -32768.0f;
    }
    return (int16_t)roundf(scaled);
}


// f_low  = {697, 770, 852, 941};
// f_high = {1209, 1336, 1477, 1633};
// coeff = cos(2*pi*f/FS) in Q15, FS = 8000
static const int16_t coeff_low[NUM_TONES]  = {27980, 26956, 25701, 24219};
static const int16_t coeff_high[NUM_TONES] = {19073, 16325, 13085, 9315};

int64_t q15_goertzel_state(const float *x, int n, int16_t coeff_half, int32_t *s1, int32_t *s2){
    *s1 = 0;
    *s2 = 0;

    for (int i = 0; i < n; i++) {
        int16_t s = float_to_q15(x[i] * INPUT_SCALE);
        int64_t term = ((int64_t)coeff_half * *s1) >> 14;
        int32_t s0 = s + (int32_t)term - *s2;
        *s2 = *s1;
        *s1 = s0;
    }

    int64_t term = ((int64_t)coeff_half * *s1) >> 14;
    int64_t energy = (int64_t)*s1 * *s1 + (int64_t)*s2* *s2 - term * *s2;
    return energy;
}


static const char keys[NUM_TONES][NUM_TONES] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char detect_q15(const float *x, int n){
    int best_low = 0;
    int best_high = 0;
    int64_t e_low[NUM_TONES];
    int64_t e_high[NUM_TONES];
    int32_t s1, s2;

    for (int i = 0; i < NUM_TONES; i++) {
        e_low[i] = q15_goertzel_state(x, n, coeff_low[i], &s1, &s2);
        e_high[i] = q15_goertzel_state(x, n, coeff_high[i], &s1, &s2);
    }

    for (int i = 1; i < NUM_TONES; i++) {
        if (e_low[i] > e_low[best_low]) {
            best_low = i;
        }
        if (e_high[i] > e_high[best_high]) {
            best_high = i;
        }
    }
    return keys[best_low][best_high];
}




int main(void) {
    FILE *fp = fopen("c/signals.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "can't open file\n");
        return 1;
    }
    char key;
    int snr;
    int line = 0;
    int correct[NUM_SNRS] = {0, 0, 0, 0};
    int snrs[NUM_SNRS];
        
    while (fscanf(fp, " %c %d", &key, &snr) == 2) {
        float x[N];
        //Read 1 signal
        for (int i = 0; i < N; i++) {
            int ok = fscanf(fp, "%f", &x[i]);
            if (ok != 1) {
                fprintf(stderr, "read failed at %d\n", i);
                fclose(fp);
                return 1;
            }             
        }
        line++;
        char got = detect_q15(x, N);

        snrs[(line - 1) / KEYS_PER_SNR] = snr;
        if (got == key) {
            correct[(line - 1) / KEYS_PER_SNR]++;
        }          
    }

    for (int i = 0; i < NUM_SNRS; i++) {
        printf("snr %d: %d/%d correct\n", snrs[i], correct[i], KEYS_PER_SNR);
    }

    fclose(fp);

    return 0;
}